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
#ifndef ALLOC_HELPER_H
#define ALLOC_HELPER_H

#include "struct_measuresuite.h"
#include <inttypes.h>

int realloc_or_fail(struct measuresuite *ms, void **dest, size_t new_len);
int map_rwx(struct measuresuite *ms, void **dest, size_t new_len);
int realloc_rwx_or_fail(struct measuresuite *ms, void **dest, size_t old_len,
                        size_t new_len);
int unmap(struct measuresuite *ms, void *dest, size_t old_len);
int init_arithmetic_results(measuresuite_t ms, struct function_tuple *fct);
int init_cycle_results(struct measuresuite *ms);
int init_json(struct measuresuite *ms);

#endif
