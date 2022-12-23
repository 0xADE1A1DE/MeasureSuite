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

#ifndef STRUCT_HELPERS_H
#define STRUCT_HELPERS_H
#include <measuresuite.h>
#include <stdint.h>

measuresuite_t create_default_ms();
int set_argwidth(measuresuite_t ms, unsigned int arg_width);
int set_argin(measuresuite_t ms, unsigned int arg_in);
int set_argout(measuresuite_t ms, unsigned int arg_out);
int set_chunk_size(measuresuite_t ms, size_t chunk_size);
int set_bounds(measuresuite_t ms, const uint64_t *bounds);
int set_num_batches(measuresuite_t ms, unsigned int num_batches);
int set_batch_size(measuresuite_t ms, unsigned int batch_size);
int validate_num_args(measuresuite_t ms);
#endif
