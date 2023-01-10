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
#include <assert.h>
#include <measuresuite.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

int main() {

  const char *const filename = {"./add_two_numbers.o"};
  /*
   * the c-function declaration would be something like
   * void add_two_numbers(uint64_t *out0,
   *                      const uint64_t *in0,
   *                      const uint64_t *in1) {
   *    *out0 = *in0 + *in1;
   * }
   */

  /*
   * properties of the function
   */

  // each parameter of the test function points to only one element (i.e.
  // out0[0],)
  const int arg_width = 1;

  // one out-parameter (there is only out0, no out1, etc.)
  const int arg_num_out = 1;

  // two in-paramters (in0, in1)
  const int arg_num_in = 2;

  // our measuresuite handle
  measuresuite_t ms = NULL;

  // initializing the measuresuite
  ms_initialize(&ms, arg_width, arg_num_in, arg_num_out);

  // id = -1 means 'load to the next free slot'
  // it will be set to the 'slot taken by the loaded function', after return
  int id = -1;
  ms_load_file(ms,  // handle
               ELF, // type of input data is elf
               filename,
               NULL, // symbol (ignored for BIN/ASM, optional for ELF, required
                     // for SHARED_OBJECT)
               &id); // ID (in/out)

  // first slot (subsequent loads will load to 1, 2, ...)
  assert(id == 0);

  // measure parameters
  const int number_of_batches = 10; // 10 batches of
  const int batch_size =
      100; // 100 iterations of the function-unter-test (add_two_asm), each

  // run the measurement
  ms_measure(ms, batch_size, number_of_batches);

  // prepare got JSON collection
  const char *json = NULL;
  size_t len = 0;
  ms_get_json(ms, &json, &len);

  assert(json != NULL);
  assert(len != 0);

  // prints the result json to stdout.
  printf("%s\n", json);

  // free all (internal) resources
  ms_terminate(ms);

  return 0;
}
