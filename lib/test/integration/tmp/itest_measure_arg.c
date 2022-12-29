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

static const int batch_size = 200;
static const int number_of_batches = 10;
const char lib[] = {"./test_data/liball.so"};

static int test_array_width_five_add_pair_ok() {

  const char symbol[] = {"array_width_five_add_pair"};

  char code[] = {"mov rax, [rsi]; *i0 \n"
                 "add rax, [rdx]; *i0 + *i1\n"
                 "mov [rdi], rax; *o0 <-\n"

                 "mov rax, [rsi + 0x08]; *i0+1\n"
                 "add rax, [rdx + 0x08]; *i0+1 + *i1+1\n"
                 "mov [rdi + 0x08], rax; *o0 + 1 <-\n"

                 "mov rax, [rsi + 0x10 ]; *i0 + 2\n"
                 "add rax, [rdx + 0x10 ]; *i0 + 2 + *i1+2\n"
                 "mov [rdi + 0x10 ], rax; *o0 + 2 <-\n"

                 "mov rax, [rsi + 0x18 ]; *i0 + 3\n"
                 "add rax, [rdx + 0x18 ]; *i0 + 3 + *i1+3\n"
                 "mov [rdi + 0x18 ], rax; *o0 + 3 <-\n"

                 "mov rax, [rsi + 0x20 ]; *i0 + 4\n"
                 "add rax, [rdx + 0x20 ]; *i0 + 4 + *i1+4\n"
                 "mov [rdi + 0x20 ], rax; *o0 + 4 <-\n"

                 "ret\n"};
  static const int arg_width = 5;
  static const int arg_num_in = 2;
  static const int arg_num_out = 1;

  measuresuite_t ms = NULL;

  ms_initialize(&ms, arg_width, arg_num_in, arg_num_out);
  ms_set_checking(ms, 1);

  int id = -1;
  ms_assert_ok(
      ms_load_data(ms, ASM, (uint8_t *)code, strlen(code), symbol, &id));
  ms_assert(id == 0);

  id = -1;
  ms_assert_ok(ms_load_file(ms, SHARED_OBJECT, lib, symbol, &id));
  ms_assert(id == 1);

  ms_assert_ok(ms_measure(ms, batch_size, number_of_batches));

  assert_string_in_json(ms, "incorrect\":0");

  ms_assert_ok(ms_terminate(ms));

  return 0;
}

static int test_array_width_three_add_pair_ok() {

  const char symbol[] = {"array_width_three_add_pair"};

  char code[] = {"mov rax, [rsi]; *i0 \n"
                 "add rax, [rdx]; *i0 + *i1\n"
                 "mov [rdi], rax; *o0 <-\n"

                 "mov rax, [rsi + 0x08]; *i0+1\n"
                 "add rax, [rdx + 0x08]; *i0+1 + *i1+1\n"
                 "mov [rdi + 0x08], rax; *o0 + 1 <-\n"

                 "mov rax, [rsi + 0x10 ]; *i0 + 2\n"
                 "add rax, [rdx + 0x10 ]; *i0 + 2 + *i1+2\n"
                 "mov [rdi + 0x10 ], rax; *o0 + 2 <-\n"

                 "ret\n"};

  static const int arg_width = 3;
  static const int arg_num_in = 2;
  static const int arg_num_out = 1;

  measuresuite_t ms = NULL;

  ms_initialize(&ms, arg_width, arg_num_in, arg_num_out);
  ms_set_checking(ms, 1);

  int id = -1;
  ms_assert_ok(
      ms_load_data(ms, ASM, (uint8_t *)code, strlen(code), symbol, &id));
  ms_assert(id == 0);

  id = -1;
  ms_assert_ok(ms_load_file(ms, SHARED_OBJECT, lib, symbol, &id));
  ms_assert(id == 1);

  ms_assert_ok(ms_measure(ms, batch_size, number_of_batches));

  assert_string_in_json(ms, "incorrect\":0");

  ms_assert_ok(ms_terminate(ms));

  return 0;
}

