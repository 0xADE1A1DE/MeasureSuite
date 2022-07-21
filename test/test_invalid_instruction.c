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

const char lib[] = {"./liball_lib.so"};
const char symbol[] = {"increment"};

int main() {
  // convenience pointer
  void (*err)(measuresuite_t, const char *) =
      error_handling_helper_template_str;

  char fa[] = {"mov rax, [rsi]\n"
               "invlid rax, 2\n"
               "mov [rdi], rax\n"
               "ret\n"};
  int num_batches = 2;
  int batch_size = 2;

  // INIT
  int arg_width = 1;
  int arg_num_in = 1;
  int arg_num_out = 1;
  int chunksize = 0;
  uint64_t bounds[] = {-1};

  measuresuite_t ms = NULL;
  if (ms_measure_init(&ms, arg_width, arg_num_in, arg_num_out, chunksize,
                      bounds, lib, symbol)) {
    err(ms, "Failed to measure_init. Reason: %s.");
    return 1;
  }

  // measure
  if (ms_measure(ms, fa, fa, batch_size, num_batches)) {
    /** this is expected this time. */

    // END
    if (ms_measure_end(ms)) {
      err(ms, "Failed to measure_end. Reason: %s.");
      return 1;
    }
    return 0;
  }

  fprintf(stderr, "assemblyline should have failed");
  return 1;
}
