#ifndef HELPER_H
#define HELPER_H

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

#include <measuresuite.h>
#include <node/node_api.h>
#include <stdio.h>
#include <string.h>

void finalise(napi_env env, void *finalize_data, void *finalize_hint);

void throw_error_return_void(napi_env env, const char *msg);

napi_value throw_and_return_napi_val(napi_env env, const char *msg);
#endif /* HELPER_H */
