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
#include <stdlib.h>
#include <string.h>

const char lib[] = {"./liball_lib.so"};
const char symbol[] = {"mul2"};

int main() {
  // convenience pointer
  void (*err)(measuresuite_t, const char *) =
      error_handling_helper_template_str;

  const int num_batches = 2000;
  // must be big enough to overflow the preallocated buffer once, to
  // test the realloc_or_fail in ms_measure_lib_only
  const size_t batch_size = 200;

  // INIT
  const int arg_width = 4;
  const int arg_num_in = 4;
  const int arg_num_out = 2;
  const int chunksize = 0;
  const uint64_t bounds[] = {-1};

  measuresuite_t ms = NULL;
  if (ms_measure_init(&ms, arg_width, arg_num_in, arg_num_out, chunksize,
                      bounds, lib, symbol)) {
    err(ms, "Failed to measure_init. Reason: %s.");
    return 1;
  }

  // measure
  if (ms_measure_lib_only(ms, batch_size, num_batches)) {
    err(ms, "Failed to ms_measure_lib_only. Reason: %s.");
    return 1;
  }

  uint64_t *dest = NULL;
  ms_get_libcycles(ms, &dest);

  for (size_t i = 0; i < batch_size; i++) {
    // every measurement should be bigger than 0
    if (dest[i] <= 0) {
      fprintf(stderr, "%lu should be bigger than 0\n", dest[i]);
      return 1;
    }
  }

  // END
  if (ms_measure_end(ms)) {
    err(ms, "Failed to measure_end. Reason: %s.");
    return 1;
  }
  return 0;
}
