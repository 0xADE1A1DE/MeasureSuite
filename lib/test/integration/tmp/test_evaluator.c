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

// unit-test
#include "helper.h"
#include "src/lib/evaluator.h"
#include <assemblyline.h>
#include <measuresuite.h>
#include <stdio.h>

const int arg_width = 3;

static void mock_check(uint64_t *out1, const uint64_t *arg1) {
  for (int i = 0; i < arg_width; i++) {
    *(out1 + i) = *(arg1 + i);
  }
}

/*
 * shouldnt segfault and return 0
 */
static int should_not_segfault(measuresuite_t *ms) {
  return run_measurement(*ms);
}

int main() {
  measuresuite_t ms = NULL;

  // convenience pointer
  void (*err)(measuresuite_t, const char *) =
      error_handling_helper_template_str;

  // INIT

  int arg_num_in = 1;
  int arg_num_out = 1;
  int chunksize = 0;
  uint64_t bounds[] = {-1, -1, -1};

  /*
   * dont matter, function check will be overwritten.
   * the file and symbol only need to exist
   */
  const char symbol[] = {"add_two_numbers"};
  const char lib[] = {"./liball_lib.so"};
  if (ms_initialize(&ms, arg_width, arg_num_in, arg_num_out, chunksize, bounds)) {
    err(ms, "Failed to init. Reason: %s.");
    return 1;
  }
  if (ms_enable_checking(ms, lib, symbol)) {
    err(ms, "Failed to enable_checking. Reason: %s.");
    return 1;
  }
  ms->function_check = &mock_check;
  ms->batch_size = 2;
  ms->num_batches = 2;

  // destroy old instances
  asm_destroy_instance(ms->al_A);
  asm_destroy_instance(ms->al_B);

  ms->al_A = asm_create_instance(NULL, 0);
  ms->al_B = asm_create_instance(NULL, 0);

  const int assumed_width_per_arg = 50;
  const int bitwidth_of_byte = 8;

  char *s = calloc(arg_width * assumed_width_per_arg, 1);
  for (int i = 0; i < arg_width; i++) {
    sprintf(s, "mov rax, [rsi + %d]\n mov [rdi + %d],rax\n",
            i * bitwidth_of_byte, i * bitwidth_of_byte);
    asm_assemble_str(ms->al_A, s);
    asm_assemble_str(ms->al_B, s);
  }

  asm_assemble_str(ms->al_A, "ret");
  asm_assemble_str(ms->al_B, "ret");

  free(s);

  // TEST
  int res = 0;
  res |= should_not_segfault(&ms);

  res |= ms_terminate(ms);

  return res;
}
