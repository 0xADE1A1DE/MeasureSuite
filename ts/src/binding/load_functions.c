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
#include "measuresuite.h"

napi_value load_asm_string(napi_env env, napi_callback_info info) {
  // getting back the instance
  void *instance_data = NULL;
  if (napi_get_instance_data(env, &instance_data) != napi_ok) {
    return throw_and_return_napi_val(env, "Unable to get instance data.");
  }
  measuresuite_t ms = (measuresuite_t)instance_data;

  const size_t argc_init = 1;
  size_t argc = argc_init;

  napi_value argv[argc]; // holds the values

  char asm_string[max_len_asmstrings];

  // parse all args
  if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok)
    return throw_and_return_napi_val(env, "Failed to parse arguments");

  // parse asmString
  size_t read_bytes = 0;
  if (napi_get_value_string_latin1(env, *argv, asm_string, max_len_asmstrings,
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
  if (ms_load_data(ms, ASM, (uint8_t *)asm_string, read_bytes, NULL, &idAsm) !=
      0) {
    ms_fprintf_error(ms, stderr);
    return throw_and_return_napi_val(
        env, "MS error'ed whille loading assemblyString.");
  };

  napi_value napi_result = NULL;
  napi_create_int32(env, idAsm, &napi_result);
  return napi_result;
}

napi_value load_asm_file(napi_env env, napi_callback_info info) {

  const size_t argc_init = 1;
  size_t argc = argc_init;

  napi_value argv[argc]; // holds the values

  char asm_file[max_len_paths];

  // parse all args
  if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok)
    return throw_and_return_napi_val(env, "Failed to parse arguments");

  // parse asmString
  size_t read_bytes = 0;
  if (napi_get_value_string_latin1(env, *argv, asm_file, max_len_asmstrings,
                                   &read_bytes) != napi_ok // read
      || read_bytes == 0                      // none read err check
      || read_bytes == max_len_asmstrings - 1 // too long err check

  ) {
    return throw_and_return_napi_val(env,
                                     "Invalid assembly filename was passed as "
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
  if (ms_load_file(ms, ASM, asm_file, NULL, &idAsm) != 0) {
    ms_fprintf_error(ms, stderr);
    return throw_and_return_napi_val(
        env, "MS error'ed whille loading assemblyString.");
  };

  napi_value napi_result = NULL;
  napi_create_int32(env, idAsm, &napi_result);
  return napi_result;
}

napi_value load_bin_file(napi_env env, napi_callback_info info) {
  // getting back the instance
  void *instance_data = NULL;
  if (napi_get_instance_data(env, &instance_data) != napi_ok) {
    return throw_and_return_napi_val(env, "Unable to get instance data.");
  }
  measuresuite_t ms = (measuresuite_t)instance_data;

  const size_t argc_init = 1;
  size_t argc = argc_init;

  napi_value argv[argc]; // holds the values

  char bin_filename[max_len_paths];

  // parse all args
  if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok)
    return throw_and_return_napi_val(env, "Failed to parse arguments");

  // parse filename
  size_t read_bytes = 0;
  if (napi_get_value_string_latin1(env, argv[0], bin_filename, max_len_paths,
                                   &read_bytes) != napi_ok // read
      || read_bytes == 0                 // none read err check
      || read_bytes == max_len_paths - 1 // too long err check

  ) {
    return throw_and_return_napi_val(env,
                                     "Invalid bin filename was passed as "
                                     "argument 0, may have been too long.");
  }

  // load bin data in instance
  int id_bin = -1;
  if (ms_load_file(ms, BIN, bin_filename, NULL, &id_bin) != 0) {
    ms_fprintf_error(ms, stderr);
    return throw_and_return_napi_val(env, "Could not load bin file to MS.");
  };

  napi_value napi_result = NULL;
  napi_create_int32(env, id_bin, &napi_result);
  return napi_result;
}

napi_value load_elf_file(napi_env env, napi_callback_info info) {
  // getting back the instance
  void *instance_data = NULL;
  if (napi_get_instance_data(env, &instance_data) != napi_ok) {
    return throw_and_return_napi_val(env, "Unable to get instance data.");
  }
  measuresuite_t ms = (measuresuite_t)instance_data;

  const size_t argc_init = 2;
  size_t argc = argc_init;

  napi_value argv[argc]; // holds the values

  char elf_filename[max_len_paths];
  char elf_symbol[max_len_symbol];

  // parse all args
  if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok)
    return throw_and_return_napi_val(env, "Failed to parse arguments");

  // parse filename
  size_t read_bytes = 0;
  if (napi_get_value_string_latin1(env, argv[0], elf_filename, max_len_paths,
                                   &read_bytes) != napi_ok // read
      || read_bytes == 0                 // none read err check
      || read_bytes == max_len_paths - 1 // too long err check

  ) {
    return throw_and_return_napi_val(env,
                                     "Invalid elf filename was passed as "
                                     "argument 0, may have been too long.");
  }

  // parse symbol name
  if (napi_get_value_string_latin1(env, argv[1], elf_symbol, max_len_symbol,
                                   &read_bytes) != napi_ok // read
      // may have been empty, which is ok
      || read_bytes == max_len_symbol - 1 // too long err check

  ) {
    return throw_and_return_napi_val(env,
                                     "Invalid elf filename was passed as "
                                     "argument 1, may have been too long.");
  }

  // load elf data in instance
  int id_elf = -1;
  if (ms_load_file(ms, ELF, elf_symbol, elf_symbol, &id_elf) != 0) {
    ms_fprintf_error(ms, stderr);
    return throw_and_return_napi_val(env, "Could not load bin file to MS.");
  };

  napi_value napi_result = NULL;
  napi_create_int32(env, id_elf, &napi_result);
  return napi_result;
}

