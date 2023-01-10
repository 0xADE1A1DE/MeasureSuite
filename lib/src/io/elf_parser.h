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
#ifndef ELF_PARSER_H
#define ELF_PARSER_H
#include "../struct_measuresuite.h"

int elf_load_symbol(measuresuite_t ms, void *dest, size_t dest_size,
                    const char *filename, const char *symbol);
int elf_load_symbol_mem(measuresuite_t ms, void *dest, size_t dest_size,
                        const uint8_t *src, const char *symbol);
#endif
