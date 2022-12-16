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

#include "load_functions.h"
#include "constants.h"
#include "helper.h"

napi_value loadAsmString(napi_env env, napi_callback_info info) {
  // getting back the instance
  void *instance_data = NULL;
  if (napi_get_instance_data(env, &instance_data) != napi_ok) {
    return throw_and_return_napi_val(env, "Unable to get instance data.");
  }
  measuresuite_t ms = (measuresuite_t)instance_data;

  const size_t argc_init = 1;
  size_t argc = argc_init;

  napi_value argv[argc]; // holds the values

  char asmString[max_len_asmstrings];

  // parse all args
  if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok)
    return throw_and_return_napi_val(env, "Failed to parse arguments");

  // parse asmString
  size_t read_bytes = 0;
  if (napi_get_value_string_latin1(env, *argv, asmString, max_len_asmstrings,
                                   &read_bytes) != napi_ok // read
      || read_bytes == 0                      // none read err check
      || read_bytes == max_len_asmstrings - 1 // too long err check

  ) {
    return throw_and_return_napi_val(env,
                                     "Invalid assemblyString was passed as "
                                     "argument 0, may have been too long.");
  }

  // load Asm data in instance
  int idAsm = -1;
  ms_load_data(ms, ASM, (uint8_t *)asmString, read_bytes, NULL, &idAsm);

  napi_value napi_result = NULL;
  napi_create_int32(env, 0, &napi_result);
  return napi_result;
}

napi_value loadAsmFile(napi_env env, napi_callback_info info) {

  const size_t argc_init = 1;
  size_t argc = argc_init;

  napi_value argv[argc]; // holds the values

  char asmString[max_len_asmstrings];

  // parse all args
  if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok)
    return throw_and_return_napi_val(env, "Failed to parse arguments");

  // parse asmString
  size_t read_bytes = 0;
  if (napi_get_value_string_latin1(env, *argv, asmString, max_len_asmstrings,
                                   &read_bytes) != napi_ok // read
      || read_bytes == 0                      // none read err check
      || read_bytes == max_len_asmstrings - 1 // too long err check

  ) {
    return throw_and_return_napi_val(env,
                                     "Invalid assemblyString was passed as "
                                     "argument 0, may have been too long.");
  }

  // getting back the instance
  void *instance_data = NULL;
  if (napi_get_instance_data(env, &instance_data) != napi_ok) {
    return throw_and_return_napi_val(env, "Unable to get instance data.");
  }
  measuresuite_t ms = (measuresuite_t)instance_data;

  // load Asm data in instance
  int idAsm = -1;
  ms_load_data(ms, ASM, (uint8_t *)asmString, read_bytes, NULL, &idAsm);

  napi_value napi_result = NULL;
  napi_create_int32(env, 0, &napi_result);
  return napi_result;
}
