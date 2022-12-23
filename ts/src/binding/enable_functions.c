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
#include "constants.h"
#include "helper.h"
#include <measuresuite.h>

napi_value enable_checking(napi_env env, napi_callback_info info) {
  // getting back the instance
  void *instance_data = NULL;
  if (napi_get_instance_data(env, &instance_data) != napi_ok) {
    return throw_and_return_napi_val(env, "Unable to get instance data.");
  }

  measuresuite_t ms = (measuresuite_t)instance_data;

  const size_t argc_measure = 2;
  size_t argc = argc_measure;

  napi_value argv[argc]; // holds the values

  // parse all args
  if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok)
    return throw_and_return_napi_val(env,
                                     "Failed to parse setBounds arguments");
  ms_set_checking(ms, 1);

  napi_value napi_result = NULL;
  napi_create_int32(env, 0, &napi_result);
  return napi_result;
}
napi_value enable_chunk_counting(napi_env env, napi_callback_info info) {
  // getting back the instance
  void *instance_data = NULL;
  if (napi_get_instance_data(env, &instance_data) != napi_ok) {
    return throw_and_return_napi_val(env, "Unable to get instance data.");
  }
  measuresuite_t ms = (measuresuite_t)instance_data;

  const size_t argc_init = 1;
  size_t argc = argc_init;

  napi_value argv[argc]; // holds the values

  // parse all args
  if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok)
    return throw_and_return_napi_val(env, "Failed to parse arguments");

  int32_t chunk_size = 0;
  // parse chunk size
  if (napi_get_value_int32(env, argv[0], &chunk_size) != napi_ok) {
    return throw_and_return_napi_val(
        env, "Invalid chunk size was passed as argument 0");
  }

  // load Asm data in instance
  if (ms_set_chunk_size(ms, chunk_size) != 0) {
    ms_fprintf_error(ms, stderr);
    return throw_and_return_napi_val(env, "Could not set chunk size to MS");
  }

  napi_value napi_result = NULL;
  napi_create_int32(env, 0, &napi_result);
  return napi_result;
}
