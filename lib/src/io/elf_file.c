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
#include "elf_file.h"
#include <stdio.h>     // EOF, fprintf
#include <stdlib.h>    // malloc
#include <string.h>    // memcpy
#include <sys/types.h> // off_t
#include <unistd.h>    // seek

// CREDIT https://github.com/TheCodeArtist/elf-parser/blob/master/elf-parser.c

/**
 * reads all section headers defined in @param hdr from @param file to sh_table
 */
int read_section_header_table64(int32_t file, Elf64_Ehdr hdr,
                                Elf64_Shdr *sh_table) {

  // seek to header
  if (lseek(file, (off_t)hdr.e_shoff, SEEK_SET) != (off_t)hdr.e_shoff) {
    return 1;
  };

  // read all headers at once
  const ssize_t combined_size = (long)hdr.e_shnum * hdr.e_shentsize;
  if (read(file, sh_table, combined_size) != combined_size) {
    return 1;
  }

  return 0;
}

// will malloc *dest; must be freed outside
static int read_section(int32_t file, Elf64_Shdr sect_hdr, void **dest) {

  *dest = malloc(sect_hdr.sh_size);
  if (!dest) {
    fprintf(stderr, "%s:Failed to allocate %ldbytes\n", __func__,
            sect_hdr.sh_size);
    return 1;
  }

  if (lseek(file, (off_t)sect_hdr.sh_offset, SEEK_SET) !=
      (off_t)sect_hdr.sh_offset) {
    return 1;
  };
  ssize_t bytes_read = read(file, *dest, sect_hdr.sh_size);
  if (bytes_read == -1 || bytes_read == 0 || bytes_read == EOF ||
      (size_t)bytes_read != sect_hdr.sh_size) {
    return 1;
  }
  return 0;
}

void find_section_offset(int32_t file, Elf64_Ehdr hdr, Elf64_Shdr sh_table[],
                         const char *needle, unsigned long *dest) {

  size_t len_needle = strlen(needle);

  /* Read section-header string-table */
  char *sh_str = NULL;
  read_section(file, sh_table[hdr.e_shstrndx], (void **)&sh_str);

  for (int i = 0; i < hdr.e_shnum; i++) {

    // sh_name is the index in the string_table
    Elf64_Word index = sh_table[i].sh_name;

    // get the address of the string to compare
    const char *name = &(sh_str[index]);

    if (strncmp(name, needle, len_needle) == 0) {
      *dest = i;
      break;
    }
  }
  free(sh_str);
}

void find_symbol_in_table(int32_t file, Elf64_Ehdr hdr, Elf64_Shdr sh_table[],
                          const char *symbol, Elf64_Sym *dest) {

  size_t symbol_len = symbol != NULL ? strlen(symbol) : 0;

  for (int i = 0; i < hdr.e_shnum; i++) {
    if ((sh_table[i].sh_type != SHT_SYMTAB) &&
        (sh_table[i].sh_type != SHT_DYNSYM)) {
      continue;
    }

    Elf64_Sym *sym_tbl = {0};

    read_section(file, sh_table[i], (void *)&sym_tbl);

    /* Read linked string-table
     * Section containing the string table having names of
     * symbols of this section
     */
    Elf64_Word str_tbl_ndx = sh_table[i].sh_link;
    char *string_tbl = NULL;
    read_section(file, sh_table[str_tbl_ndx], (void *)&string_tbl);

    unsigned long symbol_count = sh_table[i].sh_size / sizeof(Elf64_Sym);

    for (unsigned long j = 0; j < symbol_count; j++) {

      Elf64_Sym cur_sym = sym_tbl[j];
      // st_name is the index in the string_table
      Elf64_Word index = cur_sym.st_name;

      // get the address of the string to compare
      const char *name = &(string_tbl[index]);
      // if we don't have a symbol(i.e. symbol len == 0),
      // or the current symbol is the required one
      if (symbol_len == 0 || strncmp(name, symbol, symbol_len) == 0) {
        memcpy(dest, &sym_tbl[j], sizeof(Elf64_Sym));
        break;
      }
    }
    free(string_tbl);
    free(sym_tbl);
  }
}

int read_elf_header(int32_t file, Elf64_Ehdr *elf_header) {
  size_t size = sizeof(Elf64_Ehdr);
  char magic[] = {"\177ELF"};
  if (elf_header == NULL                                     // sanity
      || lseek(file, (off_t)0, SEEK_SET) != (off_t)0         // seek to start
      || (size_t)read(file, elf_header, size) != size        // read header
      || strncmp((char *)elf_header->e_ident, magic, 4) != 0 // check magic
      || elf_header->e_ident[EI_CLASS] != ELFCLASS64         // is elf64
  ) {
    return 1;
  }
  return 0;
}
