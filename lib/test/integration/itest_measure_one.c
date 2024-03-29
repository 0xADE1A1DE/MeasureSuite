/**
 * Copyright 2023 University of Adelaide
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

static const char symbol[] = {"add_two_numbers"};
static const char file_asm[] = {"./test_data/add_two_numbers.asm"};
static const char file_bin[] = {"./test_data/add_two_numbers.bin"};
static const char file_elf[] = {"./test_data/add_two_numbers.o"};
static const char file_shared_object[] = {"./test_data/add_two_numbers.so"};

static const int arg_width = 1;
static const int arg_num_in = 2;
static const int arg_num_out = 1;
static const int batch_size = 2;
static const int number_of_batches = 10;

static int test_measure_asm_ok() {

  measuresuite_t ms = NULL;

  int id = -1;
  ms_initialize(&ms, arg_width, arg_num_in, arg_num_out);
  ms_load_file(ms, ASM, file_asm, symbol, &id);

  ms_assert_ok(ms_measure(ms, batch_size, number_of_batches));

  ms_assert_ok(ms_terminate(ms));

  return 0;
}

static int test_measure_bin_ok() {

  measuresuite_t ms = NULL;

  int id = -1;
  ms_initialize(&ms, arg_width, arg_num_in, arg_num_out);

  ms_load_file(ms, BIN, file_bin, symbol, &id);
  ms_assert_ok(ms_measure(ms, batch_size, number_of_batches));

  ms_assert_ok(ms_terminate(ms));

  return 0;
}

static int test_measure_elf_ok() {

  measuresuite_t ms = NULL;

  int id = -1;
  ms_initialize(&ms, arg_width, arg_num_in, arg_num_out);

  ms_load_file(ms, ELF, file_elf, symbol, &id);
  ms_assert_ok(ms_measure(ms, batch_size, number_of_batches));

  ms_assert_ok(ms_terminate(ms));

  return 0;
}

static int test_measure_shared_object_ok() {

  measuresuite_t ms = NULL;

  int id = -1;
  ms_initialize(&ms, arg_width, arg_num_in, arg_num_out);

  ms_load_file(ms, SHARED_OBJECT, file_shared_object, symbol, &id);
  ms_assert_ok(ms_measure(ms, batch_size, number_of_batches));

  ms_assert_ok(ms_terminate(ms));

  return 0;
}

int main() {
  SIGILL_SETUP();

  int res = 0;
#if USE_ASSEMBLYLINE
  res |= test_measure_asm_ok();
#endif
  res |= test_measure_bin_ok();
  res |= test_measure_elf_ok();
  res |= test_measure_shared_object_ok();
  return res;
}
