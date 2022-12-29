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

int chunk_8();
int chunk_16();

int main() { return chunk_8() || chunk_16(); }

const int arg_width = 1;
const int arg_num_in = 1;
const int arg_num_out = 1;
const int num_batches = 2;
const int batch_size = 2;
const uint64_t bounds[] = {-1};

int chunk_8() {

  char fa_1brk[] = {"mov rax, [rsi]\n" // 3 bytes
                    "inc rax\n"        // 3 bytes
                    "mov [rdi], rax\n" // 3 bytes, chunk break here (@8)
                    "ret\n"};          // 1 bytes
  char fb_0brk[] = {"mov rax, [rsi]\n" // 3 bytes
                    "inc rax\n"        // 3 bytes
                    "clc\n"            // 1 byte
                    "clc\n"            // 1 byte
                                       // chunk ends here. (@8)
                    "mov [rdi], rax\n" // 3 bytes,
                    "ret\n"};          // 1 bytes
                                       // convenience pointer
  void (*err)(measuresuite_t, const char *) =
      error_handling_helper_template_str;

  // INIT
  const int chunksize = 8;
  measuresuite_t ms = NULL;
  if (ms_initialize(&ms, arg_width, arg_num_in, arg_num_out, chunksize, bounds)) {
    err(ms, "Failed to init. Reason: %s.");
    return 1;
  }
  if (ms_enable_checking(ms, lib, symbol)) {
    err(ms, "Failed to enable_checking. Reason: %s.");
    return 1;
  }

  const char *output = NULL;
  size_t jsonlen = 0;
  int result = 0;

  // testing 0brk and 1brk
  if (ms_measure(ms, fa_1brk, fb_0brk, batch_size, num_batches)) {
    err(ms, "Failed to measure. Reason: %s.");
    return 1;
  }
  ms_getJson(ms, &output, &jsonlen);

  if (strstr(output, "chunksA\":1") == NULL ||
      strstr(output, "chunksB\":0") == NULL) {
    printf("the chunks are wrong. they should be chunks{A\":1,B\":0} see json: "
           "%s\n",
           output);
    result = 1;
  }

  // END
  if (ms_terminate(ms)) {
    err(ms, "Failed to measure_end. Reason: %s.");
    return 1;
  }
  return result;
}

int chunk_16() {
  char fa_1brk[] = {"mov rax, [rsi]\n" // 3 bytes
                    "inc rax\n"        // 3 bytes (6)
                    "mov [rdi], rax\n" // 3 bytes,(10)
                    "ret\n"};          // 1 byte (11)

  char fb_3brk[] = {"mov rax, [rsi]\n"      // 3 bytes
                    "inc rax\n"             // 3 bytes (6)
                    "clc\n"                 // 1 byte (7)
                    "mov [rdi], rax\n"      // 3 bytes,(10)
                    "inc rax\n"             // 3 bytes(13)
                    "clc\n"                 // 1 byte(14)
                    "inc rax\n"             // 3 bytes(17) first break (@16)
                    "mulx r8, r9, [rsi]\n"  // 5 bytes(22)
                    "clc\n"                 // 1 byte(23)
                    "clc\n"                 // 1 byte(24)
                    "mulx r8, r9, [rsi]\n"  // 5 bytes(29)
                    "mulx r8, r9, [rsi]\n"  // 5 bytes(34) second break (@32)
                    "mulx r8, r9, [rsi]\n"  // 5 bytes(39)
                    "mulx r9, r10, [rsi]\n" // 5 bytes(44)
                    "mulx r9, r8, [rsi]\n"  // 5 bytes(49) third break (@48)
                    "ret\n"};               // 1bytes
                                            // convenience pointer
  void (*err)(measuresuite_t, const char *) =
      error_handling_helper_template_str;
  // INIT
  const int chunksize = 16;
  measuresuite_t ms = NULL;
  if (ms_initialize(&ms, arg_width, arg_num_in, arg_num_out, chunksize, bounds)) {
    err(ms, "Failed to init. Reason: %s.");
    return 1;
  }
  if (ms_enable_checking(ms, lib, symbol)) {
    err(ms, "Failed to enable_checking. Reason: %s.");
    return 1;
  }

  const char *output = NULL;
  size_t jsonlen = 0;
  int result = 0;

  // testing 0brk (not even one full chunk) and 3brk
  if (ms_measure(ms, fa_1brk, fb_3brk, batch_size, num_batches)) {
    err(ms, "Failed to measure. Reason: %s.");
    return 1;
  }
  ms_getJson(ms, &output, &jsonlen);

  if (strstr(output, "chunksA\":0") == NULL ||
      strstr(output, "chunksB\":3") == NULL) {
    printf("the chunks are wrong. they should be chunks{A\":0,B\":3} see json: "
           "%s\n",
           output);
    result = 1;
  }

  // END
  if (ms_terminate(ms)) {
    err(ms, "Failed to measure_end. Reason: %s.");
    return 1;
  }

  return result;
}
