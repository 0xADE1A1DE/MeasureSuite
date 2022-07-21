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

#include "helper.h"
#include <measuresuite.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

int main() {
  // convenience pointer
  void (*err)(measuresuite_t, const char *) =
      error_handling_helper_template_str;

  //
  char fa[] = {"mov rax, [rsi]; *i0\n"
               "add rax, 1; *i0+1\n"
               "mov [rdi], rax; *o0 <-\n"

               "mov rax, [rsi + 0x08]; *i0+1\n"
               "add rax, 1; *i0+1 + 1\n"
               "mov [rdi + 0x08], rax; *o0 + 1 <-\n"

               "mov rax, [rsi + 0x10 ]; *i + 2\n"
               "add rax, 1; *i + 2 + 1\n"
               "mov [rdi + 0x10 ], rax; *o + 2 <-\n"

               "ret\n"};
  const int num_batches = 10;
  const int batch_size = 20;

  // INIT
  const int arg_width = 3;
  const int arg_num_in = 1;
  const int arg_num_out = 1;
  const int chunksize = 0;
  const uint64_t bounds[] = {-1, -1, -1};
  measuresuite_t ms = NULL;
  if (ms_measure_init(&ms, arg_width, arg_num_in, arg_num_out, chunksize,
                      bounds, "./liball_lib.so", "array_width_three_add")) {
    err(ms, "Failed to measure_init. Reason: %s.");
    return 1;
  }

  // measure
  if (ms_measure(ms, fa, fa, batch_size, num_batches)) {
    err(ms, "Failed to measure. Reason: %s.");
    return 1;
  }
  const char *output = NULL;
  size_t jsonlen = 0;
  ms_getJson(ms, &output, &jsonlen);
  printf("%s\n", output);

  // Require to have true in the string but not false
  if (strstr(output, "true") == NULL && strstr(output, "false") != NULL) {
    fprintf(stderr, "should have been a correct result\n");
    ms_measure_end(ms);
    return 1;
  }
  // END
  if (ms_measure_end(ms)) {
    err(ms, "Failed to measure_end. Reason: %s.");
    return 1;
  }
  return 0;
}
