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

static int test_measure_four_ok() {

  measuresuite_t ms = NULL;

  int ids[] = {-1, -1, -1, -1};
  int pointer = 0;
  ms_assert_ok(ms_initialize(&ms, arg_width, arg_num_in, arg_num_out));

#if USE_ASSEMBLYLINE
  ms_assert_ok(ms_load_file(ms, ASM, file_asm, symbol, ids + pointer++));
#endif
  ms_assert_ok(ms_load_file(ms, SHARED_OBJECT, file_shared_object, symbol,
                            ids + pointer++));
  ms_assert_ok(ms_load_file(ms, BIN, file_bin, symbol, ids + pointer++));
  ms_assert_ok(ms_load_file(ms, ELF, file_elf, symbol, ids + pointer++));

  ms_assert_ok(ms_measure(ms, batch_size, number_of_batches));

  ms_assert_ok(ms_terminate(ms));

  return 0;
}
// 12 bin's
static int test_measure_many_ok() {
  measuresuite_t ms = NULL;

  int ids[] = {
      -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  };
  int pointer = 0;
  ms_initialize(&ms, arg_width, arg_num_in, arg_num_out);

  ms_load_file(ms, BIN, file_bin, symbol, ids + pointer++);
  ms_load_file(ms, BIN, file_bin, symbol, ids + pointer++);
  ms_load_file(ms, BIN, file_bin, symbol, ids + pointer++);
  ms_load_file(ms, BIN, file_bin, symbol, ids + pointer++);
  ms_load_file(ms, BIN, file_bin, symbol, ids + pointer++);
  ms_load_file(ms, BIN, file_bin, symbol, ids + pointer++);
  ms_load_file(ms, BIN, file_bin, symbol, ids + pointer++);
  ms_load_file(ms, BIN, file_bin, symbol, ids + pointer++);
  ms_load_file(ms, BIN, file_bin, symbol, ids + pointer++);
  ms_load_file(ms, BIN, file_bin, symbol, ids + pointer++);
  ms_load_file(ms, BIN, file_bin, symbol, ids + pointer++);
  ms_load_file(ms, BIN, file_bin, symbol, ids + pointer++);

  ms_assert_ok(ms_measure(ms, batch_size, number_of_batches));

  const char *json = NULL;
  size_t len = 0;
  ms_get_json(ms, &json, &len);

  ms_assert(len != 0);
  ms_assert(json != NULL);
  char *pos = strstr(json, "{\"stats\":{\"numFunctions\":12,\"runtime\":");
  assert(pos != NULL);

  ms_assert_ok(ms_terminate(ms));

  return 0;
}

int main() {
  SIGILL_SETUP();
  int res = 0;
  res |= test_measure_four_ok();
  res |= test_measure_many_ok();
  return res;
}
