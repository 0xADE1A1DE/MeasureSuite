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
#include "debug.h"
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static const int color_grn = 32;

#ifdef ENABLE_DEBUG
static void printbin_single_number_bin(uint64_t num, uint64_t compare) {

  const int bitwidth_uint64 = 64;
  int width = bitwidth_uint64; // bits

  printf(" (0b");
  while (width--) {
    unsigned long value = (num >> width) & 1;
    unsigned long truth = (compare >> width) & 1;
    int color = color_grn - (truth != value); // col 32 when its equal, grn

    printf("\x1b[%dm%" PRIu64, color, value);
    if (width % 4 == 0 && width > 0) {
      printf(" ");
    }
  }
  printf("\x1b[0m)");
}
#endif

static void printbin_single_number_hex(uint64_t num, uint64_t compare) {

  const short bits_in_u64 = 64;
  const short bits_in_nibble = 4;
  const char nibble_mask = 0xF;

  int width = bits_in_u64 - bits_in_nibble;
  while (width >= 0) {
    unsigned long value = (num >> width) & nibble_mask;
    unsigned long truth = (compare >> width) & nibble_mask;
    int color = color_grn - (truth != value); // col 32 when its equal, grn

    printf("\x1b[%dm%lx", color, value);
    width -= bits_in_nibble;
  }
  printf("\x1b[0m");
}

void pretty_print_results(uint64_t const *data_a, uint64_t const *data_b,
                          size_t total) {

  for (size_t i = 0; i < total; i++) {

    uint64_t ground_truth = data_a[i];
    uint64_t val = data_b[i];
    printf("\n\x1b[%dm@ %lu/%lu\x1b[0m:\n"
           "a:0x",
           color_grn - (val != ground_truth), i, total);

    printbin_single_number_hex(ground_truth, ground_truth);
#ifdef ENABLE_DEBUG
    printbin_single_number_bin(ground_truth, ground_truth);
#endif
    printf("\n\x1b[0mb:0x");

    printbin_single_number_hex(val, ground_truth);
#ifdef ENABLE_DEBUG
    printbin_single_number_bin(val, ground_truth);
#endif

    printf("\n");
    data_b++;
    data_a++;
  }
}
