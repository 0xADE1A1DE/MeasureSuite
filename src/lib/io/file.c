#include "file.h"
#include "../ms_error.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
int filesize(measuresuite_t ms, const char *filename, size_t *size) {
  struct stat st;
  if (stat(filename, &st)) {
    ms->errorno = E_INVALID_INPUT__FILE;
    ms->additional_info = strerror(errno);
    return 1;
  }
  *size = st.st_size;
  return 0;
}

int filecopy(measuresuite_t ms, void *dest, size_t dest_size,
             const char *filename) {
  size_t size = 0;
  if (filesize(ms, filename, &size) || size > dest_size) {
    return 1;
  }

  int fd = -1;
  if ((fd = open(filename, O_RDONLY | O_SYNC)) == -1 // open
      || read(fd, dest, dest_size) != (ssize_t)size  // read
      || close(fd) == -1                             // close
  ) {
    ms->errorno = E_INVALID_INPUT__FILE;
    ms->additional_info = strerror(errno);
    return 1;
  };

  return 0;
}
