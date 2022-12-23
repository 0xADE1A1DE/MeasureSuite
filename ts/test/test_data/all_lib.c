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

#include <stdint.h>

void increment(long *d, const long *s) { *d = *s + 1; }

// reminder of calling convention:
// https://en.wikipedia.org/wiki/X86_calling_conventions#List_of_x86_calling_conventions
// RDI, RSI, RDX, RCX, R8, R9, [XYZ]MM0–7

void sixparamadd(uint64_t *o0, uint64_t *o1, uint64_t *o2, const uint64_t *i0,
                 const uint64_t *i1, const uint64_t *i2) {
  *o0 = *i0 + 1;
  *o1 = *i1 + 1;
  *o2 = *i2 + 1;
}

void array_width_three_add(uint64_t o[3], const uint64_t i[3]) {
  *o++ = *i++ + 1;
  *o++ = *i++ + 1;
  *o = *i + 1;
}

void add_two_numbers(uint64_t *o, const uint64_t *i0, const uint64_t *i1) {
  *o = *i0 + *i1;
}

void array_width_three_mul(uint64_t o[3], const uint64_t i0[3],
                           const uint64_t i1[3]) {
  o[0] = i0[0] * i1[0];
  o[1] = i0[1] * i1[1];
  o[2] = i0[2] * i1[2];
  /** *o++ = *i0++ * *i1++; */
  /** *o++ = *i0++ * *i1++; */
  /** *o = *i0 * *i1; */
}

void array_width_three_add_pair(uint64_t o[3], const uint64_t i0[3],
                                const uint64_t i1[3]) {
  o[0] = i0[0] + i1[0];
  o[1] = i0[1] + i1[1];
  o[2] = i0[2] + i1[2];
}

void array_width_five_add_pair(uint64_t *o, const uint64_t *i0,
                               const uint64_t *i1) {
  o[0] = i0[0] + i1[0];
  o[1] = i0[1] + i1[1];
  o[2] = i0[2] + i1[2];
  o[3] = i0[3] + i1[3];
  o[4] = i0[4] + i1[4];
}
void mul2(uint64_t out1[4], uint64_t out2[4], const uint64_t arg1[4],
          const uint64_t arg2[4], const uint64_t arg3[4],
          const uint64_t arg4[4]) {
  out1[0] = arg1[0] * arg2[0];
  out1[1] = arg1[1] * arg2[1];
  out1[2] = arg1[2] * arg2[2];
  out1[3] = arg1[3] * arg2[3];
  out2[0] = arg3[0] * arg4[0];
  out2[1] = arg3[1] * arg4[1];
  out2[2] = arg3[2] * arg4[2];
  out2[3] = arg3[3] * arg4[3];
}
