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

  size_t max_runs = ms->num_batches * RANDOMNESS_MULTIPLIER;

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

static int init_run_order(struct measuresuite *ms) {
  size_t max_runs = ms->num_batches * RANDOMNESS_MULTIPLIER;

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
