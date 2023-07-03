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

#include "enable_functions.h"
#include "helper.h"
#include "load_functions.h"
#include "other_functions.h"
#include <node/node_api.h>

static void register_function(napi_env env, napi_value exports, void *function,
                              const char *symbol) {
  napi_value _function = NULL;

  if (napi_create_function(env, NULL, 0, function, NULL, &_function) !=
      napi_ok) {
    return throw_error_return_void(env, "Unable to wrap native function");
  }

  if (napi_set_named_property(env, exports, symbol, _function) != napi_ok) {
    return throw_error_return_void(env, "Unable to populate exports");
  }
}

napi_value Init(napi_env env, napi_value exports) {

  // init(argWidth: number, numArgIn: number, numArgOut: number): void;
  register_function(env, exports, init, "init");

  // load_asm_string(assembly: string): number;
  register_function(env, exports, load_asm_string, "load_asm_string");
  // load_asm_file(path: string): number;
  register_function(env, exports, load_asm_file, "load_asm_file");
  // load_bin_file(path: string): number;
  register_function(env, exports, load_bin_file, "load_bin_file");
  // load_elf_file(path: string, symbol?: string): number;
  register_function(env, exports, load_elf_file, "load_elf_file");
  // load_shared_object_file(path: string, symbol: string): number;
  register_function(env, exports, load_shared_object_file,
                    "load_shared_object_file");

  // unload_all(): void;
  register_function(env, exports, unload_all, "unload_all");
  // unload(id: number): void;
  register_function(env, exports, unload_last, "unload_last");

  // enable_checking(): void;
  register_function(env, exports, enable_checking, "enable_checking");
  // enable_chunk_counting(chunkSize: number): void;
  register_function(env, exports, enable_chunk_counting,
                    "enable_chunk_counting");
  // set_bounds(bounds: BigUint64Array): void;
  register_function(env, exports, binding_set_bounds, "set_bounds");
  // measure(batchSize: number, numBatches: number): string;
  register_function(env, exports, measure, "measure");

  // get_timer(): number;
  register_function(env, exports, get_timer, "get_timer");

  // destroy(): number;
  register_function(env, exports, destroy, "destroy");

  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
