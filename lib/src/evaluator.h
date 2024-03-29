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

#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "struct_measuresuite.h"

#ifndef NO_AL
/**
 * executes the functions in a R3 fashion.
 * writes the results to json in @param ms
 * @returns 0 on success, 1 on fail
 */
int run_measurement(struct measuresuite *ms);
#endif

/**
 * executes the lib check function only
 * writes the results to cycle_results in @param ms
 * @returns 0 on success, 1 on fail
 */
int run_measurement_lib_only(struct measuresuite *ms);

#endif