static int test_array_width_three_mul_ok() {

  const char symbol[] = {"array_width_three_mul"};

  char code[] = {"mov r8, rdx; saving i1 \n"
                 "mov rdx, [rsi]; *i0 \n"
                 "mulx r9, rax, [r8]; *i0 * *i1\n"
                 "mov [rdi], rax; *o0 <-\n"

                 "mov rdx, [rsi + 0x08]; *i0+1\n"
                 "mulx r9, rax, [r8 + 0x08]; *i0+1 * *i1+1\n"
                 "mov [rdi + 0x08], rax; *o0 + 1 <-\n"

                 "mov rdx, [rsi + 0x10 ]; *i0 + 2\n"
                 "mulx r9, rax, [r8 + 0x10 ]; *i0 + 2 * *i1+2\n"
                 "mov [rdi + 0x10 ], rax; *o0 + 2 <-\n"

                 "ret\n"

  };

  static const int arg_width = 3;
  static const int arg_num_in = 2;
  static const int arg_num_out = 1;

  measuresuite_t ms = NULL;

  ms_initialize(&ms, arg_width, arg_num_in, arg_num_out);
  ms_set_checking(ms, 1);

  int id = -1;
  ms_assert_ok(
      ms_load_data(ms, ASM, (uint8_t *)code, strlen(code), symbol, &id));
  ms_assert(id == 0);

  id = -1;
  ms_assert_ok(ms_load_file(ms, SHARED_OBJECT, lib, symbol, &id));
  ms_assert(id == 1);

  ms_assert_ok(ms_measure(ms, batch_size, number_of_batches));

  assert_string_in_json(ms, "incorrect\":0");

  ms_assert_ok(ms_terminate(ms));

  return 0;
}

static int test_array_width_three_add_ok() {

  const char symbol[] = {"array_width_three_add"};

  char code[] = {"mov rax, [rsi]; *i0\n"
                 "add rax, 1; *i0+1\n"
                 "mov [rdi], rax; *o0 <-\n"

                 "mov rax, [rsi + 0x08]; *i0+1\n"
                 "add rax, 1; *i0+1 + 1\n"
                 "mov [rdi + 0x08], rax; *o0 + 1 <-\n"

                 "mov rax, [rsi + 0x10 ]; *i + 2\n"
                 "add rax, 1; *i + 2 + 1\n"
                 "mov [rdi + 0x10 ], rax; *o + 2 <-\n"

                 "ret\n"};

  static const int arg_width = 3;
  static const int arg_num_in = 2;
  static const int arg_num_out = 1;

  measuresuite_t ms = NULL;

  ms_initialize(&ms, arg_width, arg_num_in, arg_num_out);
  ms_set_checking(ms, 1);

  int id = -1;
  ms_assert_ok(
      ms_load_data(ms, ASM, (uint8_t *)code, strlen(code), symbol, &id));
  ms_assert(id == 0);

  id = -1;
  ms_assert_ok(ms_load_file(ms, SHARED_OBJECT, lib, symbol, &id));
  ms_assert(id == 1);

  ms_assert_ok(ms_measure(ms, batch_size, number_of_batches));

  assert_string_in_json(ms, "incorrect\":0");

  ms_assert_ok(ms_terminate(ms));

  return 0;
}

