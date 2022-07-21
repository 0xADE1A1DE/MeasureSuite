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

#include <measuresuite.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char symbol[] = {"fiat_p521_carry_mul"};
const int arg_width = 9;
const int arg_num_in = 2;
// those arrays are below

int main() {

  // INIT
  int arg_num_out = 1;
  int chunksize = 0;
  measuresuite_t ms = NULL;
  const uint64_t bounds[] = {
      0xc00000000000000 - 1, 0xc00000000000000 - 1, 0xc00000000000000 - 1,
      0xc00000000000000 - 1, 0xc00000000000000 - 1, 0xc00000000000000 - 1,
      0xc00000000000000 - 1, 0xc00000000000000 - 1, 0x600000000000000 - 1};
  if (ms_measure_init(&ms, arg_width, arg_num_in, arg_num_out, chunksize,
                      bounds, "./does_not_exist.so", symbol)) {

    const int len = 1000;
    char *s = calloc(1, len * sizeof(char));
    ms_str_full_error(ms, s, len);
    const char expected[] =
        "The given lib check file is not readable and executable. "
        "Reason: No such file or directory\n";

    if (strstr(s, expected) == 0) {
      fprintf(stderr, "the error received \n'%s' is not the expected \n'%s'\n",
              s, expected);
      const int fatal_error = 99;
      return fatal_error;
    };

    free(s);

    // OK, as the error is expected
    return 0;
  }
  return 1;
}
