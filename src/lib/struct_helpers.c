
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

#include "struct_helpers.h"
#include "error/description.h"
#include "struct_measuresuite.h"
#include <errno.h>
#include <measuresuite.h>
#include <stddef.h>
#include <string.h>

const size_t max_number_arguments = 6;

int set_argwidth(measuresuite_t ms, unsigned int arg_width) {
  if (arg_width < 1) {
    ms->errorno = E_INVALID_INPUT__ARG_WIDTH;
    return 1;
  }
  ms->arg_width = arg_width;

  return 0;
}

int set_argin(measuresuite_t ms, unsigned int arg_in) {
  if (arg_in < 1 || arg_in >= max_number_arguments) {
    ms->errorno = E_INVALID_INPUT__NUM_ARG_IN;
    return 1;
  }
  ms->num_arg_in = arg_in;
  return 0;
}

int set_argout(measuresuite_t ms, unsigned int arg_out) {
  if (arg_out < 1 || arg_out > max_number_arguments) {
    ms->errorno = E_INVALID_INPUT__NUM_ARG_OUT;
    return 1;
  }
  ms->num_arg_out = arg_out;
  return 0;
}

int validate_num_args(measuresuite_t ms) {
  if (ms->num_arg_out + ms->num_arg_in > max_number_arguments) {
    ms->errorno = E_INVALID_INPUT__NUM_ARG_TOO_LARGE;
    return 1;
  }
  return 0;
}

/**
 * heap allocates an measure struct and sets some default variables.
 * @returns measuresuite_t or NULL on error.
 *
 */
measuresuite_t create_default_ms() {
  measuresuite_t ms = calloc(1, sizeof(struct measuresuite));
  // set some defaults to allocate some space
  // You usually want num_batches to be odd, and batch_size depends on the
  // size of the function. Longer functions require smaller batches and vice
  // versa. Both however, depend on the frequency of the CPU. You may do a
  // statistical test and see how confident those numbers are
  const int default_num_batches = 101;
  ms->num_batches = default_num_batches;
  const int default_batch_size = 20;
  ms->batch_size = default_batch_size;

  // initialize the functions-structure
  const int default_size_functions = 2; // a / b testing
  ms->size_functions = default_size_functions;
  ms->num_functions = 0; // currently, we have none loaded
  ms->functions = calloc(ms->size_functions, sizeof(struct function_tuple));

  if (ms->functions == NULL) {
    ms->errorno = E_INTERNAL_INITIALIZE__ALLOC;
    ms->additional_info = strerror(errno);
    return NULL;
  }

  ms->enable_check = 0;
  ms->bounds = NULL;
  ms->chunk_size = 0;
  ms->errorno = E_SUCCESS;
  ms->random_data_fd = -1;

  return ms;
}

int set_chunk_size(measuresuite_t ms, size_t chunk_size) {
  ms->chunk_size = chunk_size;
  return 0;
}

int set_bounds(measuresuite_t ms, const uint64_t *bounds) {

  if (bounds == NULL) {
    ms->errorno = E_INVALID_INPUT__BOUNDS_NULL;
    return 1;
  }
  if (ms->arg_width <= 0) {
    ms->errorno = E_INVALID_INPUT__ARG_WIDTH;
    return 1;
  }

  ms->bounds = calloc(ms->arg_width, sizeof(uint64_t));
  if (ms->bounds == NULL) {
    ms->errorno = E_INTERNAL_INITIALIZE__ALLOC;
    return 1;
  }
  memcpy(ms->bounds, bounds, ms->arg_width * sizeof(uint64_t));
  // could tests access here, but if its not an proper array, then the
  // measure-call will SIGSEGV
  return 0;
}

int set_num_batches(measuresuite_t ms, unsigned int num_batches) {
  if (num_batches <= 0) {
    ms->errorno = E_INVALID_INPUT__NUM_BATCHES;
    return 1;
  }
  ms->num_batches = num_batches;
  return 0;
}

int set_batch_size(measuresuite_t ms, unsigned int batch_size) {
  if (batch_size <= 0) {
    ms->errorno = E_INVALID_INPUT__BATCH_SIZE;
    return 1;
  }
  ms->batch_size = batch_size;
  return 0;
}
