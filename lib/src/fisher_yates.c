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
#include "fisher_yates.h"
#include "randomizer.h"
#include "struct_measuresuite.h"
#include <stddef.h>

int shuffle_permutations(measuresuite_t ms) {

  // nothing to shuffle if we didn't load any functions yet / there is only one
  // function
  if (ms->num_functions <= 1) {
    return 0;
  }

  for (size_t i = ms->num_functions - 1; // start with last item
       i >= 1; // until second item (no need to shuffle first item with itself)
       i--     // every item
  ) {
    size_t num = 0;
    if (get_random_number(ms, i, &num)) {
      return 1;
    }
    // swap random with current
    size_t tmp = ms->permutation[i];
    ms->permutation[i] = ms->permutation[num];
    ms->permutation[num] = tmp;
  }
  return 0;
}
