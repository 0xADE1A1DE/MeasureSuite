#include "loader.h"
#include "alloc_helper.h"
#include "error/error.h"
#include "io/elf_parser.h"
#include "io/file.h"
#include "io/shared_object.h"
#include "measuresuite.h"
#include "struct_measuresuite.h"
#ifdef USE_ASSEMBLYLINE
#include <assemblyline.h>
#endif
#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

// this essentially re-allocs the  permutation array with the new number of
// active functions and fills it with numbers 0..num_functions
static int reset_permutaions(measuresuite_t ms) {

  // allocate permutation
  ms->permutation =
      realloc(ms->permutation, ms->num_functions * sizeof(size_t));

  if (ms->permutation == NULL) {
    ms->errorno = E_INTERNAL_RANDOMNESS__AI__MALLOC;
    ms->additional_info = strerror(errno);
    return 1;
  }

  for (size_t i = 0; i < ms->num_functions; i++) {
    ms->permutation[i] = i;
  }
  return 0;
};
const size_t DEFAULT_CODE_SIZE = 60000;
static int create_new_function(measuresuite_t ms, enum load_type type,
                               size_t code_size_bytes) {

  // check size and allocate more if needed
  if (ms->size_functions <= ms->num_functions) {
    ms->size_functions *= 2;
    if (realloc_or_fail(ms, (void **)&ms->functions,
                        ms->size_functions * sizeof(struct function_tuple))) {
      return 1;
    }
  }

  // convenience pointer to the new tuple
  struct function_tuple *new = &ms->functions[ms->num_functions];

  new->type = type;

  // initialize the memory for arith_result
  init_arithmetic_results(ms, new);

  // if we need the 'code' segment, initialize that memory
  if (type == ELF || type == BIN || type == ASM) {

    new->code_size_bytes =
        code_size_bytes == 0 ? DEFAULT_CODE_SIZE : code_size_bytes;
    if (map_rwx(ms, (void **)&new->code, new->code_size_bytes)) {
      return 1;
    }
  }

  // Because we don't have any batch_size yet.
  new->cycle_results = NULL;

#ifdef USE_ASSEMBLYLINE
  new->chunks = 0;

  if (type == ASM) {
    // create asm instance
    new->al = asm_create_instance(new->code, (int)new->code_size_bytes);
  } else {
    new->al = NULL;
  }
#else
  if (type == ASM) {
    ms->errorno = E_NO_ASSEMBLYLINE;
    return 1;
  }

#endif

  // specify that we have a new one now
  ms->num_functions += 1;
  reset_permutaions(ms);
  return 0;
}

int unload(measuresuite_t ms, size_t id) {

  struct function_tuple *fct = &ms->functions[id];

  free(fct->arithmetic_results);
  fct->arithmetic_results = NULL;

  free(fct->cycle_results);
  fct->cycle_results = NULL;

  int ret = 0;
  switch (fct->type) {
  case SHARED_OBJECT:
    ret = so_unload_file(ms, fct);
    break;
  case ASM:
#if USE_ASSEMBLYLINE
    if (fct->al == NULL || asm_destroy_instance(fct->al)) {
      ms->errorno = E_LOAD__AL_FREE;
      ret = 1;
    }
    fct->al = NULL;
    __attribute__((fallthrough));
#endif
  case BIN:
  case ELF:
    unmap(ms, fct->code, fct->code_size_bytes);
    fct->code_size_bytes = 0;
  }

  ms->num_functions--;
  reset_permutaions(ms);
  return ret;
}

static int load_file_so(measuresuite_t ms, enum load_type type,
                        const char *filename, const char *symbol, int *id) {
  if (*id == -1) {
    if (create_new_function(ms, type, 0)) {
      return 1;
    }
    *id = (int)ms->num_functions - 1;
  }
  struct function_tuple *new = &ms->functions[*id];
  if (so_load_file(ms, new, filename) || so_load_symbol(ms, new, symbol)) {
    return 1;
  }
  return 0;
}

int load_file(measuresuite_t ms, enum load_type type, const char *filename,
              const char *symbol, int *id) {

  if (type == SHARED_OBJECT) {
    return load_file_so(ms, type, filename, symbol, id);
  }

  size_t size = 0;
  if (filesize(ms, filename, &size)) {
    return 1;
  }

  if (*id == -1) {
    /*
   size should suffice for
   - ASM, as a string instructions are typically longer than the encoded
   version
   - BIN (its equal anyway)
   - ELF, as we'd need less because we skip the header stuff
   */
    if (create_new_function(ms, type, size)) {
      return 1;
    }
    *id = (int)ms->num_functions - 1;
  }
  struct function_tuple *fct = &ms->functions[*id];
  /** make sure we got enough space in case we are re-using */
  if (fct->code_size_bytes < size) {
    if (realloc_rwx_or_fail(ms, fct->code, fct->code_size_bytes, size)) {
      return 1;
    }
    fct->code_size_bytes = size;
  }

  switch (type) {
  case ASM: {
#ifdef USE_ASSEMBLYLINE
    if (asm_assemble_file_counting_chunks(fct->al, (char *)filename,
                                          (int)ms->chunk_size, &fct->chunks)) {
      ms->errorno = E_LOAD__ASM_FILE;
      return 1;
    }
    return 0;
#else
    ms->errorno = E_NO_ASSEMBLYLINE;
    return 1;
#endif
  }

  case BIN:
    return filecopy(ms, fct->code, size, filename);

  case ELF:
    return elf_load_symbol(ms, fct->code, size, filename, symbol);

  default:
    return 1;
  }

  return 0;
}

int load_data(measuresuite_t ms, enum load_type type, const uint8_t *data,
              size_t data_len, const char *symbol, int *id) {
  if (type == SHARED_OBJECT) {
    ms->errorno = E_INVALID_INPUT__SO_FROM_MEMORY;
    return 1;
  }

  if (*id == -1) {
    if (create_new_function(ms, type, data_len)) {
      return 1;
    }
    *id = (int)ms->num_functions - 1;
  }

  struct function_tuple *fct = &ms->functions[*id];
  /** make sure we got enough space in case we are re-using */
  if (fct->code_size_bytes < data_len) {
    if (realloc_rwx_or_fail(ms, fct->code, fct->code_size_bytes, data_len)) {
      return 1;
    }
    fct->code_size_bytes = data_len;
  }

  switch (type) {
  case ASM: {
#ifdef USE_ASSEMBLYLINE
    if (asm_assemble_string_counting_chunks(
            fct->al, (char *)data, (int)ms->chunk_size, &fct->chunks)) {
      ms->errorno = E_LOAD__ASM_DATA;
      return 1;
    }
    return 0;
#else
    ms->errorno = E_NO_ASSEMBLYLINE;
    return 1;
#endif
  }

  case BIN: {
    memcpy(fct->code, data, data_len);
    return 0;
  }

  case ELF:
    return elf_load_symbol_mem(ms, fct->code, fct->code_size_bytes, data,
                               symbol);

  default:
    return 1;
  }

  ms->errorno = E_SUCCESS;
  return 0;
}
