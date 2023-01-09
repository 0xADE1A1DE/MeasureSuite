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

#include "checker.h"
#include "printer.h"
#include <stddef.h>
#include <stdio.h>

/*
 * checks len * sizeof(uint64) bytes
 * returns 0 if *(b+n) == *(a+n) for all n in [0, len]
 */
enum CORRECTNESS { OK = 0, WRONG = 1 };
int check(size_t len, const uint64_t *data, const uint64_t *check_data) {
  size_t total = len;
  int res = OK;
  data += len;
  check_data += len;
  // check first.
  while (len--) {
    res |= (*(--data) != *(--check_data));
  }

  // if where is a mistake, print all
  if (res == WRONG) {
    while (++len < total) {
#if PRINT_BIN
      printbin(a, b, len, total);
#else
      printhex(data, check_data, len, total);
#endif
      data++;
      check_data++;
    }
  }
  // and return the result anyway
  return res;
}
