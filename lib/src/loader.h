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
