#ifndef ARG_PARSE_H
#define ARG_PARSE_H

#include <stdlib.h>
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

struct opts {
  int arg_width;
  int arg_num_in;
  int arg_num_out;
  int num_batches;
  int batch_size;
  int check;
  char *sym;
};

static const struct opts default_opts = {
    .arg_width = 10,
    .arg_num_in = 2,
    .arg_num_out = 1,
    .num_batches = 31,
    .batch_size = 150,
    .check = 0,
    .sym = NULL,
};
int parse(struct opts *dest, int argc, char *argv[]);

#endif /* ARG_PARSE_H */
