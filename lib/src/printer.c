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

#include "printer.h"
#include <inttypes.h>
#include <stdio.h>

void printbin_single_number(uint64_t num) {

  const int bitwidth_uint64 = 64;

  int width = bitwidth_uint64; // bits
  uint64_t mask = (uint64_t)1 << (bitwidth_uint64 - 1);
  while (width--) {
    printf("%" PRIu64, num & mask);
    mask >>= 1;
  }
  printf("\n");
}

static const int color_grn = 32;

void printbin(uint64_t const *data_a, uint64_t const *data_b, size_t idx,
              size_t total) {
  int color = color_grn - (*data_a != *data_b); // col 32 when its equal, grn
  printf("\n\x1b[%dm @ %lu/%lu: \n"
         "a:0b",
         color, idx, total);
  printbin_single_number(*data_a);
  printf("b:0b");
  printbin_single_number(*data_b);
  printf("\x1b[0m");
}

void printhex(uint64_t const *data_a, uint64_t const *data_b, size_t idx,
              size_t total) {
  int color = color_grn - (*data_a != *data_b); // col 32 when its equal, grn
  printf("\n\x1b[%dm @ %" PRIu64 "/%" PRIu64 ": \n"
         "a:0x%016lx\n"
         "b:0x%016lx\x1b[0m\n",
         color, idx, total, *data_a, *data_b);
}