napi_value load_shared_object_file(napi_env env, napi_callback_info info) {
  // getting back the instance
  void *instance_data = NULL;
  if (napi_get_instance_data(env, &instance_data) != napi_ok) {
    return throw_and_return_napi_val(env, "Unable to get instance data.");
  }
  measuresuite_t ms = (measuresuite_t)instance_data;

  const size_t argc_init = 2;
  size_t argc = argc_init;

  napi_value argv[argc]; // holds the values

  char so_filename[max_len_paths];
  char so_symbol[max_len_symbol];

  // parse all args
  if (napi_get_cb_info(env, info, &argc, argv, NULL, NULL) != napi_ok)
    return throw_and_return_napi_val(env, "Failed to parse arguments");

  // parse filename
  size_t read_bytes = 0;
  if (napi_get_value_string_latin1(env, argv[0], so_filename, max_len_paths,
                                   &read_bytes) != napi_ok // read
      || read_bytes == 0                 // none read err check
      || read_bytes == max_len_paths - 1 // too long err check

  ) {
    return throw_and_return_napi_val(env,
                                     "Invalid so filename was passed as "
                                     "argument 0, may have been too long.");
  }
  if (napi_get_value_string_latin1(env, argv[1], so_symbol, max_len_symbol,
                                   &read_bytes) != napi_ok // read
      || read_bytes == 0                 // none read err check
      || read_bytes == max_len_paths - 1 // too long err check

  ) {
    return throw_and_return_napi_val(env,
                                     "Invalid so symbolname was passed as "
                                     "argument 1, may have been too long.");
  }

  // load SO data in instance
  int id_so = -1;
  if (ms_load_file(ms, SHARED_OBJECT, so_filename, so_symbol, &id_so) != 0) {
    ms_fprintf_error(ms, stderr);
    return throw_and_return_napi_val(
        env, "Could not load shared object file to MS.");
  };

  napi_value napi_result = NULL;
  napi_create_int32(env, id_so, &napi_result);
  return napi_result;
}
