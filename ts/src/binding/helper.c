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

#include "helper.h"
// NOLINTNEXTLINE (must declare hint as a valid callback for NODE_API)
void finalise(napi_env env, void *finalize_data, void *finalize_hint) {
  if (ms_terminate((measuresuite_t)finalize_data)) {
    if (napi_throw_error(env, NULL, "measure_end didnt work.") != napi_ok) {
      fprintf(stderr, "Unable to throw error.\n");
    }
  }
}

void throw_error_return_void(napi_env env, const char *msg) {
  // getting back the instance
  void *instance_data = NULL;
  if (napi_get_instance_data(env, &instance_data) == napi_ok) {
    // and call finalise here (to not cause memory leaks)
    finalise(env, instance_data, NULL);
  } else {
    fprintf(stderr, "Unable to get instance data.\n");
  }
  if (napi_throw_error(env, NULL, msg) != napi_ok) {
    fprintf(stderr, "Unable to throw error.\n");
  }
}

napi_value throw_and_return_napi_val(napi_env env, const char *msg) {
  throw_error_return_void(env, msg);
  napi_value res = NULL;
  const char errmsg[] = {"Error, see exception"};
  napi_create_string_latin1(env, errmsg, strlen(errmsg), &res);
  return res;
}
