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
