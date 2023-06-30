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

#include "alloc_helper.h"
#include "error/description.h"
#include "evaluator.h"
#include "loader.h"
#include "randomizer.h"
#include "struct_helpers.h"
#include "struct_measuresuite.h"
#include "timer.h"
#include <measuresuite.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// set static variables
int ms_initialize(measuresuite_t *dest_ms, int arg_width, int num_arg_in,
                  int num_arg_out) {

  measuresuite_t ms = create_default_ms();
  *dest_ms = ms;

  if (ms == NULL                     // alloc ok?
      || set_argwidth(ms, arg_width) // set arg width
      || set_argin(ms, num_arg_in)   // set arg in
      || set_argout(ms, num_arg_out) // set arg out
      || validate_num_args(ms)       // validate arg counts
      || init_random(ms)             // initialize randomness structures
      || init_json(ms)               // initialize measure structs
      || init_timer(ms)              // initialize timer structures
  ) {
    return 1;
  }

  ms->errorno = E_SUCCESS;
  return 0;
}

int ms_set_bounds(measuresuite_t ms, const uint64_t *bounds) {
  return set_bounds(ms, bounds);
}

// NOTE: only useful when used with AL
int ms_set_chunk_size(measuresuite_t ms, size_t chunk_size) {
  return set_chunk_size(ms, chunk_size);
}

void ms_set_checking(measuresuite_t ms, int control) {
  ms->enable_check = control == 0 ? 0 : 1;
}

int ms_load_file(measuresuite_t ms, enum load_type type, const char *filename,
                 const char *symbol, int *id) {
  return load_file(ms, type, filename, symbol, id);
}

int ms_load_data(measuresuite_t ms, enum load_type type, const uint8_t *data,
                 size_t data_len, const char *symbol, int *id) {
  return load_data(ms, type, data, data_len, symbol, id);
}

int ms_unload_all(measuresuite_t ms) {
  for (size_t i = ms->num_functions; i > 0; i--) {
    if (ms_unload_last(ms)) {
      return 1;
    }
  }
  ms->errorno = E_SUCCESS;
  return 0;
}

int ms_unload_last(measuresuite_t ms) {
  if (ms->num_functions == 0) {
    ms->errorno = E_INTERNAL_FUNCTIONS__NOTHING_TO_UNLOAD;
    return 1;
  }

  if (unload(ms, ms->num_functions - 1)) {
    return 1;
  }

  ms->errorno = E_SUCCESS;
  return 0;
}

int ms_measure(measuresuite_t ms, int batch_size, int num_batches) {

  if (set_num_batches(ms, num_batches)  // set number of batches
      || set_batch_size(ms, batch_size) // set batch size
      || run_measurement(ms)            // measure
  ) {
    return 1;
  }

  ms->errorno = E_SUCCESS;
  return 0;
}

void ms_get_json(measuresuite_t ms, const char **json, size_t *json_len) {
  *json = ms->json;
  *json_len = strlen(*json);
}

int ms_get_cycles(measuresuite_t ms, size_t **dest, size_t idx) {
  if (idx >= ms->num_functions) {
    ms->errorno = E_INVALID_INPUT__NUM_IDX_OOB;
    return 1;
  }
  *dest = ms->functions[idx].cycle_results;
  return 0;
}

/**
 * frees memory used for randomness and scratches
 * frees memory and mmaps
 */
int ms_terminate(measuresuite_t ms) {
  if (ms_unload_all(ms) // unload all the loaded functions
      || end_random(ms) // free random data spot
      || end_timer(ms)  // free all timer related data
  ) {
    return 1;
  }

  free(ms->json);
  free(ms->functions);
  free(ms->bounds);
  free(ms);
  return 0;
}

void ms_printf_error(measuresuite_t ms) {
  printf("%s\n", ms_get_error_string(ms));
  if (ms->additional_info) {
    printf("%s\n", ms->additional_info);
  }
}

void ms_fprintf_error(measuresuite_t ms, FILE *file) {
  fprintf(file, "%s\n", ms_get_error_string(ms));
  if (ms->additional_info) {
    fprintf(file, "%s\n", ms->additional_info);
  }
}

void ms_sprintf_error(measuresuite_t ms, char *dest, int len) {
  snprintf(dest, len, "%s Reason: %s\n", get_error_string(ms->errorno),
           ms->additional_info);
}

const char *ms_get_error_string(measuresuite_t ms) {
  return get_error_string(ms->errorno);
}
