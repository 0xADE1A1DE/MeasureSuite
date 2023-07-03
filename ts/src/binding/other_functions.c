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
#include "other_functions.h"
#include "helper.h"
#include "measuresuite.h"
#include <node/js_native_api.h>
#include <stddef.h>
#include <stdint.h>
void init(napi_env env, napi_callback_info info) {
  const size_t argc_init = 3;
  size_t argc = argc_init;

  napi_value argv[argc]; // holds the values
  // this pointer points to the next free element in the argv-array
  napi_value *cur_napi = argv;
  int arg_width = 0;
  int num_arg_in = 0;
  int num_arg_out = 0;

  // parse all args
  if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok)
    return throw_error_return_void(env, "Failed to parse arguments");

  // parse arg_widths
  if (napi_get_value_int32(env, *cur_napi++, &arg_width) != napi_ok)
    return throw_error_return_void(
        env, "Invalid arg_width was passed as argument 0");

  // parse num_args_in
  if (napi_get_value_int32(env, *cur_napi++, &num_arg_in) != napi_ok)
    return throw_error_return_void(
        env, "Invalid num_arg_in was passed as argument 1");

  // parse num_args_out
  if (napi_get_value_int32(env, *cur_napi++, &num_arg_out) != napi_ok)
    return throw_error_return_void(
        env, "Invalid num_arg_out was passed as argument 2");

  // execute measure_init
  measuresuite_t ms = NULL;
  if (ms_initialize(&ms, arg_width, num_arg_in, num_arg_out) != 0) {
    ms_fprintf_error(ms, stderr);
    return throw_error_return_void(env,
                                   "Unable to create measuresuite instance.");
  }

  // save the measuresuite_t handle in as the instance data. and set the
  // finalise callback to call ms_teminate
  if (napi_set_instance_data(env, ms, &finalise, NULL) != napi_ok) {
    return throw_error_return_void(
        env, "Unable to set instance data / finalize_cb.");
  }
}
napi_value destroy(napi_env env, napi_callback_info info) {
  void *instance_data = NULL;
  if (napi_get_instance_data(env, &instance_data) != napi_ok) {
    return throw_and_return_napi_val(env, "Unable to get instance data.");
  }

  measuresuite_t ms = (measuresuite_t)instance_data;
  if (ms_terminate(ms)) {
    throw_and_return_napi_val(env, "Unable to destroy measuresuite instance.");
  }
  napi_value napi_result = NULL;
  napi_create_int32(env, 0, &napi_result);
  return napi_result;
}

napi_value get_timer(napi_env env, napi_callback_info info) {
  void *instance_data = NULL;
  if (napi_get_instance_data(env, &instance_data) != napi_ok &&
      instance_data != NULL) {
    return throw_and_return_napi_val(env, "Unable to get instance data.");
  }

  measuresuite_t ms = (measuresuite_t)instance_data;
  enum TIMER timer = ms_get_timer(ms);
  napi_value napi_result = NULL;

  if (timer == PMC) {
    napi_create_int32(env, 0, &napi_result);
    return napi_result;
  }
  if (timer == RDTSCP) {
    napi_create_int32(env, 1, &napi_result);
    return napi_result;
  }
  napi_create_int32(env, -1, &napi_result);
  return napi_result;
}

napi_value binding_set_bounds(napi_env env, napi_callback_info info) {
  // getting back the instance
  void *instance_data = NULL;
  if (napi_get_instance_data(env, &instance_data) != napi_ok) {
    return throw_and_return_napi_val(env, "Unable to get instance data.");
  }

  measuresuite_t ms = (measuresuite_t)instance_data;

  const size_t argc_setBounds = 1;
  size_t argc = argc_setBounds;

  napi_value argv[argc]; // holds the values

  // parse all args
  if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok)
    return throw_and_return_napi_val(env,
                                     "Failed to parse setBounds arguments");

  // parse bounds (we don't do the reference stuff, because in ms, the bounds
  // array will be copied and managed internally.)
  size_t bounds_len = 0;
  size_t byte_offset = 0;
  uint64_t *bounds = NULL;
  napi_typedarray_type type; // NOLINT as there is no non-init'ed type.

  if (napi_get_typedarray_info(env, argv[0], &type, &bounds_len,
                               (void **)&bounds, NULL,
                               &byte_offset) != napi_ok) {
    const napi_extended_error_info *str = NULL;
    napi_get_last_error_info(env, &str);
    printf("parsing array buffer failed because: %s\n", str->error_message);
    return throw_and_return_napi_val(
        env, "Invalid arraybuffer was passed as argument 4");
  }

  if (type != napi_biguint64_array) {
    return throw_and_return_napi_val(
        env, "Invalid object was passed as argument 4. Expected arraybuffer.");
  }

  if (ms_set_bounds(ms, bounds) != 0) {
    ms_fprintf_error(ms, stderr);
    return throw_and_return_napi_val(env, "Could not set Bounds on MS.");
  };

  napi_value napi_result = NULL;
  napi_create_int32(env, 0, &napi_result);
  return napi_result;
};

napi_value measure(napi_env env, napi_callback_info info) {
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
  int32_t batch_size = 0;
  // parse num_args_out
  if (napi_get_value_int32(env, argv[0], &batch_size) != napi_ok) {
    return throw_and_return_napi_val(
        env, "Invalid batch size was passed as argument 0");
  }
  int32_t num_batches = 0;
  // parse num_args_out
  if (napi_get_value_int32(env, argv[1], &num_batches) != napi_ok) {
    return throw_and_return_napi_val(
        env, "Invalid number of batches was passed as argument 1");
  }

  if (ms_measure(ms, batch_size, num_batches) != 0) {
    ms_fprintf_error(ms, stderr);
    return throw_and_return_napi_val(env, "Could not measure.");
  };

  // get json and return string
  const char *json = NULL;
  size_t json_len = 0;
  ms_get_json(ms, &json, &json_len);
  napi_value napi_result = NULL;
  napi_create_string_latin1(env, json, json_len, &napi_result);

  return napi_result;
};
