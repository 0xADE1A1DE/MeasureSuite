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

#ifndef STRUCT_MEASURESUITE_H
#define STRUCT_MEASURESUITE_H

#include "ms_error.h"
#ifndef NO_AL
#include <assemblyline.h>
#endif
#include <inttypes.h>
#include <stdlib.h>

struct measuresuite {
  // input vars (provided "on_init")
  int arg_width, num_arg_in, num_arg_out, chunk_size;
  uint64_t *
      bounds; // array of length arg_width and prodives bitmasks. Defaults to -1

  // how many measurements are done at least for function_A / B
  size_t num_batches;

  // how many times function_A/B is called in a row resulting in one measurement
  size_t batch_size;

  // this is the output json, which is being built after measurement is done,
  // alloc'd on init, realloced on demand in measurement
  char *json;
  // is is the length of the allocated space at *json (not the non-NUL-chars
  // use strlen for that.)
  size_t json_len;

  // they are pointers to input. For the functions_{A,B,Check}
  // alloc'd on init
  uint64_t *random_data;
  size_t random_data_size_bytes; // how many bytes are allocated at *random_data
  int random_data_fd; // filedescriptor from which new random data is being
                      // read.

  // pointer to allocated memory to store the arithmetic_results for
  // function_A/B and check.
  uint64_t *arithmetic_results;
  size_t arithmetic_results_size_u64;

  // the cycles are measures in 64-bit uints
  // alloc'd on init, realloced on demand in measurement
  uint64_t *cycle_results;
  size_t cycle_results_size_u64; // size in elements of size uint64_t
  char *run_order;
  size_t run_order_size_bytes;

  // function_check (functionptr)
  void *function_check;
  // handle for lib_check_functions_handle
  void *lib_check_functions_handle;

  // handle to assemblers
  assemblyline_t al_A;
  assemblyline_t al_B;

  // amount of chunks
  int chunks_A;
  int chunks_B;

  // holds the last error number
  ERROR_NUMBER errorno;
  char *additional_info;
};

#endif
