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
#include <stdlib.h>

const char lib[] = {"./liball_lib.so"};
const char symbol[] = {"add_two_numbers"};

int main() {
  char fa[] = {"mov rax, [rsi]\n"
               "add rax, [rdx]\n"
               "mov [rdi], rax\n"
               "ret\n"};

  const int num_batches = 2;
  const int batch_size = 2;

  // INIT
  const int arg_width = 1;
  const int arg_num_in = 2;
  const int arg_num_out = 1;
  const int chunksize = 0;
  const uint64_t bounds[] = {-1};
  measuresuite_t ms = NULL;
  if (ms_measure_init(&ms, arg_width, arg_num_in, arg_num_out, chunksize,
                      bounds, lib, symbol)) {
    error_handling_helper_template_str(ms,
                                       "Failed to measure_init. Reason: %s.");
    return 1;
  }

  // measure
  if (ms_measure(ms, fa, fa, batch_size, num_batches)) {
    error_handling_helper_template_str(ms, "Failed to measure. Reason: %s.");
    return 1;
  }
  const char *output = NULL;
  size_t jsonlen = 0;
  ms_getJson(ms, &output, &jsonlen);
  printf("%s\n", output);

  // END
  if (ms_measure_end(ms)) {
    error_handling_helper_template_str(ms,
                                       "Failed to measure_end. Reason: %s.");
    return 1;
  }

  return 0;
}