static int test_array_width_six_param_add_ok() {

  const char symbol[] = {"six_param_add1"};

  /** void six_param_add1(uint64_t *o0, uint64_t *o1, uint64_t *o2,
   * uint64_t *i0, uint64_t *i1, uint64_t *i2); */
  char code[] = {"mov rax, [rcx]; *i0\n"
                 "add rax, 1; *i0+1\n"
                 "mov [rdi], rax; *o0 <-\n"
                 "mov rax, [r8]; *i1\n"
                 "add rax, 1; *i1 + 1\n"
                 "mov [rsi], rax; *o1 <-\n"
                 "mov rax, [r9]; *i2\n"
                 "add rax, 1; *i2 + 1\n"
                 "mov [rdx], rax; *o2 <-\n"
                 "ret\n"};

  static const int arg_width = 1;
  static const int arg_num_in = 3;
  static const int arg_num_out = 3;

  measuresuite_t ms = NULL;

  ms_initialize(&ms, arg_width, arg_num_in, arg_num_out);
  ms_set_checking(ms, 1);

  int id = -1;
  ms_assert_ok(
      ms_load_data(ms, ASM, (uint8_t *)code, strlen(code), symbol, &id));
  ms_assert(id == 0);

  id = -1;
  ms_assert_ok(ms_load_file(ms, SHARED_OBJECT, lib, symbol, &id));
  ms_assert(id == 1);

  ms_assert_ok(ms_measure(ms, batch_size, number_of_batches));

  assert_string_in_json(ms, "incorrect\":0");

  ms_assert_ok(ms_terminate(ms));

  return 0;
}

static int test_broadcast_2_ok() {

  const char symbol[] = {"broadcast_2"};

  /** void six_param_add1(uint64_t *o0, uint64_t *o1, uint64_t *o2,
   * uint64_t *i0, uint64_t *i1, uint64_t *i2); */
  char code[] = {"mov rax, [rdx]; *i0\n"
                 "mov [rdi], rax; *o0 <-\n"
                 "mov [rsi], rax; *o1 <-\n"
                 "ret\n"};

  static const int arg_width = 1;
  static const int arg_num_in = 1;
  static const int arg_num_out = 2;

  measuresuite_t ms = NULL;

  ms_initialize(&ms, arg_width, arg_num_in, arg_num_out);
  ms_set_checking(ms, 1);

  int id = -1;
  ms_assert_ok(
      ms_load_data(ms, ASM, (uint8_t *)code, strlen(code), symbol, &id));
  ms_assert(id == 0);

  id = -1;
  ms_assert_ok(ms_load_file(ms, SHARED_OBJECT, lib, symbol, &id));
  ms_assert(id == 1);

  ms_assert_ok(ms_measure(ms, batch_size, number_of_batches));

  assert_string_in_json(ms, "incorrect\":0");

  ms_assert_ok(ms_terminate(ms));

  return 0;
}
static int test_broadcast_array_2_ok() {

  const char symbol[] = {"broadcast_array_2"};

  /** void six_param_add1(uint64_t *o0, uint64_t *o1, uint64_t *o2,
   * uint64_t *i0, uint64_t *i1, uint64_t *i2); */
  char code[] = {"mov rax, [rsi]; *i0\n"
                 "mov [rdi], rax; *o0[0] <-\n"
                 "mov [rdi+0x08], rax; *o0[1] <-\n"
                 "ret\n"};

  static const int arg_width = 2;
  static const int arg_num_in = 1;
  static const int arg_num_out = 1;

  measuresuite_t ms = NULL;

  ms_initialize(&ms, arg_width, arg_num_in, arg_num_out);
  ms_set_checking(ms, 1);

  int id = -1;
  ms_assert_ok(
      ms_load_data(ms, ASM, (uint8_t *)code, strlen(code), symbol, &id));
  ms_assert(id == 0);

  id = -1;
  ms_assert_ok(ms_load_file(ms, SHARED_OBJECT, lib, symbol, &id));
  ms_assert(id == 1);

  ms_assert_ok(ms_measure(ms, batch_size, number_of_batches));

  assert_string_in_json(ms, "incorrect\":0");

  ms_assert_ok(ms_terminate(ms));

  return 0;
}

int main() {
  int res = 0;
  res |= test_broadcast_array_2_ok();
  res |= test_broadcast_2_ok();
  res |= test_array_width_three_add_ok();
  res |= test_array_width_three_add_pair_ok();
  res |= test_array_width_three_mul_ok();
  res |= test_array_width_five_add_pair_ok();
  res |= test_array_width_six_param_add_ok();
  return res;
}
