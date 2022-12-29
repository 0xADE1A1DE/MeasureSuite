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

#include "arg_parse.h"
#include "debug.h"
#include <getopt.h>
#include <measuresuite.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PARSE(x)                                                               \
  if (optarg == NULL)                                                          \
    break;                                                                     \
  (x) = atoi(optarg);

const static struct option long_options[] = {
    // clang-format off
        { "width",       required_argument, 0, 'w'},
        { "in",          required_argument, 0, 'i'},
        { "out",         required_argument, 0, 'o'},
        { "num_batches", required_argument, 0, 'n'},
        { "batch_size",  required_argument, 0, 'b'},
        { "check",       no_argument,       0, 'c'},
        { "symbol",      required_argument, 0, 's'},
        {0, 0, 0, 0}
    // clang-format on
};

// NOLINTBEGIN (readability-function-cognitive-complexity)
int parse(struct opts *dest, int argc, char *argv[]) {
  *dest = default_opts;

  while (1) {
    int this_option_optind = optind ? optind : 1;
    int option_index = 0;

    int option =
        getopt_long(argc, argv, "w:i:o:n:b:cs:", long_options, &option_index);
    if (option == -1)
      break;

    switch (option) {
    case 'c':
      dest->check = 1;
      break;
    case 'w':
      PARSE(dest->arg_width)
      break;
    case 'i':
      PARSE(dest->arg_num_in);
      break;
    case 'o':
      PARSE(dest->arg_num_out);
      break;
    case 'n':
      PARSE(dest->num_batches);
      break;
    case 'b':
      PARSE(dest->batch_size);
      break;
    case 's':
      _DEBUG("reading symbol now %s\n", optarg);
      if (optarg == NULL)
        break;
      dest->sym = calloc(strlen(optarg), sizeof(char));
      if (dest->sym == NULL) {
        break;
      }
      strncpy(dest->sym, optarg, strlen(optarg));
      _DEBUG("symbol %s\n", optarg);
      break;

    case '?':
      break;

    default:
      printf("?? getopt returned character code 0%o ??\n", option);
    }
  }

  return optind;
}
#undef PARSE
// NOLINTEND
