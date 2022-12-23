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

static const int arg_width = 1;
static const int arg_num_in = 2;
static const int arg_num_out = 1;
static int test_init_terminate_ok() {

  measuresuite_t ms = NULL;

  ms_assert_ok(ms_initialize(&ms, arg_width, arg_num_in, arg_num_out));
  ms_assert_ok(ms_terminate(ms));

  return 0;
}
static int test_init_terminate_arg_width() {

  measuresuite_t ms = NULL;

  ms_assert(ms_initialize(&ms, -10, arg_num_in, arg_num_out) == 1);
  ms_assert_ok(ms_terminate(ms));

  return 0;
}
static int test_init_terminate_arg_num_in() {

  measuresuite_t ms = NULL;

  ms_assert(ms_initialize(&ms, arg_width, 200, arg_num_out) == 1);
  ms_assert_ok(ms_terminate(ms));

  ms_assert(ms_initialize(&ms, arg_width, -1, arg_num_out) == 1);
  ms_assert_ok(ms_terminate(ms));

  ms_assert(ms_initialize(&ms, arg_width, 6, arg_num_out) == 1);
  ms_assert_ok(ms_terminate(ms));

  return 0;
}
static int test_init_terminate_arg_num_out() {

  measuresuite_t ms = NULL;

  ms_assert(ms_initialize(&ms, arg_width, arg_num_in, -1) == 1);
  ms_assert_ok(ms_terminate(ms));

  ms_assert(ms_initialize(&ms, arg_width, arg_num_in, 7) == 1);
  ms_assert_ok(ms_terminate(ms));

  ms_assert(ms_initialize(&ms, arg_width, arg_num_in, 1000) == 1);
  ms_assert_ok(ms_terminate(ms));

  return 0;
}

int main() {
  int res = 0;
  res |= test_init_terminate_ok();
  res |= test_init_terminate_arg_width();
  res |= test_init_terminate_arg_num_in();
  res |= test_init_terminate_arg_num_out();
  return res;
}
