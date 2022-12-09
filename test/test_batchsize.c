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
#include <string.h>

const char lib[] = {"./liball_lib.so"};
const char symbol[] = {"increment"};

int main() {
  // convenience pointer
  void (*err)(measuresuite_t, const char *) =
      error_handling_helper_template_str;

  char fa[] = {"mov rax, [rsi]\n"
               "add rax, 1\n"
               "mov [rdi], rax\n"
               "ret\n"};
  const int num_batches = 200;
  const int batch_size = 2;

  // INIT
  const int arg_width = 1;
  const int arg_num_in = 1;
  const int arg_num_out = 1;
  const int chunksize = 0;
  const uint64_t bounds[] = {-1};

  measuresuite_t ms = NULL;
  if (ms_initialize(&ms, arg_width, arg_num_in, arg_num_out, chunksize, bounds)) {
    err(ms, "Failed to init. Reason: %s.");
    return 1;
  }
  if (ms_enable_checking(ms, lib, symbol)) {
    err(ms, "Failed to enable_checking. Reason: %s.");
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

  const char *found = output;
  int num_found = 0;
  while ((found = strchr(found, '[')) != NULL) {
    num_found++;
    found += 1; // and continue searching from the next char.
  };
  printf("num_batches of %d resulted in %d x '[' char.\n", num_batches,
         num_found);

  // END
  if (ms_terminate(ms)) {
    err(ms, "Failed to measure_end. Reason: %s.");
    return 1;
  }
  // numFound must be bigger than 2*num_batches, because each batch produces 2
  // [a,b,c] pairs.
  // if it is smaller (true), return 1;
  return num_found <= 2 * num_batches;
}
