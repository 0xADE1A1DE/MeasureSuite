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

const char symbol[] = {"sixparamadd"};
const char lib[] = {"./liball_lib.so"};
int main() {
  // convenience pointer
  void (*err)(measuresuite_t, const char *) =
      error_handling_helper_template_str;

  /** void sixparamadd(uint64_t *o0, uint64_t *o1, uint64_t *o2, uint64_t *i0,
   * uint64_t *i1, uint64_t *i2); */
  char fa[] = {"mov rax, [rcx]; *i0\n"
               "add rax, 1; *i0+1\n"
               "mov [rdi], rax; *o0 <-\n"
               "mov rax, [r8]; *i1\n"
               "add rax, 1; *i1 + 1\n"
               "mov [rsi], rax; *o1 <-\n"
               "mov rax, [r9]; *i2\n"
               "add rax, 1; *i2 + 1\n"
               "mov [rdx], rax; *o2 <-\n"
               "ret\n"};
  const int num_batches = 10;
  const int batch_size = 20;

  // INIT
  const int arg_width = 1;
  const int arg_num_in = 3;
  const int arg_num_out = 3;
  const int chunksize = 0;
  const uint64_t bounds[] = {-1};

  measuresuite_t ms = NULL;
  if (ms_initialize(&ms, arg_width, arg_num_in, arg_num_out, chunksize,
                    bounds)) {
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
  printf("%s\n", output);

  // Require to have true in the string but not false
  if (strstr(output, "true") == NULL && strstr(output, "false") != NULL) {
    fprintf(stderr, "should have been a correct result\n");
    ms_terminate(ms);
    return 1;
  }
  // END
  if (ms_terminate(ms)) {
    err(ms, "Failed to measure_end. Reason: %s.");
    return 1;
  }
  return 0;
}
