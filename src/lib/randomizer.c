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

#include <errno.h> //errno
#include <fcntl.h> // open/close
#include <stdio.h>
#include <stdlib.h> // malloc
#include <string.h> //strerror
#include <unistd.h> // read/write

#include "ms_error.h"
#include "randomizer.h"

static const char randomfile_name[] = {"/dev/urandom"};

int init_random(struct measuresuite *ms) {

  int count_uint64s = ms->arg_width * ms->num_arg_in;
  // for the measurement / get_one_random_byte
  ms->random_data_size_bytes = count_uint64s * sizeof(uint64_t) + 1;

  // sanity check size
  const size_t size_of_random_bin = 102400;
  if (ms->random_data_size_bytes > size_of_random_bin) {
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

  // allocate
  ms->random_data = malloc(ms->random_data_size_bytes);
  if (ms->random_data == NULL) {
    ms->errorno = E_INTERNAL_RANDOMNESS__AI__MALLOC;
    ms->additional_info = strerror(errno);
    return 1;
  }

  // fill
  if (randomize(ms)) {
    // ms->errno will be set inside randomize
    return 1;
  }
  return 0;
}

int randomize(struct measuresuite *ms) {
  if (ms->random_data_fd == -1) {
    ms->errorno = E_INTERNAL_RANDOMNESS__UNINITIALIZED;
    return 1;
  }

  size_t bytes_read =
      read(ms->random_data_fd, ms->random_data, ms->random_data_size_bytes);
  if (ms->random_data_size_bytes != bytes_read) {
    // don't care if its EOF (bytes_read == 0) or fail (bytes_read == -1)
    ms->errorno = E_INTERNAL_RANDOMNESS__AI__READ;
    ms->additional_info = strerror(errno);
    return 1;
  }

  // only set the bound for the data required. otherwise, It will overwrite data
  // somewhere...
  for (int i_na = 0; i_na < ms->num_arg_in; i_na++) {
    for (int i_w = 0; i_w < ms->arg_width; i_w++) {
      uint64_t *d = ms->random_data + (i_na * ms->arg_width) + i_w;
      /** printf("%p: dst[%i][%i] 0x%016lx & 0x%016lx", d, i_na, i_w, *d,
       * ms->bounds[i_w]); */
      *d &= ms->bounds[i_w];
      /** printf("= 0x%016lx\n", *d); */
    }
    /** printf("\n"); */
  }
  return 0;
}

int end_random(struct measuresuite *ms) {
  // free field
  if (ms->random_data != NULL) {
    free(ms->random_data);
    ms->random_data = NULL;
  }

  // sanity check
  if (ms->random_data_fd == -1) {
    ms->errorno = E_INTERNAL_RANDOMNESS__UNINITIALIZED;
    return 1;
  }
  if (close(ms->random_data_fd)) {
    ms->errorno = E_INTERNAL_RANDOMNESS__AI__CLOSE_FILE;
    ms->additional_info = strerror(errno);
    return 1;
  }
  ms->random_data_fd = -1;
  ms->random_data_size_bytes = 0;
  return 0;
}

int get_random_byte(struct measuresuite *ms, uint8_t *dest) {
  if (ms->random_data == NULL) {
    ms->errorno = E_INTERNAL_RANDOMNESS__UNINITIALIZED;
    return 1;
  }
  if (ms->random_data_size_bytes < 1) {
    // because it would be more than 0 if it would have been initialized
    // correctly
    ms->errorno = E_INTERNAL_RANDOMNESS__UNINITIALIZED;
    return 1;
  }
  uint8_t *byteview = (uint8_t *)ms->random_data;
  uint8_t *lastbyte = byteview + ms->random_data_size_bytes - 1;
  *dest = *lastbyte;
  return 0;
}
