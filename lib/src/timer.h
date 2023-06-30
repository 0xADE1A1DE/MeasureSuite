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

#ifndef TIMER_H
#define TIMER_H

#include "struct_measuresuite.h"
#include <stdint.h>

int init_timer(struct measuresuite *ms);
int end_timer(struct measuresuite *ms);
void start_timer(struct measuresuite *ms, uint64_t *start);
uint64_t stop_timer(struct measuresuite *ms, uint64_t start);

uint64_t current_timestamp();

#endif
