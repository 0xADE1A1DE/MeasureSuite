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

#include <assemblyline.h> // asm_get_code
#include <errno.h>        // errno
#include <stdio.h>        // snprintf
#include <stdlib.h>       // alloc / size_t
#include <string.h>       // memset / strerror

#include "checker.h" // check
#include "evaluator.h"
#include "randomizer.h" // randomize / get_random_byte
#include "struct_measuresuite.h"
#include "timer.h" // ms_start/ms_stop_timer / ms_current_timestamp

static void run_batch(struct measuresuite *ms, uint64_t *count, uint64_t *out,
                      void (*func)(uint64_t *o, ...));

static int realloc_or_fail(struct measuresuite *ms, void **dest,
                           size_t new_len) {
  *dest = realloc(*dest, new_len);
  if (*dest == NULL) {
    ms->errorno = E_INTERNAL_MEASURE__AI__ALLOC;
    ms->additional_info = strerror(errno);
    return 1;
  }
  return 0;
}

int run_measurement_lib_only(struct measuresuite *ms) {

  // init arith_result mem;
  // setting for each measurement to 0
  memset(ms->arithmetic_results, 0,
         ms->arithmetic_results_size_u64 * sizeof(uint64_t));

  // init cyclecount mem
  memset(ms->cycle_results, 0, ms->cycle_results_size_u64 * sizeof(uint64_t));
  size_t count_c = 0;

  // START MEASUREMENT
  do {
    if (randomize(ms) != 0) {
      return 1;
    }

    run_batch(ms, ms->cycle_results + count_c, ms->arithmetic_results,
              ms->function_check);

    count_c++;

    // if we fall out of space
    if (count_c >= ms->cycle_results_size_u64) {
      // new size, *2 backoff
      ms->cycle_results_size_u64 *= 2;

      if (realloc_or_fail(ms, (void **)&(ms->cycle_results),
                          ms->cycle_results_size_u64 * sizeof(uint64_t))) {
        return 1;
      }
      // memset'ing is done as init in recursive step
      return run_measurement(ms);
    }

    // as long we did not finish num_batches
  } while (count_c < (size_t)ms->num_batches);

  return 0;
}

static int generate_json_from_measurement_results(
    struct measuresuite *ms, uint64_t start_time, int check_result,
    size_t count_a, size_t count_c, uint64_t cycl_res_test[],
    uint64_t cycl_res_chk[]) {
  char *json = ms->json;
  char *json_end = ms->json + ms->json_len;
  json += snprintf(json, ms->json_len,
                   "{\"stats\":"
                   "{\"countA\":%lu,"
                   "\"countB\":%lu,"
                   "\"chunksA\":%d,"
                   "\"chunksB\":%d,"
                   "\"batchSize\":%lu,"
                   "\"numBatches\":%d,"
                   "\"runtime\":%" PRIu64 ","
                   "\"runOrder\":\"%s\","
                   "\"checkResult\":%s},"
                   "\"times\":[",
                   count_a, count_c - count_a, ms->chunks_A, ms->chunks_B,
                   ms->batch_size, ms->num_batches,
                   ms_current_timestamp() - start_time, ms->run_order,
                   check_result ? "false" : "true");
  const int max_print_len = 48;
  // each iteration we append "[-1,LU,LU],\0", which has a maxlen of strlen(LU)
  // -= 20; strlen("[-1,LU,LU],") == 7+2*20==47 + NUL-char
  for (size_t idx = 0; idx < count_c; idx++) {
    if (max_print_len + json > json_end) {
      ms->json_len *= 2;                                 // double-backoff
      long old_len_actual = (long)json - (long)ms->json; // like:strlen

      if (realloc_or_fail(ms, (void **)&(ms->json), ms->json_len))
        return 1;

      // update local pointers
      json = ms->json + old_len_actual;
      json_end = ms->json + ms->json_len;
      memset(json, '\0', json_end - json); // and zero the rest
    }
    char c = ms->run_order[idx];
    // print out the results in json-format, using -1 as the 'no
    // measurement'-placeholder
    const char *tpl = c == 'a' ? "[%" PRIu64 ",-1,%" PRIu64 "],"
                               : "[-1,%" PRIu64 ",%" PRIu64 "],";

    json += snprintf(json, max_print_len, tpl, cycl_res_test[idx],
                     cycl_res_chk[idx]);
  }
  // finalise json, overwriting the last comma
  snprintf(json - 1, 3, "]}");
  return 0;
}

