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

#include "ms_error_description.h"
#include "ms_error.h"
#include "stdio.h" // NULL

static struct error_desc {
  ERROR_NUMBER errno;
  const char *message;
} const error_desc[] = {
    {E_SUCCESS, "No Error"},
    {E_INVALID_INPUT__ARG_WIDTH,
     "The width of an argument must be at least one. This specifies how many "
     "uint64_t the arg1, arg2, ... points to."},
    {E_INVALID_INPUT__BOUNDS_NULL, "The provided bounds pointer is null."},
    {E_INVALID_INPUT__NUM_ARG_IN,
     "The number of in-arguments is invalid (<0 or too big.) I.e. There must "
     "be at least one arg1 in function_check(out1[n], arg1[n])"},
    {E_INVALID_INPUT__NUM_ARG_OUT,
     "The number of out-arguments is invalid (<0 or too big.) I.e. There must "
     "be at least one out1 in function_check(out1[n], arg1[n])"},
    {E_INVALID_INPUT__CHUNK_SIZE,
     "The given chunksize is invalid. Use Chunksize 0 to disable NOP'ing to "
     "chunk boundries."},
    {E_INVALID_INPUT__ASM_FUNCTION_A,
     "The given function function A could not be assembled."},
    {E_INVALID_INPUT__ASM_FUNCTION_B,
     "The given function function B could not be assembled."},
    {E_INVALID_INPUT__LIB_CHECK_FILE_NOT_ACCESSIBLE,
     "The given lib check file is not readable and executable."},
    {E_INTERNAL_RANDOMNESS__AI__MALLOC,
     "Cannot malloc memory for random data."},
    {E_INTERNAL_RANDOMNESS__AI__OPEN_FILE, "Cannot open randomness file."},
    {E_INTERNAL_RANDOMNESS__AI__READ, "Cannot read randomness file."},
    {E_INTERNAL_RANDOMNESS__AI__CLOSE_FILE, "Cannot close randomness file."},
    {E_INVALID_INPUT__IN_TOO_LARGE,
     "The product of num_arg_in and arg_width is too large."},
    {E_INTERNAL_RANDOMNESS__UNINITIALIZED,
     "Randomness was not initialized. Call init_random first."},
    {E_INTERNAL_MEASURE__FREE_A, "Could not free the handle from Function_A"},
    {E_INTERNAL_MEASURE__FREE_B, "Could not free the handle from Function_B"},
    {E_INTERNAL_MEASURE__AI__DLCLOSE, "Failed to dlclose lib_check_function."},

    {E_INTERNAL_MEASURE__AI__DLSYM, "Failed to dlsym."},
    {E_INTERNAL_MEASURE__AI__DLOPEN, "Failed to dlopen lib_check_function."},

    {E_INTERNAL_MEASURE__AI__ALLOC, "Failed to allocate memory."},

};

const char *get_error_string(ERROR_NUMBER e) {
  for (size_t i = 0; i < sizeof(error_desc) / sizeof(error_desc[0]); i++) {
    if (error_desc[i].errno == e) {
      return error_desc[i].message;
    }
  }
  return NULL;
}
