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

#include "randomizer.h"
#include "error/error.h"
#include <errno.h> //errno
#include <fcntl.h> // open/close
#include <linux/perf_event.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h> // malloc
#include <string.h> //strerror
#include <sys/types.h>
#include <unistd.h> // read/write

static const char randomfile_name[] = {"/dev/urandom"};

int init_random(struct measuresuite *ms) {

  size_t count_uint64s = ms->arg_width * ms->num_arg_in;
  // for the measurement / get_one_random_qword
  ms->random_data_len = count_uint64s + 1;

  // sanity check size
  const size_t size_of_random_bin = 102400;
  if (ms->random_data_len > size_of_random_bin) {
    ms->errorno = E_INVALID_INPUT__IN_TOO_LARGE;
    return 1;
  }

  ms->random_data_fd = -1;
  ms->random_data_fd = open(randomfile_name, O_RDONLY);

  if (ms->random_data_fd == -1) {
    ms->errorno = E_INTERNAL_RANDOMNESS__AI__OPEN_FILE;
    ms->additional_info = strerror(errno);
    return 1;
  }

  // allocate data
  ms->random_data = malloc(ms->random_data_len * sizeof(uint64_t));
  if (ms->random_data == NULL) {
    ms->errorno = E_INTERNAL_RANDOMNESS__AI__MALLOC;
    ms->additional_info = strerror(errno);
    return 1;
  }

  // fill
  if (randomize(ms)) {
    return 1;
  }
  return 0;
}

int randomize(struct measuresuite *ms) {
  if (ms->random_data_fd == -1) {
    ms->errorno = E_INTERNAL_RANDOMNESS__UNINITIALIZED;
    return 1;
  }

  size_t len = ms->random_data_len * sizeof(uint64_t);
  size_t bytes_read = read(ms->random_data_fd, ms->random_data, len);
  if (len != bytes_read) {
    // don't care if its EOF (bytes_read == 0) or fail (bytes_read == -1)
    ms->errorno = E_INTERNAL_RANDOMNESS__AI__READ;
    ms->additional_info = strerror(errno);
    return 1;
  }

  if (ms->bounds != NULL) {
    // only set the bound for the data required. otherwise, It will overwrite
    // data somewhere...
    for (size_t i_na = 0; i_na < ms->num_arg_in; i_na++) {
      for (size_t i_w = 0; i_w < ms->arg_width; i_w++) {
        uint64_t *data = ms->random_data + (i_na * ms->arg_width) + i_w;
        *data &= ms->bounds[i_w];
      }
    }
  }
  return 0;
}

int end_random(struct measuresuite *ms) {
  // free field
  free(ms->random_data);
  ms->random_data = NULL;

  // sanity check
  if (ms->random_data_fd != -1) {
    if (close(ms->random_data_fd)) {
      ms->errorno = E_INTERNAL_RANDOMNESS__AI__CLOSE_FILE;
      ms->additional_info = strerror(errno);
      return 1;
    }
  }
  ms->random_data_fd = -1;
  ms->random_data_len = 0;
  return 0;
}

int get_random_qword(struct measuresuite *ms, uint64_t *dest) {
  if (ms->random_data == NULL ||
      ms->random_data_len < 1 // because it would be more than 0 if it would
                              // have been initialized correctly
  ) {
    ms->errorno = E_INTERNAL_RANDOMNESS__UNINITIALIZED;
    return 1;
  }

  *dest = ms->random_data[ms->random_data_len - 1];
  return 0;
}
// radnom number 0 .. max
int get_random_number(struct measuresuite *ms, size_t max, size_t *dest) {

  // calc mask
  size_t mask = 1;
  do {
    mask = ~(~mask << 1); // shift left 1, will w/1's
  } while (mask < max);

  do {
    if (get_random_qword(ms, dest)) {
      return 1;
    }
    *dest &= mask;
    if (*dest <= max) {
      break;
    }
    randomize(ms);
  } while (1);

  return 0;
}
