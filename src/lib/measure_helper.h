#ifndef MEASURE_HELPER_H
#define MEASURE_HELPER_H

#include "struct_measuresuite.h"

/**
 * Will dlopen @param lib_check_functions_filename
 * It will save the dl-handle in @param ms
 * @returns 0 on success, 1 on fail
 */
int load_check_file(struct measuresuite *,
                    const char *lib_check_functions_filename);

/**
 * Will dlopen @param ms'es dl-handle and load symbol @param
 * check_function_symbolname It will save the the function pointer
 * in @param ms
 * @returns 0 on success, 1 on fail
 */
int load_check_function(struct measuresuite *,
                        const char *check_function_symbolname);

/**
 * Will dlclose the dlopened lib_check_functions_filename
 * @returns 0 on success, 1 on fail
 */
int unload_check_function(struct measuresuite *);

/**
 * Calculates and allocates / callocates scratch space needed for runnning
 * measurements
 * @returns 0 on success, 1 on fail
 */
int init_measure_scratch(struct measuresuite *);
/**
 * Frees the allocated scratch memory.
 * @returns 0 on success, 1 on fail
 */
int end_measure_scratch(struct measuresuite *);
#endif
