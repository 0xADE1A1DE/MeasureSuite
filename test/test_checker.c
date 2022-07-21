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

// unit-test
#include "src/lib/checker.h"

int zero_same_8b() {
  const uint64_t a = 0;
  const uint64_t b = 0;
  return check(1, &a, &b);
}

int deadbeef_same_4b() {
  const uint64_t a = 0xDEADBEEF;
  const uint64_t b = 0xDEADBEEF;
  return check(1, &a, &b);
}

int deadbeef_same_16b() {
  const uint64_t a[] = {0xDEADBEEFDEADBEEF, 0xDEADBEEFDEADBEEF};
  const uint64_t b[] = {0xDEADBEEFDEADBEEF, 0xDEADBEEFDEADBEEF};
  return check(2, a, b);
}

int deadbeef_diff_16b() {
  // both are different
  const uint64_t a[] = {0xDEADBEEFDEADBEEF, 0xDEADBEEFDEADBEEF};
  const uint64_t b[] = {0xDEADBEEFDEADBEF0, 0xDEADBEEFDEADBEF0};
  // -----------------------------------^^----diff----------^^
  return check(2, a, b);
}

int deadbeef_diff_16b_1bdiff() {
  // both are different
  const uint64_t a[] = {0xDEADBEEFDEADBEEF, 0xDEADBEEFDEADBEEF};
  const uint64_t b[] = {0xDEADBEEFDEADBEEF, 0xDEADBEEFDEADBEF0};
  // ------------------------------------diff---------------^^
  return check(2, a, b);
}

int deadbeef_diff_16b_2bdiff() {
  // both are different
  const uint64_t a[] = {0xDEADBEEFDEADBEEF, 0xDEADBEEFDEADBEEF};
  const uint64_t b[] = {0xDEADBEEFDEADBEF0, 0xDEADBEEFDEADBEEF};
  // -----------------------------------^^-diff
  return check(2, a, b);
}

int main() {
  int res = 0;
  res |= zero_same_8b();
  res |= deadbeef_same_4b();
  res |= deadbeef_same_16b();
  res |= !deadbeef_diff_16b();
  res |= !deadbeef_diff_16b_1bdiff();
  res |= !deadbeef_diff_16b_2bdiff();
  return res;
}
