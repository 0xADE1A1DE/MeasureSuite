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

#include <assert.h>
#include <measuresuite.h>

static int test_init_terminate_ok() {

  const int arg_width = 1;
  const int arg_num_in = 2;
  const int arg_num_out = 1;
  measuresuite_t ms = NULL;

  assert(ms_initialize(&ms, arg_width, arg_num_in, arg_num_out) == 0);
  assert(ms_terminate(ms) == 0);

  return 0;
}
static int test_init_terminate_arg_width() {
  const int arg_num_in = 2;
  const int arg_num_out = 1;
  measuresuite_t ms = NULL;

  assert(ms_initialize(&ms, -10, arg_num_in, arg_num_out) == 1);
  assert(ms_terminate(ms) == 0);

  return 0;
}
static int test_init_terminate_arg_num_in() {
  const int arg_width = 1;
  const int arg_num_out = 1;
  measuresuite_t ms = NULL;

  assert(ms_initialize(&ms, arg_width, 200, arg_num_out) == 1);
  assert(ms_terminate(ms) == 0);

  assert(ms_initialize(&ms, arg_width, -1, arg_num_out) == 1);
  assert(ms_terminate(ms) == 0);

  assert(ms_initialize(&ms, arg_width, 6, arg_num_out) == 1);
  assert(ms_terminate(ms) == 0);

  return 0;
}
static int test_init_terminate_arg_num_out() {
  const int arg_width = 1;
  const int arg_num_in = 2;
  measuresuite_t ms = NULL;

  assert(ms_initialize(&ms, arg_width, arg_num_in, -1) == 1);
  assert(ms_terminate(ms) == 0);

  assert(ms_initialize(&ms, arg_width, arg_num_in, 7) == 1);
  assert(ms_terminate(ms) == 0);

  assert(ms_initialize(&ms, arg_width, arg_num_in, 1000) == 1);
  assert(ms_terminate(ms) == 0);

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
