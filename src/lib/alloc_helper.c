#include "alloc_helper.h"
#include "ms_error.h"
#include <errno.h>    // errno
#include <stdlib.h>   // realloc
#include <string.h>   // strerror
#include <sys/mman.h> // mmap...

int realloc_or_fail(struct measuresuite *ms, void **dest, size_t new_len) {
  *dest = realloc(*dest, new_len);

  if (*dest == NULL) {
    ms->errorno = E_INTERNAL_MEASURE__AI__ALLOC;
    ms->additional_info = strerror(errno);
    return 1;
  }

  return 0;
}

int map_rwx(struct measuresuite *ms, void **dest, size_t new_len) {
  *dest = mmap(NULL, new_len, PROT_READ | PROT_WRITE | PROT_EXEC,
               MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
  if (*dest == NULL) {
    ms->errorno = E_INTERNAL_MEASURE__AI__ALLOC;
    ms->additional_info = strerror(errno);
    return 1;
  }

  return 0;
}

int realloc_rwx_or_fail(struct measuresuite *ms, void **dest, size_t old_len,
                        size_t new_len) {
  // not using mremap here, because it may clash with errno (and USE_GNU)
  if (munmap(*dest, old_len)) {
    ms->errorno = E_INTERNAL_MEASURE__AI__ALLOC;
    ms->additional_info = strerror(errno);
    return 1;
  }

  return map_rwx(ms, *dest, new_len);
}

int unmap(struct measuresuite *ms, void **dest, size_t old_len) {
  if (munmap(*dest, old_len)) {
    ms->errorno = E_INTERNAL_MEASURE__AI__ALLOC;
    ms->additional_info = strerror(errno);
    return 1;
  }

  return 0;
}

int init_arithmetic_results(measuresuite_t ms, struct function_tuple *t) {
  /** Arithmetic Results: */
  /** +---------------------------------------------------------+ */
  /** | Arithmetic Res (for first) | Arithmetic Res (for seond) | */
  /** +---------------------------------------------------------+ */
  /**   ^--- #argOut * sizeof(Out)                                */

  /** Arithmetic Res */
  /** +---------------------------------------------------------+ */
  /** |         out1 , out2, ... , out[#numArgOut]              | */
  /** +---------------------------------------------------------+ */
  /**     ^---   out1 * arg_width */

  /** Out1  each sizeof(u64)*/
  /** +---------------------------------------------------------+ */
  /** |         out1[0] , out1[1], ... , out1[#arg_width]       | */
  /** +---------------------------------------------------------+ */

  size_t size = ms->arg_width * ms->num_arg_out * sizeof(uint64_t);

  t->arithmetic_results = malloc(size);

  if (t->arithmetic_results == NULL) {
    ms->errorno = E_INTERNAL_MEASURE__AI__ALLOC;
    ms->additional_info = strerror(errno);
    return 1;
  }

  return 0;
}

int init_cycle_results(struct measuresuite *ms) {

  size_t max_runs = ms->num_batches;

  for (size_t function_i = 0; function_i < ms->num_functions; function_i++) {
    // will shuffle the perm-array
    if ((ms->functions[function_i].cycle_results = malloc(max_runs)) == 0) {
      ms->errorno = E_INTERNAL_MEASURE__AI__ALLOC;
      ms->additional_info = strerror(errno);
      return 1;
    }
  }

  return 0;
}

int init_json(struct measuresuite *ms) {

  const unsigned long char_per_long = 10;
  // every one produces  num_functions long numbers
  const unsigned long char_per_batch = char_per_long * ms->num_functions;

  // every batch produces char_per_batch' chars
  const unsigned long dynamic_length = char_per_batch * ms->num_batches;

  // the static stuff...
  const int len_other_stats = 1025;
  ms->json_len = len_other_stats + dynamic_length;

  ms->json = calloc(ms->json_len, sizeof(char));
  if (ms->json == NULL) {
    ms->errorno = E_INTERNAL_MEASURE__AI__ALLOC;
    ms->additional_info = strerror(errno);
    return 1;
  }

  return 0;
}
