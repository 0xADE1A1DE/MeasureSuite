#ifndef ELF_FILE_H
#define ELF_FILE_H
#include <elf.h>
#include <stdint.h>

int read_section_header_table64(int32_t file, Elf64_Ehdr hdr,
                                Elf64_Shdr sh_table[]);
void find_symbol_in_table(int32_t file, Elf64_Ehdr hdr, Elf64_Shdr sh_table[],
                          const char *symbol, Elf64_Sym *dest);
int read_elf_header(int32_t file, Elf64_Ehdr *elf_header);
void find_section_offset(int32_t file, Elf64_Ehdr hdr, Elf64_Shdr sh_table[],
                         const char *needle, unsigned long *dest);
#endif
