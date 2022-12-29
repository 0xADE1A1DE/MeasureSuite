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

  const int too_many_arg_in = 200;
  ms_assert(ms_initialize(&ms, arg_width, too_many_arg_in, arg_num_out) == 1);
  ms_assert_ok(ms_terminate(ms));

  const int neg_arg_in = -1;
  ms_assert(ms_initialize(&ms, arg_width, neg_arg_in, arg_num_out) == 1);
  ms_assert_ok(ms_terminate(ms));

  const int too_many_arg_in_2 = 6;
  ms_assert(ms_initialize(&ms, arg_width, too_many_arg_in_2, arg_num_out) == 1);
  ms_assert_ok(ms_terminate(ms));

  return 0;
}
static int test_init_terminate_arg_num_out() {

  measuresuite_t ms = NULL;

  const int neg_arg_out = -1;
  ms_assert(ms_initialize(&ms, arg_width, arg_num_in, neg_arg_out) == 1);
  ms_assert_ok(ms_terminate(ms));

  const int too_many_arg_out = 7;
  ms_assert(ms_initialize(&ms, arg_width, arg_num_in, too_many_arg_out) == 1);
  ms_assert_ok(ms_terminate(ms));

  const int too_many_arg_out_2 = 1000;
  ms_assert(ms_initialize(&ms, arg_width, arg_num_in, too_many_arg_out_2) == 1);
  ms_assert_ok(ms_terminate(ms));

  return 0;
}

int main() {
  SIGILL_SETUP();
  int res = 0;
  res |= test_init_terminate_ok();
  res |= test_init_terminate_arg_width();
  res |= test_init_terminate_arg_num_in();
  res |= test_init_terminate_arg_num_out();
  return res;
}
