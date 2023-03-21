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

#include "arg_parse.h"
#include <debug.h>
#include <measuresuite.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

static const int arg_width = 10;
static const int arg_num_in = 2;
static const int arg_num_out = 1;
static void print_usage(char *bin_name) {
  printf("Usage: %s [OPTIONS]... FILE...\n", bin_name);
  printf("\
          Measures all provided FILE's, by calling assumed function signature  int (*)(uint64_t out_1[], uint64_t out_2[], ..., uint64_t in_1[], uint64_t in_2[], ...);\n\
          The [FILE]... must have valid extensions such as {"
#if USE_ASSEMBLYLINE
         ".asm,"
#endif
         ".bin,.o,.so}\n\
          -w N --width N        Number of elements in each array. Defaults to %d.\n\
          -o N --out N          Number of out-arrays. Defaults to %d.\n\
          -i N --in N           Number of in-arrays. Defaults to %d.\n\
          -n N --num_batches N  Number of batches to measure (=number of elements in each of the result json's cycles-property.) Defaults to %d.\n\
          -b N --batch_size N   Number of iterations of each function per batch. Defaults to %d.\n\
          -s SYM --symbol SYM   SYM is the symbol being looked for in all .so and .o files.\n\
                                Required for .so-files. Will resort in the first found symbol in .o files if SYM omitted.\n\
                                Will be ignored for .bin"
#if USE_ASSEMBLYLINE
         " and .asm"
#endif
         "\n\
          -c --check            If set, will check if all out's of all functions calculate the same result provided same input. Defaults to %s.\n\
          -h --help             This help message.\n",

         default_opts.arg_width, default_opts.arg_num_out,
         default_opts.arg_num_in, default_opts.num_batches,
         default_opts.batch_size, default_opts.check == 0 ? "no" : "yes");
}

static int load(measuresuite_t ms, const char *filename, char *sym) {

  const char *dot = strrchr(filename, '.');
  if (!dot || dot == filename) {
    fprintf(stderr, "File >>%s<<must have an extention.\n", filename);
    return -1;
  }
  dot++;

  enum load_type type = ASM;
  char valid = 0;

  if (strcmp(dot, "asm") == 0) {

#if USE_ASSEMBLYLINE
    type = ASM;
    valid = 1;
#else
    fprintf(stderr, "AssemblyLine not installed. Thus, file cannot have asm "
                    "extension. Install AssemblyLine and recompile.\n");
    return -1;
#endif
  }

  if (strcmp(dot, "bin") == 0) {
    type = BIN;
    valid = 1;
  }
  if (strcmp(dot, "so") == 0) {
    type = SHARED_OBJECT;
    valid = 1;
  }

  if (strcmp(dot, "o") == 0) {
    type = ELF;
    valid = 1;
  }

  if (!valid) {
    fprintf(stderr, "File >>%s<<must have a valid extention.\n", filename);
    return -1;
  }

  int id = -1;

  if (ms_load_file(ms, type, filename, sym, &id)) {
    return 1;
  }
  return 0;
}

int main(int argc, char *argv[]) {
  if (argc < 2 || strcmp(argv[1], "-h") == 0 ||
      strcmp(argv[1], "--help") == 0) {
    print_usage(argv[0]);
    return -1;
  }
  struct opts parsed = {0};
  int idx = parse(&parsed, argc, argv);

  measuresuite_t ms = NULL;
  if (ms_initialize(&ms, parsed.arg_width, parsed.arg_num_in,
                    parsed.arg_num_out)) {
    goto ms_error;
  }

  ms_set_checking(ms, parsed.check);

  for (; idx < argc; idx++) {
    DEBUG("loading file %s\n", argv[idx]);
    int res = load(ms, argv[idx], parsed.sym);
    if (res == 0) {
      continue;
    }
    if (res == 1) {
      goto ms_error;
    }
    return -1;
  }

  if (ms_measure(ms, parsed.batch_size, parsed.num_batches)) {
    goto ms_error;
  };

  const char *json = NULL;
  size_t len = 0;

  ms_get_json(ms, &json, &len);
  printf("%s", json);

  if (ms_terminate(ms)) {
    goto ms_error;
  }
  free(parsed.sym);

  return 0;

ms_error:
  fprintf(stderr, "Error with Measuresuite:");
  ms_fprintf_error(ms, stderr);
  return 1;
}
