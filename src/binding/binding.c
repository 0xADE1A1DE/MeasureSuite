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

#include "enable_functions.h"
#include "helper.h"
#include "load_functions.h"
#include "other_functions.h"
#include <node/node_api.h>

static void registerFunction(napi_env env, napi_value exports, void *function,
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
  registerFunction(env, exports, init, "init");
  // loadAsmString(assembly: string): string;
  registerFunction(env, exports, loadAsmString, "loadAsmString");
  // loadAsmFile(path: string): string;
  registerFunction(env, exports, loadAsmFile, "loadAsmFile");
  // loadBinFile(path: string): string;
  registerFunction(env, exports, loadBinFile, "loadBinFile");
  // loadElfFile(path: string, symbol?: string): string;
  registerFunction(env, exports, loadElfFile, "loadElfFile");
  // loadSharedObjectFile(path: string, symbol: string): string;
  registerFunction(env, exports, loadSharedObjectFile, "loadSharedObjectFile");
  // enableChecking(): void;
  registerFunction(env, exports, enableChecking, "enableChecking");
  // enableChunkCounting(chunkSize: number): void;
  registerFunction(env, exports, enableChunkCounting, "enableChunkCounting");
  // setBounds(bounds: BigUint64Array): void;
  registerFunction(env, exports, setBounds, "setBounds");
  // measure(batchSize: number, numBatches: number): string;
  registerFunction(env, exports, measure, "measure");

  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
