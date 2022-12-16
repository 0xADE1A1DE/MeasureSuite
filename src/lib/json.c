#include "json.h"
#include "alloc_helper.h"
#include "struct_measuresuite.h"
int generate_json(struct measuresuite *ms, uint64_t delta_in_seconds,
                  size_t check_result) {
  char *json = ms->json;
  char *json_end = ms->json + ms->json_len;

  json += snprintf(json, ms->json_len,
                   "{\"stats\":"
                   "{"
                   "\"numFunctions\":%" PRIu64 ","
                   "\"runtime\":%" PRIu64 "," // in seconds
                   "\"incorrect\":%" PRIu64
                   "}," // if 0, ok, otherwise the index of which function is
                        // incorrect to the previous one.
                   "\"functions\":[",
                   ms->num_functions, delta_in_seconds, check_result);

  // print function meta data
  FOR_EACH_FUNCTION {

    switch (fct->type) {
    case ASM:
      json +=
          snprintf(json, json_end - json,
                   "{\"type\":\"ASM\", \"chunks\":%" PRIi32 "},", fct->chunks);
      break;
    case BIN:
      json += snprintf(json, json_end - json, "{\"type\":\"BIN\"},");
      break;
    case ELF:
      json += snprintf(json, json_end - json, "{\"type\":\"ELF\"},");
      break;
    case SHARED_OBJECT:
      json += snprintf(json, json_end - json, "{\"type\":\"SHARED_OBJECT\"},");
      break;
    }
  }
  // overwrite comma
  json--;
  json += snprintf(json, json_end - json, "],\"cycles\":[");

  // print cycles
  FOR_EACH_FUNCTION {

    json += snprintf(json, json_end - json, "[");
    for (size_t run_i = 0; run_i < ms->num_batches; run_i++) {
      json += snprintf(json, json_end - json, "%" PRIu64 ",",
                       fct->cycle_results[run_i]);
    }
    // overwrite comma after last number
    json--;
    // close array and comma for next one
    json += snprintf(json, json_end - json, "],");
  }

  // overwrite comma after last array
  json -= 1;
  json += snprintf(json, json_end - json, "]}");

  if (json_end - json <= 0) {
    // we did not have enough space.

    // enlarge
    ms->json_len *= 2;
    if (realloc_or_fail(ms, (void **)&(ms->json), ms->json_len)) {
      return 1;
    }

    // and try again recursively
    return generate_json(ms, delta_in_seconds, check_result);
  }

  return 0;
}
