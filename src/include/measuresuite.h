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

#ifndef MEASURE_H
#define MEASURE_H

#include <stddef.h>
#include <stdint.h>

typedef struct measuresuite *measuresuite_t;
typedef struct ERROR_NUMBER error_t;

/**
 * This method creates a measuresuite instance and saves the reference to @param
 * *ms.
 * It will check validity of the parameters, allocate memory regions and
 * sets up the measuresuite with
 * @param arg_width is the width of the array, each pointer points to.
 * @param num_arg_in is the amount of `in` pointers
 * @param num_arg_out is the amount of `out` pointers
 * @param chunk_size which chunk_size to consider. Just passed to AssemblyLine
 * @param lib_check_functions_filename filename of where to find the shared
 * object with the symbol
 * @param check_function_symbolname name of the symbol to call.
 *
 * @returns 0 on success
 * @returns 1 on failure
 *
 */
int ms_measure_init(measuresuite_t *ms, int arg_width, int num_arg_in,
                    int num_arg_out, int chunk_size, const uint64_t *bounds,
                    const char *lib_check_functions_filename,
                    const char *check_function_symbolname);

#ifndef NO_AL
/**
 * Needs an init'ed @param ms.
 * Will then assembles @param functionA and @param functionB to memory.
 * Will then randomly run @param batch_size'ed batches; until each function has
 * been called at least @num_batches times.
 *
 * @returns 0 on success
 * @returns 1 on failure
 */
int ms_measure(measuresuite_t ms, char *functionA, char *functionB,
               int batch_size, int num_batches);
#endif

/**
 * will set the json result of the last measurement stored in @param ms to
 * @param json. Will write the length needed for that JSON into @param json_len
 *
 * @returns void
 */
void ms_getJson(measuresuite_t ms, const char **json, size_t *json_len);

/**
 * like ms_measure, but will only measure the symbol from the
 * check_function_symbolname use in conjunction with ms_get_libcycles.
 *
 * @returns 0 on success
 * @returns 1 on failure
 */
int ms_measure_lib_only(measuresuite_t ms, size_t batch_size, int num_batches);

/**
 * will set @param dest to the array of measurements
 * The array will have length of batch_size with which ms_measure_lib_only was
 * called
 *
 * @returns void
 */
void ms_get_libcycles(measuresuite_t ms, uint64_t **dest);

/**
 * Will release all resources allocated with @param ms
 *
 * @returns 0 on success
 * @returns 1 on failure
 */
int ms_measure_end(measuresuite_t ms);

/**
 * Prints the last error of @param ms to stdout
 */
void ms_p_error(measuresuite_t ms);

/**
 * Returns a pointer to the string corresponding to the last error stored in
 * @param ms
 */
const char *ms_str_error(measuresuite_t ms);

/**
 * Prints most @param len chars from the error code to *dest.
 */
void ms_str_full_error(measuresuite_t ms, char *dest, int len);
#endif
