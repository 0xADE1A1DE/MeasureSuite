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

#ifdef USE_ASSEMBLYLINE
#include <assemblyline.h> // asm_get_code
#endif
#include "alloc_helper.h"        // realloc_or_fail
#include "checker.h"             // check
#include "evaluator.h"           // own
#include "randomizer.h"          // randomize
#include "struct_measuresuite.h" // struct ms; struct function_tuple
#include "timer.h"               // ms_{start,stop}_timer / ms_current_timestamp
#include <stdio.h>               // snprintf
#include <stdlib.h>              // alloc / size_t
#include <string.h>              // memset / strerror

static void run_batch(struct measuresuite *ms, struct function_tuple *t,
                      uint64_t *count);

#ifndef NO_AL
static int generate_json_from_measurement_results(struct measuresuite *ms,
                                                  uint64_t start_time,
                                                  size_t check_result) {
  unsigned long delta_in_seconds = ms_current_timestamp() - start_time;
  char *json = ms->json;
  char *json_end = ms->json + ms->json_len;

  json += snprintf(json, ms->json_len,
                   "{\"stats\":"
                   "{"
                   "\"numFunctions\":%" PRIu64 ","
                   "\"runtime\":%" PRIu64 "," // in seconds
                   "\"incorrect\":%" PRIu64
                   "}," // if 0, ok, otherwise the index of which function is
                        // incorrect to the previous one.
                   "\"functions\":[",
                   ms->num_functions, delta_in_seconds, check_result);

  // print function meta data
  for (size_t i = 0; i < ms->num_functions; i++) {
    struct function_tuple *t = &ms->functions[i];
    switch (t->type) {
    case ASM:
      json +=
          snprintf(json, json - json_end,
                   "{\"type\":\"ASM\", \"chunks\":%" PRIi32 "},", t->chunks);
      break;
    case BIN:
      json += snprintf(json, json - json_end, "{\"type\":\"BIN\"},");
      break;
    case ELF:
      json += snprintf(json, json - json_end, "{\"type\":\"ELF\"},");
      break;
    case SHARED_OBJECT:
      json += snprintf(json, json - json_end, "{\"type\":\"SHARED_OBJECT\"},");
      break;
    }
  }
  // overwrite comma
  json--;
  json += snprintf(json, json - json_end, "],\"cycles\":[");

  // print cycles
  for (size_t i = 0; i < ms->num_functions; i++) {
    struct function_tuple *t = &ms->functions[i];
    json += snprintf(json, json - json_end, "[");
    for (size_t run_i = 0; run_i < ms->num_batches; run_i++) {
      json += snprintf(json, json - json_end, "%" PRIu64 ",",
                       t->cycle_results[run_i]);
    }
    // overwrite comma
    json--;
    json += snprintf(json, json - json_end, "],[");
  }
  // overwrite comma and last [
  json -= 2;
  json += snprintf(json, json - json_end, "]}");

  if (json - json_end <= 0) {
    // we did not have enough space.

    // enlarge
    ms->json_len *= 2;
    if (realloc_or_fail(ms, (void **)&(ms->json), ms->json_len)) {
      return 1;
    }

    // and try again recursively
    return generate_json_from_measurement_results(ms, start_time, check_result);
  }

  return 0;
}

int run_measurement(struct measuresuite *ms) {

  // init result indicator
  size_t check_result = 0;
  if (init_cycle_results(ms)) {
    return 1;
  };

  // START MEASUREMENT
  uint64_t start_time = ms_current_timestamp();

  for (size_t batch_i = 0; batch_i < ms->num_batches; batch_i++) {
    // will shuffle the perm-array
    if (randomize(ms) != 0) {
      return 1;
    }

    // for as many functions as we need to measure
    for (size_t func_i = 0; func_i < ms->num_functions; func_i++) {

      // get the function to measure
      size_t function_index = ms->permutation[func_i];
      struct function_tuple *t = &ms->functions[function_index];

      // measure
      run_batch(ms, t, &t->cycle_results[batch_i]);
    }

    if (ms->enable_check) {

      for (size_t func_i = 1; func_i < ms->num_functions; func_i++) {

        // get the tuple and the previous
        struct function_tuple *t = &ms->functions[func_i];
        struct function_tuple *prev = &ms->functions[func_i - 1];

        // check
        if (check(ms->arg_width * ms->num_arg_out, t->arithmetic_results,
                  prev->arithmetic_results)) {
          check_result = func_i;
          break;
        };
      }
    }
  }

  int json_generation_result_code =
      generate_json_from_measurement_results(ms, start_time, check_result);

  if (json_generation_result_code) {
    return 1;
  }

  return 0;
}

#endif

static void run_batch(struct measuresuite *ms, struct function_tuple *t,
                      uint64_t *count) {

  uint64_t *out = t->arithmetic_results;
  // we always call the function with three in-arguments. It itself will then
  // take which ever it needs. However, the positon of the in-args is dependent
  // on the num out args, thus the switch
  size_t bs = ms->batch_size;
  int w = ms->arg_width;

  // this is the initial config for the case that we have one out-variable
  uint64_t *a0 = out;
  uint64_t *a1 = ms->random_data;
  uint64_t *a2 = ms->random_data + w;
  uint64_t *a3 = ms->random_data + 2 * w;
  uint64_t *a4 = ms->random_data + 3 * w;
  uint64_t *a5 = ms->random_data + 4 * w;

  if (ms->num_arg_out == 1) {
    // do nothing, stay with default
  } else if (ms->num_arg_out == 2) {
    // shift them all one
    a5 = a4;
    a4 = a3;
    a3 = a2;
    a2 = a1;
    // and add the new out
    a1 = out + w;
  } else if (ms->num_arg_out == 3) {
    a5 = a3;
    a4 = a2;
    a3 = a1;
    a2 = out + 2 * w;
    a1 = out + w;
  } else if (ms->num_arg_out == 4) {
    a5 = a2;
    a4 = a1;
    a3 = out + 3 * w;
    a2 = out + 2 * w;
    a1 = out + w;
  } else {
    a5 = a1;
    a4 = out + 4 * w;
    a3 = out + 3 * w;
    a2 = out + 2 * w;
    a1 = out + w;
  }

  uint64_t start_time = 0;
  ms_start_timer(&start_time);
  void (*func)(uint64_t * o, ...) = t->code;
  for (; bs > 0;) {
    func(a0, a1, a2, a3, a4, a5);
    bs--;
  }

  *count = ms_stop_timer(start_time);
}
