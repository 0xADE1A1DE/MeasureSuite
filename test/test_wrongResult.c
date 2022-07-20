#include "helper.h"

#include <measuresuite.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

const char lib[] = {"./liball_lib.so"};
const char symbol[] = {"increment"};

int main() {
  // convenience pointer
  void (*err)(measuresuite_t, const char *) =
      error_handling_helper_template_str;

  char fa[] = {"mov rax, [rsi]\n"
               "add rax, 2\n"
               "mov [rdi], rax\n"
               "ret\n"};
  const int num_batches = 2;
  const int batch_size = 2;

  // INIT
  const int arg_width = 1;
  const int arg_num_in = 1;
  const int arg_num_out = 1;
  const int chunksize = 0;
  const uint64_t bounds[] = {-1};
  measuresuite_t ms = NULL;
  if (ms_measure_init(&ms, arg_width, arg_num_in, arg_num_out, chunksize,
                      bounds, lib, symbol)) {
    err(ms, "Failed to measure_init. Reason: %s.");
    return 1;
  }

  // measure
  if (ms_measure(ms, fa, fa, batch_size, num_batches)) {
    err(ms, "Failed to measure. Reason: %s.");
    return 1;
  }

  // get the json
  const char *output = NULL;
  size_t jsonlen = 0;
  ms_getJson(ms, &output, &jsonlen);
  printf("%s\n", output);

  // Require to have false in the string but not true, because in the lib we
  // calculate "plus1", whereas in the assebly we are passing, we add two.
  if (strstr(output, "false") == NULL && strstr(output, "true") != NULL) {
    fprintf(stderr, "should have been an INCORRECT result\n");
    ms_measure_end(ms);
    return 1;
  }

  // END
  if (ms_measure_end(ms)) {
    err(ms, "Failed to measure_end. Reason: %s.");
    return 1;
  }

  return 0;
}