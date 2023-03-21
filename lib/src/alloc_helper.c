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
#include "alloc_helper.h"
#include "debug.h"
#include "error/error.h"
#include "struct_measuresuite.h"
#include <errno.h> // errno
#include <fcntl.h> // open
#include <stdint.h>
#include <stdlib.h>   // realloc
#include <string.h>   // strerror
#include <sys/mman.h> // mmap...
#include <unistd.h>   // close

int realloc_or_fail(struct measuresuite *ms, void **dest, size_t new_len) {

  DEBUG("Reallocing to new length of %d bytes\n", new_len);

  *dest = realloc(*dest, new_len);

  if (*dest == NULL) {
    ms->errorno = E_INTERNAL_MEASURE__AI__ALLOC;
    ms->additional_info = strerror(errno);
    return 1;
  }

  return 0;
}

int map_rwx(struct measuresuite *ms, void **dest, size_t new_len) {
  int fd_zero = open("/dev/zero", O_RDWR);
  if (fd_zero == -1) {
    ms->errorno = E_INTERNAL_MEASURE__AI__ALLOC;
    ms->additional_info = strerror(errno);
    return 1;
  }

  *dest = mmap(NULL, new_len, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE,
               fd_zero, 0);
  // NOLINTNEXTLINE
  if (*dest == MAP_FAILED) {
    ms->errorno = E_INTERNAL_MEASURE__AI__ALLOC;
    ms->additional_info = strerror(errno);
    return 1;
  }

  if (close(fd_zero) == -1) { /*No longer needed*/
    ms->errorno = E_INTERNAL_MEASURE__AI__ALLOC;
    ms->additional_info = strerror(errno);
    return 1;
  }

  return 0;
}

int realloc_rwx_or_fail(struct measuresuite *ms, void **dest, size_t old_len,
                        size_t new_len) {
  // not using mremap here, because it may clash with errno (and USE_GNU)
  if (munmap(*dest, old_len)) {
    ms->errorno = E_INTERNAL_MEASURE__AI__ALLOC;
    ms->additional_info = strerror(errno);
    return 1;
  }

  return map_rwx(ms, *dest, new_len);
}

int unmap(struct measuresuite *ms, void *dest, size_t old_len) {
  if (munmap(dest, old_len)) {
    ms->errorno = E_INTERNAL_MEASURE__AI__ALLOC;
    ms->additional_info = strerror(errno);
    return 1;
  }

  return 0;
}

int init_arithmetic_results(measuresuite_t ms, struct function_tuple *fct) {

  /** Arithmetic Res */
  /** +---------------------------------------------------------+ */
  /** |         out1 , out2, ... , out[#numArgOut]              | */
  /** +---------------------------------------------------------+ */
  /**     ^---   out1 * arg_width */

  /** Out1  each sizeof(u64)*/
  /** +---------------------------------------------------------+ */
  /** |         out1[0] , out1[1], ... , out1[#arg_width]       | */
  /** +---------------------------------------------------------+ */

  size_t size = ms->arg_width * ms->num_arg_out * sizeof(uint64_t);
  DEBUG("init_arithmetic_results, size: %d\n", size);

  fct->arithmetic_results = malloc(size);

  if (fct->arithmetic_results == NULL) {
    ms->errorno = E_INTERNAL_MEASURE__AI__ALLOC;
    ms->additional_info = strerror(errno);
    return 1;
  }

  return 0;
}

int init_cycle_results(struct measuresuite *ms) {

  FOR_EACH_FUNCTION {

    fct->cycle_results = malloc(ms->num_batches * sizeof(uint64_t));

    if (fct->cycle_results == 0) {
      ms->errorno = E_INTERNAL_MEASURE__AI__ALLOC;
      ms->additional_info = strerror(errno);
      return 1;
    }
  }

  return 0;
}

int init_json(struct measuresuite *ms) {

  const unsigned long char_per_long = 10;
  // at max, every function poduces one long per batch
  const unsigned long char_per_batch = char_per_long * ms->size_functions;

  // every batch produces char_per_batch' chars
  const unsigned long dynamic_length = char_per_batch * ms->num_batches;

  // the static stuff...
  const int len_other_stats = 1025;
  ms->json_len = len_other_stats + dynamic_length;

  ms->json = calloc(ms->json_len, sizeof(char));
  if (ms->json == NULL) {
    ms->errorno = E_INTERNAL_MEASURE__AI__ALLOC;
    ms->additional_info = strerror(errno);
    return 1;
  }

  return 0;
}
