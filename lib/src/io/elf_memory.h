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
#ifndef ELF_MEMORY_H
#define ELF_MEMORY_H
#include <elf.h>
#include <stdint.h>

int read_section_header_table64_mem(const uint8_t *src, Elf64_Ehdr hdr,
                                    Elf64_Shdr sh_table[]);
void find_symbol_in_table_mem(Elf64_Sym *dest, const uint8_t *src,
                              Elf64_Shdr sh_table[], Elf64_Half sh_table_len,
                              const char *symbol);
int read_elf_header_mem(const uint8_t *src, Elf64_Ehdr *elf_header);

// this will  look for 'needle' as a section name in the sh_table and set @param
// *dest to the index in the table
void find_section_offset_mem(const uint8_t *src, Elf64_Ehdr hdr,
                             Elf64_Shdr sh_table[], const char *needle,
                             unsigned long *dest);
#endif
