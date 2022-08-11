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

// measuresuite.c
#include <node/node_api.h>
#include <stdio.h>
#include <string.h>

#include <measuresuite.h>

// how many arguments the measuresuite_init function takes
#define MS_INIT_ARGC 7
// how many arguments the measure function takes
#define MS_MEASURE_ARGC 4

// how may chars are allowed for the filename for the
// /path/to/libcheckfunctions-clang-AMD.so
#define MS_INIT_LIB_CHECK_FILE_NAME_MAX_LEN 10240
// how many chars are allowed for the symbol within the lib
#define MS_INIT_SYMBOL_NAME_MAX_LEN 10240

// how many chars are allowed for the function A/ B
#define MS_MEASURE_FUNCTION_MAX_LEN 1024000

// NOLINTNEXTLINE (must declare hint as a valid callback for NODE_API)
void finalise(napi_env env, void *finalize_data, void *finalize_hint) {
  if (ms_measure_end((measuresuite_t)finalize_data)) {
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

void measuresuite_init(napi_env env, napi_callback_info info) {
  size_t argc = MS_INIT_ARGC;
  napi_value argv[MS_INIT_ARGC]; // holds the values
  // this pointer points to the next free element in the argv-array
  napi_value *cur_napi = argv;
  int arg_width = 0;
  int num_arg_in = 0;
  int num_arg_out = 0;
  int chunksize = 0;

  char lib_check_functions_filename[MS_INIT_LIB_CHECK_FILE_NAME_MAX_LEN];
  char check_function_symbolname[MS_INIT_SYMBOL_NAME_MAX_LEN];

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

  // parse chunksize
  if (napi_get_value_int32(env, *cur_napi++, &chunksize) != napi_ok)
    return throw_error_return_void(
        env, "Invalid chunksize was passed as argument 3");

  // parse bounds (we don't do the reference stuff, because in ms, the bounds
  // array will be copied and managed internally.)
  size_t bounds_len = 0;
  size_t byte_offset = 0;
  uint64_t *bounds = NULL;
  napi_typedarray_type type; // NOLINT as there is no non-init'ed type.

  if (napi_get_typedarray_info(env, *cur_napi++, &type, &bounds_len,
                               (void **)&bounds, NULL,
                               &byte_offset) != napi_ok) {
    const napi_extended_error_info *s = NULL;
    napi_get_last_error_info(env, &s);
    printf("parsing array buffer failed because: %s\n", s->error_message);
    return throw_error_return_void(
        env, "Invalid arraybuffer was passed as argument 4");
  }
  if (type != napi_biguint64_array) {
    return throw_error_return_void(
        env, "Invalid object was passed as argument 4. Expected arraybuffer.");
  }

  if (bounds_len != (size_t)arg_width) {
    printf("parsing arraybuffer yielded the wrond sizes %lu vs expected %d.\n",
           bounds_len, arg_width);
    return throw_error_return_void(
        env, "Invalid arraybuffer length mismatch array and arg_width.");
  }

  size_t read_bytes = 0;
  // parse lib_check_functions_filename
  if (napi_get_value_string_utf8(env, *cur_napi++, lib_check_functions_filename,
                                 MS_INIT_LIB_CHECK_FILE_NAME_MAX_LEN,
                                 &read_bytes) != napi_ok ||
      read_bytes == 0 || read_bytes == MS_INIT_LIB_CHECK_FILE_NAME_MAX_LEN - 1)
    return throw_error_return_void(
        env, "Invalid lib_check_functions_filename was passed as "
             "argument 5, may have been too long.");

  // parse check_function_symbolname
  if (napi_get_value_string_utf8(env, *cur_napi++, check_function_symbolname,
                                 MS_INIT_SYMBOL_NAME_MAX_LEN,
                                 &read_bytes) != napi_ok ||
      read_bytes == 0 || read_bytes == MS_INIT_SYMBOL_NAME_MAX_LEN - 1)
    return throw_error_return_void(
        env, "Invalid check_function_symbolname was passed as "
             "argument 6, may have been too long.");

  // execute measure_init
  measuresuite_t ms = NULL;
  if (ms_measure_init(&ms, arg_width, num_arg_in, num_arg_out, chunksize,
                      bounds, lib_check_functions_filename,
                      check_function_symbolname) != 0) {
    ms_p_error(ms);
    return throw_error_return_void(env,
                                   "Unable to create measuresuite instance.");
  }

  // save the measuresuite_t handle in as the instance data. and set the
  // finalise callback to call measure end
  if (napi_set_instance_data(env, ms, &finalise, NULL) != napi_ok) {
    return throw_error_return_void(
        env, "Unable to set instance data / finalize_cb.");
  }

  /** napi_value napi_result; */
  /** napi_create_int32(env, 0, &napi_result); */
  /** return napi_result; */
}

napi_value measuresuite_measure(napi_env env, napi_callback_info info) {

  // getting back the instance
  void *instance_data = NULL;
  if (napi_get_instance_data(env, &instance_data) != napi_ok) {
    return throw_and_return_napi_val(env, "Unable to get instance data.");
  }
  measuresuite_t ms = (measuresuite_t)instance_data;

  // argument parsing
  size_t argc = MS_MEASURE_ARGC;
  napi_value argv[MS_MEASURE_ARGC]; // holds the values;
  // this pointer points to the next free element in the argv-array
  napi_value *cur_napi = argv;
  int batchSize = 0;
  int numBatches = 0;

  char functionA[MS_MEASURE_FUNCTION_MAX_LEN];
  char functionB[MS_MEASURE_FUNCTION_MAX_LEN];

  // parse all args
  if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok)
    return throw_and_return_napi_val(env, "Failed to parse arguments");

  size_t read_bytes = 0;
  // parse function_A
  if (napi_get_value_string_latin1(env, *cur_napi++, functionA,
                                   MS_MEASURE_FUNCTION_MAX_LEN,
                                   &read_bytes) != napi_ok ||
      read_bytes == 0 || read_bytes == MS_MEASURE_FUNCTION_MAX_LEN - 1) {
    return throw_and_return_napi_val(env,
                                     "Invalid function_A was passed as "
                                     "argument 0, may have been too long.");
  }

  if (napi_get_value_string_latin1(env, *cur_napi++, functionB,
                                   MS_MEASURE_FUNCTION_MAX_LEN,
                                   &read_bytes) != napi_ok ||
      read_bytes == 0 || read_bytes == MS_MEASURE_FUNCTION_MAX_LEN - 1)
    return throw_and_return_napi_val(env,
                                     "Invalid function_B was passed as "
                                     "argument 1, may have been too long.");

  // parse batchSize
  if (napi_get_value_int32(env, *cur_napi++, &batchSize) != napi_ok)
    return throw_and_return_napi_val(
        env, "Invalid batchSize was passed as argument 2");

  // parse numBatches
  if (napi_get_value_int32(env, *cur_napi++, &numBatches) != napi_ok)
    return throw_and_return_napi_val(
        env, "Invalid numBatches was passed as argument 3");

  // measure
  int measure_res = ms_measure(ms, functionA, functionB, batchSize, numBatches);
  if (measure_res != 0) {
    return throw_and_return_napi_val(env, ms_str_error(ms));
  }

  size_t json_len = 0;
  const char *json = NULL;
  napi_value result = NULL;
  ms_getJson(ms, &json, &json_len);

  if (napi_create_string_latin1(env, json, json_len, &result) != napi_ok) {
    return throw_and_return_napi_val(env, "Unable to create result json.");
  }

  return result;
}

napi_value measuresuite_measure_lib_only(napi_env env,
                                         napi_callback_info info) {

  // getting back the instance
  void *instance_data = NULL;
  if (napi_get_instance_data(env, &instance_data) != napi_ok) {
    return throw_and_return_napi_val(env, "Unable to get instance data.");
  }
  measuresuite_t ms = (measuresuite_t)instance_data;

  // argument parsing
  size_t argc = MS_MEASURE_ARGC;
  napi_value argv[MS_MEASURE_ARGC]; // holds the values;
  // this pointer points to the next free element in the argv-array
  napi_value *cur_napi = argv;
  int batchSize = 0;
  int numBatches = 0;

  // parse all args
  if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok)
    return throw_and_return_napi_val(env, "Failed to parse arguments");

  // parse batchSize
  if (napi_get_value_int32(env, *cur_napi++, &batchSize) != napi_ok)
    return throw_and_return_napi_val(
        env, "Invalid batchSize was passed as argument 1");

  // parse numBatches
  if (napi_get_value_int32(env, *cur_napi++, &numBatches) != napi_ok)
    return throw_and_return_napi_val(
        env, "Invalid numBatches was passed as argument 1");

  // measure
  int measure_res = ms_measure_lib_only(ms, batchSize, numBatches);
  if (measure_res != 0) {
    return throw_and_return_napi_val(env, ms_str_error(ms));
  }

  // get a pointer to the cycle results
  const uint64_t *cycle_results = NULL;
  ms_get_libcycles(ms, &cycle_results);

  // length of elements in the typed array
  size_t length = (size_t)numBatches;

  // WE WILL CAST THEM TO uint32_t!

  // create a JS arraybuffer from it
  napi_value result = NULL;
  if (napi_create_arraybuffer(env, sizeof(uint32_t) * length, NULL, &result)) {
    return throw_and_return_napi_val(env,
                                     "Unable to create result arraybuffer.");
  }

  // fill the array
  napi_value js_element;
  uint32_t c_element;

  for (size_t i = 0; i < length; i++) {
    c_element = (uint32_t)cycle_results[i];

    if (napi_create_uint32(env, c_element, &js_element) != napi_ok ||
        napi_set_element(env, result, i, js_element) != napi_ok) {
      return throw_and_return_napi_val(env, "Unable to create result array.");
    };
  };

  return result;
}

void registerFunction(napi_env env, napi_value exports, void *function,
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

  registerFunction(env, exports, measuresuite_init, "measuresuite_init");
  registerFunction(env, exports, measuresuite_measure, "measuresuite_measure");
  registerFunction(env, exports, measuresuite_measure_lib_only,
                   "measuresuite_measure_lib_only");

  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
