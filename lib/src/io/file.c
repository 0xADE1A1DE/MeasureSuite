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
#include "file.h"
#include "../error/error.h"
#include <debug.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int filesize(measuresuite_t ms, const char *filename, size_t *size) {
  struct stat stats;
  DEBUG("trying to Stat file '%s'\n", filename);
  if (stat(filename, &stats)) {
    ms->errorno = E_INVALID_INPUT__FILE;
    ms->additional_info = strerror(errno);
    return 1;
  }
  *size = stats.st_size;
  return 0;
}

int filecopy(measuresuite_t ms, void *dest, size_t dest_size,
             const char *filename) {
  size_t size = 0;
  if (filesize(ms, filename, &size) || size > dest_size) {
    return 1;
  }

  int file = open(filename, O_RDONLY | O_SYNC);
  if (file == -1                                      // open
      || read(file, dest, dest_size) != (ssize_t)size // read
      || close(file) == -1                            // close
  ) {
    ms->errorno = E_INVALID_INPUT__FILE;
    ms->additional_info = strerror(errno);
    return 1;
  };

  return 0;
}
