#ifndef LOADER_H
#define LOADER_H
#include "measuresuite.h"
#include <stdlib.h>

int load_file(measuresuite_t ms, enum load_type type, const char *filename,
              const char *symbol, int *id);

int load_data(measuresuite_t ms, enum load_type type, const uint8_t *data,
              size_t data_len, const char *symbol, int *id);
int unload(measuresuite_t ms, size_t id);
#endif
