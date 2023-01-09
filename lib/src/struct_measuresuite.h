/**
 * Copyright 2023 University of Adelaide
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

#include "error/error.h"  // ERROR_NUMBER
#include "measuresuite.h" // load_type
#include <linux/perf_event.h>
#include <stddef.h>
#include <stdint.h>

#ifdef USE_ASSEMBLYLINE
#include <assemblyline.h>
#endif

#include <inttypes.h> // uint64_t's
#include <stdlib.h>   // size_t

struct function_tuple {

  enum load_type type;

  // actual code
  void *code; // function pointer
  union {
    size_t code_size_bytes; // for when we allcate ourselves (ASM/BIN)
    void *lib_handle;       // dlopen'ed handle
  };

  uint64_t *arithmetic_results;
  uint64_t *cycle_results;

#ifdef USE_ASSEMBLYLINE
  // how many chunk breaks have been observed while assembling with AL
  int chunks;
  // assembler
  assemblyline_t al;
#endif
};

struct measuresuite {
  // details of argument to call the fucntions with
  size_t arg_width, num_arg_in, num_arg_out;

  // array of length arg_width and prodives bitmasks. Defaults to -1
  uint64_t *bounds;

  // to count chunks (if used with AL)
  size_t chunk_size;

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
  size_t random_data_len; // how many uint64_t's are allocated at
                          // *random_data
  int random_data_fd;     // file descriptor from which new random data is being
                          // read.
  size_t *permutation;    // pointing to an array of #num_functions size,
                          // cointaining indexes into the *functions-array

  // // the cycles are measures in 64-bit uints
  // // alloc'd on init, realloced on demand in measurement
  // uint64_t *cycle_results;
  // size_t cycle_results_size_u64; // size in elements of size uint64_t
  // char *run_order;
  // size_t run_order_size_bytes;

  char enable_check : 1;

  // points to the code in memory to execute
  struct function_tuple *functions;
  size_t size_functions; // available function pointers
  size_t num_functions;  // used function pointers

  // holds the last error number
  ERROR_NUMBER errorno;
  char *additional_info;

  // timer
  struct timer_t {
    int fdperf;
    struct perf_event_mmap_page *buf;
    uint64_t (*timer_function)(struct measuresuite *ms);
  } timer;
};

// helper to iterate over all available function
#define FOR_EACH_FUNCTION                                                      \
  for (struct function_tuple *fct = ms->functions;                             \
       fct <= &ms->functions[ms->num_functions - 1]; fct++)

// use it like:
// FOR_EACH_FUNCTION {
// fct->tuple ...
// }

#endif
