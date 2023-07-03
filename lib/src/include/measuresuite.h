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

#ifndef MEASURESUITE_H
#define MEASURESUITE_H

#include <stddef.h> // size_t
#include <stdint.h> // uint64_t's
#include <stdio.h>  // FILE

typedef struct measuresuite *measuresuite_t;

/**
 *
 * Unless otherwise specified, all functions returning an int, will
 * return 0 on success and
 * return 1 on error.
 *
 * */

/**
 * This method creates a measuresuite instance and saves the reference to @param
 * *ms.
 * It will check validity of the parameters, allocate memory regions and
 * sets up the measuresuite with
 * @param arg_width is the width of the array, each pointer points to.
 * @param num_arg_in is the amount of `in` pointers
 * @param num_arg_out is the amount of `out` pointers
 *
 *
 */
int ms_initialize(measuresuite_t *ms, int arg_width, int num_arg_in,
                  int num_arg_out);

/**
 * sets @param chunk_size just passed to AssemblyLine when assembling asm-data.
 */
int ms_set_bounds(measuresuite_t ms, const uint64_t *bounds);

/**
 * sets @param chunk_size just passed to AssemblyLine when assembling asm-data.
 * When used, the resulting JSON will fill the 'chunks' property.
 */
int ms_set_chunk_size(measuresuite_t ms, size_t chunk_size);

/**
 * This will control correctness checking.
 *
 * if @param control is 0, correctness checks are disabled,
 * enabled otherwise.
 *
 * if enabled, all functions must calculate the same.
 */
void ms_set_checking(measuresuite_t ms, int control);

/**
 * Those load_types are used in ms_load_{file,data}. See the documentaion there
 * for explanation.
 */
enum load_type { ASM, BIN, ELF, SHARED_OBJECT };

/**
 * Loads a function from a file.
 * Will use the next free slot if @param id is set to -1; subsequently write the
 * given number into @param id Will overwrite an existing function, if @param
 * @id is set to some slot number
 *
 * Accpets different types of files.
 *
 *
 * load_type ASM
 *
 * @param filename must be a path to a file containing Intel-assembly (*.asm),
 * which is passed to AssemblyLine.
 * @param symbol is ignored.
 *
 *
 * load_type BIN
 *
 * @param filename must be a path to a file containing machinecode (*.bin).
 * @param symbol is ignored.
 *
 *
 * load_type ELF
 *
 * @param filename must be a path to an elf-file (*.o).
 * The symbol table from it will be read.
 * If @param symbol is not NULL, the respective symbol is loaded.
 * Otherwise the first found symbol is loaded.
 *
 *
 * load_type SHARED_OBJECT
 *
 * @param filename must be a path to a shared object file (*.so).
 * The file is `dlopen`ed
 * subsequently, the @param symbol is `dlsym`ed on the library.
 *
 */

int ms_load_file(measuresuite_t ms, enum load_type type, const char *filename,
                 const char *symbol, int *id);

/**
 *
 * Same as ms_load_file, but reads from memory instead.
 *
 * load_type ASM
 *
 * @param data must be point to a NUL-terminated string containing
 * Intel-assembly which is passed to AssemblyLine.
 * @param symbol is ignored.
 * @param data_len is ignored.
 *
 *
 * load_type BIN
 *
 * @param data must point to machinecode. Exactly @param data_len bytes will be
 * copied.
 * @param symbol is ignored.
 *
 *
 * load_type ELF
 *
 * @param data must constain an elf-file in memeory
 * The symbol table from it will be read.
 * If @param symbol is not NULL, the respective symbol is loaded.
 * Otherwise the first found symbol is loaded.
 * @param data_len is ignored.
 *
 * load_type SHARED_OBJECT
 * invalid. Use ms_load_file instead.
 */

int ms_load_data(measuresuite_t ms, enum load_type type, const uint8_t *data,
                 size_t data_len, const char *symbol, int *id);

/*
 * will unload and free all memory associated with functions. The next load_xxx
 * will be put into id=0
 */
int ms_unload_all(measuresuite_t ms);

/*
 * will unload and free the last memory associated with functions. The next
 * load_xxx will be put into the same place as the previous load.
 */
int ms_unload_last(measuresuite_t ms);

/**
 * Will then assembles @param functionA and @param functionB to memory.
 * Will then randomly run @param batch_size'ed batches; until each function has
 * been called at least @num_batches times.
 *
 * if checking is enabled, will early abort if one function is detected to
 * calcultate a different result than the previous then @returns 1
 */
int ms_measure(measuresuite_t ms, int batch_size, int num_batches);

/**
 * will set the json result of the last measurement stored in @param ms to
 * @param json. Will write the length needed for that JSON into @param json_len
 */
void ms_get_json(measuresuite_t ms, const char **json, size_t *json_len);

/**
 * will set @param dest to the array of cycle measurements for function @param
 * idx The array will have length of number_of_batches
 *
 */
int ms_get_cycles(measuresuite_t ms, uint64_t **dest, size_t idx);

enum TIMER { PMC, RDTSCP };
/**
 * will return the used timer. Only valid if MS has been initialized
 * (ms_initialize has been called)
 */
enum TIMER ms_get_timer(measuresuite_t ms);

/**
 * Will release all resources allocated with @param ms
 * can be called with NULL, then no operation will be done.
 */
int ms_terminate(measuresuite_t ms);

/**
 * Prints the last error of @param ms to stdout
 */
void ms_printf_error(measuresuite_t ms);

/**
 * Prints the last error of @param ms to stdout
 */
void ms_fprintf_error(measuresuite_t ms, FILE *file);

/**
 * Prints at most @param len chars from the error code to *dest.
 */
void ms_sprintf_error(measuresuite_t ms, char *dest, int len);

/**
 * Returns a pointer to the string corresponding to the last error stored in
 * @param ms
 */
const char *ms_get_error_string(measuresuite_t ms);

#endif