int run_measurement(struct measuresuite *ms) {

  // getting pointers
  void *function_A = asm_get_code(ms->al_A);
  void *function_B = asm_get_code(ms->al_B);

  // init arith_result mem; setting for each measurement to 0
  // size:|arg_width*so(u64)*num_arg_out     arg_width*so(u64*num_arg_out)
  //      +--------------------------------+------------------------------+
  // ref: |    arith_res_test              |        arith_res_chk         |
  //      +--------------------------------+------------------------------+
  memset(ms->arithmetic_results, 0,
         ms->arithmetic_results_size_u64 * sizeof(uint64_t));
  uint64_t *arith_res_tst = ms->arithmetic_results;
  uint64_t *arith_res_chk =
      ms->arithmetic_results + ms->arg_width * ms->num_arg_out;

  // init cyclecount mem
  memset(ms->cycle_results, 0, ms->cycle_results_size_u64 * sizeof(uint64_t));
  size_t count_a = 0;
  size_t count_c = 0;
  // allocate results arrays for a and b - runs, each maxruns long
  // assume, runs == 2;  max_runs == 4; will allocate 16 elements.
  // 4 for A, 4 for B, 8 for checking each of those
  // [ABBABABB    | CCCCC  ]
  // a start the start
  uint64_t *cycl_res_tst = ms->cycle_results;
  // second half for c
  uint64_t *cycl_res_chk = ms->cycle_results + ms->cycle_results_size_u64 / 2;

  // init run_order mem (see in measure_helper, basically since we dont save 'c'
  // we only need half as much + NUL)
  memset(ms->run_order, 0, (ms->cycle_results_size_u64 / 2 + 1) * sizeof(char));

  // init result indicator
  int check_result = 0;

  // START MEASUREMENT
  uint64_t start_time = ms_current_timestamp();

  do {
    if (randomize(ms) != 0) {
      return 1;
    }

    uint8_t rand_byte = 0x00;

    if (get_random_byte(ms, &rand_byte)) {
      return 1;
    }

    unsigned char run_a = rand_byte & 0x01;

    const char char_b = 'b';
    ms->run_order[count_c] = (char)((uint8_t)char_b - (uint8_t)run_a);
    // because count_c is incremented everytime, we can use it as an index for
    // runorder as well. and since run_order was \0ed, it is always a perfect
    // valid string.

    void(*f) = run_a ? function_A : function_B;

    run_batch(ms, cycl_res_tst + count_c, arith_res_tst, f);
    count_a += run_a;

    run_batch(ms, cycl_res_chk + count_c, arith_res_chk, ms->function_check);
    count_c++;

    // check
    check_result =
        check(ms->arg_width * ms->num_arg_out, arith_res_chk, arith_res_tst);

    // if it failed
    if (check_result) {
      break;
    }

    int repeat_measurement = 0;
    // if we fall out of space
    if (count_c >= ms->cycle_results_size_u64 / 2) {
      // new size, *2 backoff
      ms->cycle_results_size_u64 *= 2;

      if (realloc_or_fail(ms, (void **)&(ms->cycle_results),
                          ms->cycle_results_size_u64 * sizeof(uint64_t))) {
        return 1;
      }
      repeat_measurement = 1;
    }

    if (count_c >= ms->run_order_size_bytes / 2) {

      // new size, *2 backoff
      ms->run_order_size_bytes *= 2;

      if (realloc_or_fail(ms, (void **)&(ms->run_order),
                          (ms->run_order_size_bytes + 1) * sizeof(char)))
        return 1;
      repeat_measurement = 1;
    }

    if (repeat_measurement) {
      // memset'ing is done as init in recursive step
      return run_measurement(ms);
    }

    // as long as not both functions has been run for arg-runs amounts
  } while (count_a < (size_t)ms->num_batches ||
           count_c - count_a < (size_t)ms->num_batches);

  int json_generation_failed = generate_json_from_measurement_results(
      ms, start_time, check_result, count_a, count_c, cycl_res_tst,
      cycl_res_chk);

  if (json_generation_failed) {
    return 1;
  }

  return 0;
}


static void run_batch(struct measuresuite *ms, uint64_t *count, uint64_t *out,
                      void (*func)(uint64_t *o, ...)) {

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
  uint64_t *a4 = NULL;
  uint64_t *a5 = NULL;

  if (ms->num_arg_out == 2) {
    // shift them all one
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
  }

  uint64_t start_time = 0;
  ms_start_timer(&start_time);
  /** while (bs--) */
  /**   func(a0, a1, a2, a3, a4, a5); */

  for (; bs > 0;) {
    func(a0, a1, a2, a3, a4, a5);
    bs--;
  }

  *count = ms_stop_timer(start_time);
}
