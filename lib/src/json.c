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
#include "json.h"
#include "alloc_helper.h"
#include "debug.h"
#include "struct_measuresuite.h"

#define PRINT(...)                                                             \
  size = json_end - json;                                                      \
  len = snprintf(json, size, ##__VA_ARGS__);                                   \
  if (len >= size) {                                                           \
    goto enlarge;                                                              \
  }                                                                            \
  json += len;

// NOLINTBEGIN (readability-function-cognitive-complexity)
int generate_json(struct measuresuite *ms, uint64_t delta_in_seconds,
                  size_t check_result) {
  char *json = ms->json;
  char *json_end = ms->json + ms->json_len - 1;

  size_t size = 0; // available
  size_t len = 0;  // written

  PRINT("{\"stats\":"
        "{"
        "\"numFunctions\":%" PRIu64 ","
        "\"runtime\":%" PRIu64 "," // in seconds
        "\"incorrect\":%" PRIu64
        "}," // if incorrect is '0', all functions calculate the same, otherwise
             // the index of which function is incorrect to the previous one.
        "\"functions\":[",
        ms->num_functions, delta_in_seconds, check_result);

  // print function meta data
  //

  FOR_EACH_FUNCTION {
    switch (fct->type) {
    case ASM:
#ifdef USE_ASSEMBLYLINE
      PRINT("{\"type\":\"ASM\", \"chunks\":%" PRIi32 "},", fct->chunks);
#endif
      break;
    case BIN:
      PRINT("{\"type\":\"BIN\"},");
      break;
    case ELF:
      PRINT("{\"type\":\"ELF\"},");
      break;
    case SHARED_OBJECT:
      PRINT("{\"type\":\"SHARED_OBJECT\"},");
      break;
    }
  }

  // overwrite comma
  json--;
  PRINT("],\"cycles\":[");

  // print cycles
  FOR_EACH_FUNCTION {

    PRINT("[");
    for (size_t run_i = 0; run_i < ms->num_batches; run_i++) {
      PRINT("%" PRIu64 ",", fct->cycle_results[run_i]);
    }
    // overwrite comma after last number
    json--;
    // close array and comma for next one
    PRINT("],");
  }

  // overwrite comma after last array
  json -= 1;
  PRINT("]}");

  return 0;

  // we did not have enough space.
enlarge:

  // enlarge
  ms->json_len *= 2;
  DEBUG("trying to realloc space for more json (new len: %lu) %lu, %lu\n",
        ms->json_len, ms->num_batches, ms->batch_size);
  DEBUG("JSON was: %s", ms->json);
  if (realloc_or_fail(ms, (void **)&(ms->json), ms->json_len)) {
    return 1;
  }

  // and try again recursively
  return generate_json(ms, delta_in_seconds, check_result);
}
#undef PRINT
// NOLINTEND
