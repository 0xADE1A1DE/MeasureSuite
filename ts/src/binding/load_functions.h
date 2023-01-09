#ifndef LOAD_FUNCTIONS_H
#define LOAD_FUNCTIONS_H

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
#include <node/node_api.h>

napi_value load_asm_string(napi_env env, napi_callback_info info);
napi_value load_asm_file(napi_env env, napi_callback_info info);
napi_value load_bin_file(napi_env env, napi_callback_info info);
napi_value load_elf_file(napi_env env, napi_callback_info info);
napi_value load_shared_object_file(napi_env env, napi_callback_info info);

#endif /* LOAD_FUNCTIONS_H */
