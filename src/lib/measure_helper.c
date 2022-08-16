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

#include <dlfcn.h>  // dlopen
#include <errno.h>  // errno
#include <math.h>   // ceil log10
#include <stdio.h>  // strerror
#include <stdlib.h> // malloc
#include <string.h> // strerror
#include <unistd.h> // access|F_OK...

#include "measure_helper.h"
#include "ms_error.h"

static int init_cycle_results(struct measuresuite *ms);
static int init_arithmetic_results(struct measuresuite *ms);
static int init_run_order(struct measuresuite *ms);
static int init_json(struct measuresuite *ms);

#define RANDOMNESS_MULTIPLIER 4;
// magicnumber. we dont expect the randomness to be 4 times more one then zero.
// for perfect randomness, we would assume an RANDOMNESS_MULTIPLIER = 1;

int load_check_file(struct measuresuite *ms,
                    const char *lib_check_functions_filename) {

  if (access(lib_check_functions_filename, F_OK | X_OK | R_OK) != 0) {
    ms->errorno = E_INVALID_INPUT__LIB_CHECK_FILE_NOT_ACCESSIBLE;
    ms->additional_info = strerror(errno);
    return 1;
  }

  dlerror(); // clear error

  if ((ms->lib_check_functions_handle = dlopen(
           lib_check_functions_filename, RTLD_NOW | RTLD_LOCAL)) == NULL) {
    ms->errorno = E_INTERNAL_MEASURE__AI__DLOPEN;
    ms->additional_info = dlerror();
    return 1;
  }

  return 0;
}

int load_check_function(struct measuresuite *ms,
                        const char *check_function_symbolname) {

  // sanity check  the handle
  if (ms->lib_check_functions_handle == NULL) {
    return 1;
  }

  dlerror(); // clear error
  if ((ms->function_check = dlsym(ms->lib_check_functions_handle,
                                  check_function_symbolname)) == NULL) {
    ms->errorno = E_INTERNAL_MEASURE__AI__DLSYM;
    ms->additional_info = dlerror();
    return 1;
  }

  return 0;
}

int unload_check_function(struct measuresuite *ms) {

  dlerror(); // clear error
  if (dlclose(ms->lib_check_functions_handle) != 0) {
    ms->errorno = E_INTERNAL_MEASURE__AI__DLCLOSE;
    ms->additional_info = dlerror();
    return 1;
  }

  return 0;
}

int init_measure_scratch(struct measuresuite *ms) {
  if (init_cycle_results(ms) || init_arithmetic_results(ms) ||
      init_run_order(ms) || init_json(ms)) {
    return 1;
  }
  return 0;
}

int end_measure_scratch(struct measuresuite *ms) {
  // free allocated memory
  free(ms->arithmetic_results);
  free(ms->run_order);
  free(ms->cycle_results);
  free(ms->json);
  return 0;
}

static int init_cycle_results(struct measuresuite *ms) {

  int max_runs = ms->num_batches * RANDOMNESS_MULTIPLIER;

  // this *4 is because we need 4 times the space. one half for c, one quater of
  // a and b resp.
  ms->cycle_results_size_u64 = max_runs * 4;
  size_t size_cycl_res_b = ms->cycle_results_size_u64 * sizeof(uint64_t);

  ms->cycle_results = malloc(size_cycl_res_b);
  if (ms->cycle_results == NULL) {
    ms->errorno = E_INTERNAL_MEASURE__AI__ALLOC;
    ms->additional_info = strerror(errno);
    return 1;
  }
  return 0;
}

static int init_arithmetic_results(struct measuresuite *ms) {
  /**                                                             */
  /** +---------------------------------------------------------+ */
  /** |                  Arithmetic Results                     | */
  /** +---------------------------------------------------------+ */
  /**   ^-- 2 * ArithmeticResult                                  */

  /** Arithmetic Results: */
  /** +---------------------------------------------------------+ */
  /** | Arithmetic Res (for F_A/B) | Arithmetic Res (for check) | */
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

  ms->arithmetic_results_size_u64 = ms->arg_width * 2 * ms->num_arg_out;
  size_t size_arith_res_b = ms->arithmetic_results_size_u64 * sizeof(uint64_t);

  ms->arithmetic_results = malloc(size_arith_res_b);
  if (ms->arithmetic_results == NULL) {
    ms->errorno = E_INTERNAL_MEASURE__AI__ALLOC;
    ms->additional_info = strerror(errno);
    return 1;
  }
  return 0;
}
static int init_run_order(struct measuresuite *ms) {
  int max_runs = ms->num_batches * RANDOMNESS_MULTIPLIER;

  /**
   * max_runs is a over estimation for each run.
   *  +1 for NUL
   */
  ms->run_order_size_bytes =
      sizeof(char) *
      (1 + max_runs * 2 /* x2 because max_runs a's and max_runs b's */);

  ms->run_order = malloc(ms->run_order_size_bytes);
  if (ms->run_order == NULL) {
    ms->errorno = E_INTERNAL_MEASURE__AI__ALLOC;
    ms->additional_info = strerror(errno);
    return 1;
  }
  return 0;
}
static int init_json(struct measuresuite *ms) {
  // inital json alloc
  // log10 is the usual number of chars, which one measurement takes. we have 3
  // functions to measure for each char in runorder. then we'll add another +1
  // for the runorder itself. the 1025 is the other stats - this should give a
  // pretty good estimation on how many chars we need.
  // int backoff = 1025 + strlen(run_order) * (1 + 3 *
  // ceil(log10(results_c[0]))); assuming, one batch takes less that 999 cycles,
  // which needs three chars 7 chars for '[-1,,],', times 2 for (a or b) and c
  // -> two measurements
  // + 2 for each in runorder
  const int chars_per_empty_entry = 7;
  int char_per_run = 2 + chars_per_empty_entry +
                     (2 * 3 * (int)ceil(log10((double)ms->batch_size)));

  // one measurement is roughly (eval=10) "[-1,9990,9990],"*/
  const int len_other_stats = 1025;
  ms->json_len = len_other_stats + char_per_run * ms->num_batches;
  ms->json = calloc(ms->json_len, sizeof(char));
  if (ms->json == NULL) {
    ms->errorno = E_INTERNAL_MEASURE__AI__ALLOC;
    ms->additional_info = strerror(errno);
    return 1;
  }
  return 0;
}
