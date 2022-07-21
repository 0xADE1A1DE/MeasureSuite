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

#include "printer.h"
#include <stdio.h>
void printbin_single_number(uint64_t n) {

  const int bitwitdh_uint64 = 64;

  int width = bitwitdh_uint64; // bits
  uint64_t mask = (uint64_t)1 << (bitwitdh_uint64 - 1);
  while (width--) {
    if (n & mask)
      printf("1");
    else
      printf("0");

    mask >>= 1;
  }
  printf("\n");
}
static const int color_grn = 32;

void printbin(uint64_t const *a, uint64_t const *b, int len, int l) {
  int color = color_grn - (*a != *b); // col 32 when its equal, grn
  printf("\n\x1b[%dm @ %d/%d: \n"
         "a:0b",
         color, len, l);
  printbin_single_number(*a);
  printf("b:0b");
  printbin_single_number(*b);
  printf("\x1b[0m");
}

void printhex(uint64_t const *a, uint64_t const *b, int len, int l) {
  int color = color_grn - (*a != *b); // col 32 when its equal, grn
  printf("\n\x1b[%dm @ %d/%d: \n"
         "a:0x%016lx\n"
         "b:0x%016lx\x1b[0m\n",
         color, len, l, *a, *b);
}
