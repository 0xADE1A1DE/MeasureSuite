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

#include "evaluator.h"           // own
#include "alloc_helper.h"        // init_cycle_results
#include "checker.h"             // check
#include "fisher_yates.h"        // shuffle_permutations
#include "json.h"                // generate_json_from_measurement_results
#include "randomizer.h"          // randomize
#include "struct_measuresuite.h" // struct ms; struct function_tuple
#include "timer.h"               // {start,stop}_timer / current_timestamp
#include <assert.h>              // assert
#include <stdio.h>               // snprintf
#include <stdlib.h>              // alloc / size_t
#include <string.h>              // memset / strerror

static void run_batch(struct measuresuite *ms, struct function_tuple *fct,
                      uint64_t *count) {

  uint64_t *out = fct->arithmetic_results;
  // we always call the function with three in-arguments. It itself will then
  // take which ever it needs. However, the positon of the in-args is dependent
  // on the num out args, thus the switch
  //
  size_t batch_size = ms->batch_size; // working copy
  size_t width = ms->arg_width;

  // this is the initial config for the case that we have one out-variable
  uint64_t *arg0 = out;
  uint64_t *arg1 = ms->random_data;
  uint64_t *arg2 = ms->random_data + width;
  uint64_t *arg3 = ms->random_data + (size_t)2 * width;
  uint64_t *arg4 = ms->random_data + (size_t)3 * width;
  uint64_t *arg5 = ms->random_data + (size_t)4 * width;

  if (ms->num_arg_out == 1) {
    // do nothing, stay with default
  } else if (ms->num_arg_out == 2) {
    // shift them all one
    arg5 = arg4;
    arg4 = arg3;
    arg3 = arg2;
    arg2 = arg1;
    // and add the new out
    arg1 = out + width;
  } else if (ms->num_arg_out == 3) {
    arg5 = arg3;
    arg4 = arg2;
    arg3 = arg1;
    arg2 = out + (size_t)2 * width;
    arg1 = out + width;
  } else if (ms->num_arg_out == 4) {
    arg5 = arg2;
    arg4 = arg1;
    arg3 = out + (size_t)3 * width;
    arg2 = out + (size_t)2 * width;
    arg1 = out + width;
  } else {
    arg5 = arg1;
    arg4 = out + (size_t)4 * width;
    arg3 = out + (size_t)3 * width;
    arg2 = out + (size_t)2 * width;
    arg1 = out + width;
  }

  uint64_t start_time = 0;
  start_timer(ms, &start_time);
  void (*func)(uint64_t * out, ...) = fct->code;
  for (; batch_size > 0;) {
    func(arg0, arg1, arg2, arg3, arg4, arg5);
    batch_size--;
  }

  *count = stop_timer(ms, start_time);
}

int run_measurement(struct measuresuite *ms) {

  // init result indicator
  size_t check_result = 0;
  if (init_cycle_results(ms)) {
    return 1;
  };

  // START MEASUREMENT
  uint64_t start_time = current_timestamp();

  for (size_t batch_i = 0; batch_i < ms->num_batches; batch_i++) {

    if (randomize(ms) != 0 || shuffle_permutations(ms) != 0) {
      return 1;
    }

    // for as many functions as we need to measure
    for (size_t func_i = 0; func_i < ms->num_functions; func_i++) {

      // get the function to measure
      size_t function_index = ms->permutation[func_i];
      struct function_tuple *fct = &ms->functions[function_index];

      // measure
      run_batch(ms, fct, &fct->cycle_results[batch_i]);
    }

    if (ms->enable_check) {

      for (size_t func_i = 1; func_i < ms->num_functions; func_i++) {

        // get the tuple and the previous
        struct function_tuple *fct = &ms->functions[func_i];
        struct function_tuple *prev = &ms->functions[func_i - 1];

        // check
        if (check(ms->arg_width * ms->num_arg_out, fct->arithmetic_results,
                  prev->arithmetic_results)) {
          check_result = func_i;
          break;
        };
      }
    }
  }

  unsigned long elapsed_in_sec = current_timestamp() - start_time;

  if (generate_json(ms, elapsed_in_sec, check_result)) {
    return 1;
  }

  return 0;
}
