/**
 * Copyright 2022 University of Adelaide
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef NO_AL
#include <assemblyline.h>
#endif
#include <measuresuite.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "evaluator.h"
#include "measure_helper.h"
#include "ms_error_description.h"
#include "randomizer.h"
#include "struct_measuresuite.h"
#include "timer.h"

// set static variables
int ms_measure_init(measuresuite_t *dest_ms, int arg_width, int num_arg_in,
                    int num_arg_out, int chunk_size, const uint64_t *bounds,
                    const char *lib_check_functions_filename,
                    const char *check_function_symbolname) {

  measuresuite_t ms = calloc(1, sizeof(struct measuresuite));
  *dest_ms = ms;

  // validate and set
  if (arg_width < 1) {
    ms->errorno = E_INVALID_INPUT__ARG_WIDTH;
    return 1;
  }
  ms->arg_width = arg_width;

  if (bounds == NULL) {
    ms->errorno = E_INVALID_INPUT__BOUNDS_NULL;
    return 1;
  }
  ms->bounds = calloc(ms->arg_width, sizeof(uint64_t));
  memcpy(ms->bounds, bounds, ms->arg_width * sizeof(uint64_t));
  // could tests access here, but if its not an proper array, then the
  // measure-call will SIGSEGV

  if (num_arg_in < 1 || num_arg_in > 3) {
    ms->errorno = E_INVALID_INPUT__NUM_ARG_IN;
    return 1;
  }
  ms->num_arg_in = num_arg_in;

  if (num_arg_out < 1 || num_arg_out > 3) {
    ms->errorno = E_INVALID_INPUT__NUM_ARG_OUT;
    return 1;
  }
  ms->num_arg_out = num_arg_out;

  if (chunk_size < 0) {
    ms->errorno = E_INVALID_INPUT__CHUNK_SIZE;
    return 1;
  }
  ms->chunk_size = chunk_size;

  // set some defaults to allocate some space
  // You usually want num_batches to be odd, and batch_size depends on the
  // size of the function. Longer functions require smaller batches and vice
  // versa. Both however, depend on the frequency of the CPU. You may do a
  // statiscial test and see how confident those numbers are
  const int default_num_batches = 101;
  ms->num_batches = default_num_batches;
  const int default_batch_size = 20;
  ms->batch_size = default_batch_size;

  if (init_random(ms)) {
    return 1;
  }

  if (init_measure_scratch(ms)) {
    return 1;
  }

  if (load_check_file(ms, lib_check_functions_filename)) {
    return 1;
  }

  if (load_check_function(ms, check_function_symbolname)) {
    return 1;
  }

  ms_init_timer();

#ifndef NO_AL
  ms->al_A = asm_create_instance(NULL, 0);
  ms->al_B = asm_create_instance(NULL, 0);

  // For now, set chunk size to zero. the provided chunk size is
  // used for the chunk break counting.
  asm_set_chunk_size(ms->al_A, 0);
  asm_set_chunk_size(ms->al_B, 0);

  asm_set_debug(ms->al_A, false);
  asm_set_debug(ms->al_B, false);

  asm_set_all(ms->al_A, SMART);
  asm_set_all(ms->al_B, SMART);
#endif

  ms->errorno = E_SUCCESS;
  return 0;
}

#ifndef NO_AL
int ms_measure(measuresuite_t ms, char *functionA, char *functionB,
               int batch_size, int num_batches) {
  asm_set_offset(ms->al_A, 0);
  asm_set_offset(ms->al_B, 0);

  ms->num_batches = num_batches;
  ms->batch_size = batch_size;

  // assembling
  if (asm_assemble_string_counting_chunks(ms->al_A, functionA, ms->chunk_size,
                                          &ms->chunks_A)) {
    ms->errorno = E_INVALID_INPUT__ASM_FUNCTION_A;
    return 1;
  }
  if (asm_assemble_string_counting_chunks(ms->al_B, functionB, ms->chunk_size,
                                          &ms->chunks_B)) {
    ms->errorno = E_INVALID_INPUT__ASM_FUNCTION_B;
    return 1;
  }

  // running measurement
  if (run_measurement(ms) != 0) {
    return 1;
  }

  ms->errorno = E_SUCCESS;
  return 0;
}
#endif

int ms_measure_lib_only(measuresuite_t ms, size_t batch_size, int num_batches) {
  ms->num_batches = num_batches;
  ms->batch_size = batch_size;

  // running measurement
  if (run_measurement_lib_only(ms) != 0) {
    return 1;
  }

  ms->errorno = E_SUCCESS;
  return 0;
}

void ms_get_libcycles(measuresuite_t ms, uint64_t **dest) {
  *dest = ms->cycle_results;

  ms->errorno = E_SUCCESS;
}

/**
 * frees memory used for randomness and scratches
 * frees memory and mmaps
 * returns 0 on success, 1 in case of failure
 */
int ms_measure_end(measuresuite_t ms) {

#ifndef NO_AL
  // destroying the assemblers.
  if (ms->al_A == NULL || asm_destroy_instance(ms->al_A)) {
    if (ms->al_A == NULL) {
      printf("ms ->al_A is null. \n");
    }
    ms->errorno = E_INTERNAL_MEASURE__FREE_A;
    return 1;
  }
  if (ms->al_B == NULL || asm_destroy_instance(ms->al_B)) {
    if (ms->al_B == NULL) {
      printf("ms ->al_B is null. \n");
    }
    ms->errorno = E_INTERNAL_MEASURE__FREE_B;
    return 1;
  }
#endif

  // free random data spot
  if (end_random(ms)) {
    return 1;
  }

  if (end_measure_scratch(ms)) {
    return 1;
  }

  unload_check_function(ms);

  free(ms->bounds);
  free(ms);
  return 0;
}

void ms_getJson(measuresuite_t ms, const char **json, size_t *json_len) {
  *json = ms->json;
  *json_len = strlen(*json);
}

const char *ms_str_error(measuresuite_t ms) {
  return get_error_string(ms->errorno);
}

void ms_str_full_error(measuresuite_t ms, char *dest, int len) {
  snprintf(dest, len, "%s Reason: %s\n", get_error_string(ms->errorno),
           ms->additional_info);
}

void ms_p_error(measuresuite_t ms) {
  printf("%s\n", ms_str_error(ms));
  if (ms->additional_info) {
    printf("%s\n", ms->additional_info);
  }
}
