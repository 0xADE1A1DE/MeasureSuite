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

#ifndef RANDOMIZER_H
#define RANDOMIZER_H

#include "struct_measuresuite.h"
#include <stdint.h> // uint64_t

int init_random(struct measuresuite *);
int end_random(struct measuresuite *);
int randomize(struct measuresuite *);

int get_random_byte(struct measuresuite *, uint8_t *dest);

#endif
