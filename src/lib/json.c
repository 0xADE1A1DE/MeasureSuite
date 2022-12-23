#include "json.h"
#include "alloc_helper.h"
#include "struct_measuresuite.h"

#define PRINT(...)                                                             \
  size = json_end - json;                                                      \
  len = snprintf(json, size, ##__VA_ARGS__);                                   \
  if (len >= size) {                                                           \
    goto enlarge;                                                              \
  }                                                                            \
  json += len;

int generate_json(struct measuresuite *ms, uint64_t delta_in_seconds,
                  size_t check_result) {
  char *json = ms->json;
  char *json_end = ms->json + ms->json_len - 1;

  size_t size = json_end - json; // available
  size_t len = 0;                // written

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

  for (struct function_tuple *fct = ms->functions;
       fct <= &ms->functions[ms->num_functions - 1]; fct++) {
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
  for (struct function_tuple *fct = ms->functions;
       fct <= &ms->functions[ms->num_functions - 1]; fct++) {

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
  fprintf(stderr, "trying to realloc space for more json\n");
  if (realloc_or_fail(ms, (void **)&(ms->json), ms->json_len)) {
    return 1;
  }

  // and try again recursively
  return generate_json(ms, delta_in_seconds, check_result);
}
#undef PRINT
