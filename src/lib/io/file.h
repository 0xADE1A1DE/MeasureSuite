#ifndef FILE_H
#define FILE_H

#include "../struct_measuresuite.h"
int filesize(measuresuite_t ms, const char *filename, size_t *size);
int filecopy(measuresuite_t ms, void *dest, size_t dest_size,
             const char *filename);
#endif
