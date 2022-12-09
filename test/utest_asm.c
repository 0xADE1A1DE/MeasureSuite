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
#include <assert.h>
#include <measuresuite.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char lib[] = {"./liball_lib.so"};
const char symbol[] = {"add_two_numbers"};

int main() {
  char fa[] = {"mov rax, [rsi]\n"
               "add rax, [rdx]\n"
               "mov [rdi], rax\n"
               "ret\n"};

  // convenience pointer
  void (*err)(measuresuite_t, const char *) =
      error_handling_helper_template_str;
  const int num_batches = 2;
  const int batch_size = 2;

  // INIT
  const int arg_width = 1;
  const int arg_num_in = 2;
  const int arg_num_out = 1;
  const int chunksize = 0;
  const uint64_t bounds[] = {-1};
  measuresuite_t ms = NULL;

  if (ms_initialize(&ms, arg_width, arg_num_in, arg_num_out, chunksize,
                    bounds)) {
    err(ms, "Failed to init. Reason: %s.");
    return 1;
  }
  if (ms_enable_checking(ms, lib, symbol)) {
    err(ms, "Failed to enable_checking. Reason: %s.");
    return 1;
  }

  // measure
  if (ms_measure(ms, fa, fa, batch_size, num_batches)) {
    error_handling_helper_template_str(ms, "Failed to measure. Reason: %s.");
    return 1;
  }
  const char *output = NULL;
  size_t jsonlen = 0;
  ms_get_json(ms, &output, &jsonlen);
  printf("%s\n", output);

  // END
  if (ms_terminate(ms)) {
    error_handling_helper_template_str(ms,
                                       "Failed to measure_end. Reason: %s.");
    return 1;
  }

  return 0;
}
static int test_asm();           // aaaaaaaaaaaa
static int test_asm_asm();       // abababaaba
static int test_asm_check();     /// acacacacacacacaca
static int test_asm_asm_check(); /// acbcabcbcbabc

int main() {
  int ret = 0;
  ret |= test_asm();     // aaaaaaaaaaaa
  ret |= test_asm_asm(); // abababaaba

  ret |= test_asm_check();     /// acacacacacacacaca
  ret |= test_asm_asm_check(); /// acbcabcbcbabc

  return ret;
}
int test_asm() {
  char fa[] = {"mov rax, [rsi]\n"
               "add rax, [rdx]\n"
               "mov [rdi], rax\n"
               "ret\n"};

  // convenience pointer
  void (*err)(measuresuite_t, const char *) =
      error_handling_helper_template_str;

  const int num_batches = 2;
  const int batch_size = 2;

  // INIT
  const int arg_width = 1;
  const int arg_num_in = 2;
  const int arg_num_out = 1;
  const int chunksize = 0;
  const uint64_t bounds[] = {-1};
  measuresuite_t ms = NULL;

  /*
   * will run aaaaaaaaa
   **/
  if (ms_initialize(&ms, arg_width, arg_num_in, arg_num_out))
    goto err;

  int id = -1;
  // *id is -1 => new AL, *id=next
  if (ms_load_asm(ms, fa, &id))
    goto err;

  assert(id >= 0);

  if (ms_measure(ms, batch_size, num_batches))
    goto err;

  const char *output = NULL;
  size_t jsonlen = 0;

  ms_get_json(ms, &output, &jsonlen);
  printf("%s\n", output);

  char *pos = strstr(output, "runOrder\": \"aa");
  assert(pos != NULL);

  ms_terminate(ms);
  return 0;
err:

  ms_terminate(ms);
  return 1;
}

#if false
  /** ms_load_asm(ms, asm, &id); // */
  /** ms_measure(ms, batch_size, num_batches); */
  /*
  // will run aabbabaaba
   **/
  ms_initialize(&ms, arg_width, arg_num_in, arg_num_out);
  ms_measure_asm(ms, fa, fa, batch_size, num_batches);
  ms_terminate(ms);

  /*
   * will run acacac
   **/
  ms_initialize(&ms, arg_width, arg_num_in, arg_num_out);
  ms_load_shared_object(ms, lib, symbol);
  ms_measure_asm(ms, fa, batch_size, num_batches);
  ms_terminate(ms);

  /*
   * will run acacbcbcacbcacacbcac
   **/
  ms_initialize(&ms, arg_width, arg_num_in, arg_num_out);
  ms_load_shared_object(ms, lib, symbol);
  ms_measure_asm(ms, fa, fa, batch_size, num_batches);
  ms_terminate(ms);

  /*
   * will run cccccc
   **/
  ms_initialize(&ms, arg_width, arg_num_in, arg_num_out);
  ms_load_shared_object(ms, lib, symbol);
  ms_measure_shared_object(ms, batch_size, num_batches);
  ms_terminate(ms);

  /*
   * will run  eeeeeeeeeeeee
   **/
  ms_initialize(&ms, arg_width, arg_num_in, arg_num_out);
  ms_load_elf(ms, filename, symbol)
      ms_measure_elfs(ms, batch_size, num_batches);
  ms_terminate(ms);

  /*
   * will run  efefefefeffefef
   **/
  ms_initialize(&ms, arg_width, arg_num_in, arg_num_out);
  ms_load_elf(ms, filename, symbol);
  ms_load_elf(ms, filename2, symbol2);
  ms_measure_elfs(ms, batch_size, num_batches);

  /*
   * will run  efefefefeffefef
   **/
  ms_initialize(&ms, arg_width, arg_num_in, arg_num_out);
  ms_load_elf(ms, filename, symbol);
  ms_load_elf(ms, filename2, symbol2);
  ms_measure_elfs(ms, batch_size, num_batches);

  // optional
  ms_set_chunksize(
      ms,
      chunksize); // only useful with al; only returns no/chunk breaks in JSON
  ms_set_inbounds(ms, bounds); // can be used to limit the range of valid inputs
  ms_set_outbounds(ms,
                   bounds);  // can be used to limit the range of valid outputs
  ms_set_bounds(ms, bounds); // shortcut to set both.
  ms_enable_checking(
      ms); // if so is loaded, will check and error out if invalid check
  ms_disable_checking(ms); // won't check and error out if invalid check

  if (ms_enable_checking(ms, lib, symbol)) {
    err(ms, "Failed to enable_checking. Reason: %s.");
    return 1;
  }

  // measure
  if (ms_measure(ms, fa, fa, batch_size, num_batches)) {
    error_handling_helper_template_str(ms, "Failed to measure. Reason: %s.");
    return 1;
  }
#endif
