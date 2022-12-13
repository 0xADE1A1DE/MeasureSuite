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

#ifndef MS_ERROR_H
#define MS_ERROR_H
typedef enum {
  E_SUCCESS = 0,
  E_INVALID_INPUT__ARG_WIDTH,
  E_INVALID_INPUT__BOUNDS_NULL,
  E_INVALID_INPUT__NUM_ARG_IN,
  E_INVALID_INPUT__NUM_ARG_OUT,
  E_INVALID_INPUT__NUM_ARG_TOO_LARGE,
  E_INVALID_INPUT__NUM_BATCHES,
  E_INVALID_INPUT__BATCH_SIZE,
  E_INVALID_INPUT__NUM_IDX_OOB,
  E_INVALID_INPUT__IN_TOO_LARGE,
  E_INVALID_INPUT__FILE,
  E_INTERNAL_RANDOMNESS__AI__MALLOC,
  E_INTERNAL_RANDOMNESS__AI__OPEN_FILE,
  E_INTERNAL_RANDOMNESS__AI__READ,
  E_INTERNAL_RANDOMNESS__AI__CLOSE_FILE,
  E_INTERNAL_RANDOMNESS__UNINITIALIZED,
  E_INTERNAL_MEASURE__FREE_A,
  E_INTERNAL_MEASURE__FREE_B,
  E_INTERNAL_MEASURE__AI__DLCLOSE,
  E_INTERNAL_MEASURE__AI__DLSYM,
  E_INTERNAL_MEASURE__AI__DLOPEN,
  E_INTERNAL_MEASURE__AI__ALLOC,
  E_INTERNAL_INITIALIZE__ALLOC,
  E_INTERNAL_FUNCTIONS__NOTHING_TO_UNLOAD,
  E_LOAD__ASM_FILE,
  E_LOAD__SO_FILE,
  E_LOAD__ASM_DATA,
  E_LOAD__ELF_FILE_IO,
  E_LOAD__ELF_FILE_MALLOC,
  E_LOAD__ELF_FILE_INVALID_ELF,
  E_LOAD__ELF_MEM_INVALID_ELF,
  E_LOAD__AL_FREE,
} ERROR_NUMBER;

#endif
