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

static const char symbol[] = {"add_two_numbers"};
static const char file_asm[] = {"./test_data/add_two_numbers.asm"};
static const char file_shared_object[] = {"./test_data/add_two_numbers.so"};
static const int arg_width = 1;
static const int arg_num_in = 2;
static const int arg_num_out = 1;
static const int batch_size = 2;
static const int number_of_batches = 10;

static int test_measure_two_ok() {

  measuresuite_t ms = NULL;

  int ids[] = {-1, -1, -1, -1};
  int pointer = 0;
  ms_assert_ok(ms_initialize(&ms, arg_width, arg_num_in, arg_num_out));

  ms_load_file(ms, ASM, file_asm, symbol, ids + pointer++);
  ms_load_file(ms, SHARED_OBJECT, file_shared_object, symbol, ids + pointer++);

  ms_measure(ms, batch_size, number_of_batches);
  const char *json = NULL;
  size_t len = 0;
  ms_get_json(ms, &json, &len);

  ms_assert(len != 0);
  ms_assert(json != 0);

  // EXAMPLE STRING
  //{"stats":{"numFunctions":2,"runtime":0,"incorrect":0},"functions":[{"type":"ASM",
  //"chunks":0},{"type":"SHARED_OBJECT"}],"cycles":[[1721,1714,1589,1701,1704,2589,2550,2589,2584,2593],[2403,1674,1639,1674,1782,1751,2597,2594,2598,2589]]}

  char *pos = strstr(json, "{\"stats\":{\"numFunctions\":2,\"runtime\":");
  assert(pos != NULL);
  pos =
      strstr(json, "\"incorrect\":0},\"functions\":[{\"type\":\"ASM\", "
                   "\"chunks\":0},{\"type\":\"SHARED_OBJECT\"}],\"cycles\":[[");
  assert(pos != NULL);

  ms_assert_ok(ms_terminate(ms));

  return 0;
}

int main() {
  int res = 0;
  res |= test_measure_two_ok();
  return res;
}
