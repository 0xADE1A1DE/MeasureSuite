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
     "The number of in-arguments is invalid (must be between 1 and 6.) I.e. "
     "There must "
     "be at least one arg1 in function_check(out1[n], arg1[n])"},
    {E_INVALID_INPUT__NUM_ARG_OUT,
     "The number of out-arguments is invalid (must be between 1 and 6.) I.e. "
     "There must "
     "be at least one out1 in function_check(out1[n], arg1[n])"},
    {E_INVALID_INPUT__NUM_ARG_TOO_LARGE,
     "The function can at max take 6 parameters. I.e. Sum of number of in/out "
     "arguments must be <=6."},
    {E_INVALID_INPUT__NUM_BATCHES,
     "The given number of batches is invalid. Must be >0."},
    {E_INVALID_INPUT__BATCH_SIZE,
     "The given batch size is invalid. Must be >0."},
    {E_INVALID_INPUT__NUM_IDX_OOB, "The provided index is too large. There is "
                                   "not that many functions loaded."},
    {E_INVALID_INPUT__FILE, "The given file is cannot be stat'ed."},
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
    {E_INTERNAL_MEASURE__AI__DLCLOSE, "Failed to dlclose."},

    {E_INTERNAL_MEASURE__AI__DLSYM, "Failed to dlsym."},
    {E_INTERNAL_MEASURE__AI__DLOPEN, "Failed to dlopen."},

    {E_INTERNAL_MEASURE__AI__ALLOC, "Failed to allocate memory."},
    {E_INTERNAL_FUNCTIONS__NOTHING_TO_UNLOAD,
     "Failed to unload function, because none have been loaded. "},
    {E_INTERNAL_INITIALIZE__ALLOC,
     "Failed to allocate memory internally. Out Of Memory?"},
    {E_LOAD__ASM_FILE, "Cannot load ASM_FILE."},
    {E_LOAD__ASM_DATA, "Cannot load ASM_DATA."},
    {E_LOAD__AL_FREE,
     "Cannot unload Assemblyline. Maybe is has been unloaded alraedy."},
    {E_LOAD__ELF_FILE_IO,
     "An File I/O error occurred while loading the ELF file."},
    {E_LOAD__ELF_FILE_INVALID_ELF,
     "The ELF file does not have the expected format."},
    {E_LOAD__ELF_MEM_INVALID_ELF,
     "The ELF file (memory) does not have the expected format."},
    {E_LOAD__ELF_FILE_MALLOC,
     "An allocation error occurred while loading the ELF file."}

};

const char *get_error_string(ERROR_NUMBER e) {
  for (size_t i = 0; i < sizeof(error_desc) / sizeof(error_desc[0]); i++) {
    if (error_desc[i].errno == e) {
      return error_desc[i].message;
    }
  }
  return NULL;
}
