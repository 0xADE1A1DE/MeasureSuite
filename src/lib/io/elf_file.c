#include "elf_file.h"
#include <stdio.h>  // EOF
#include <stdlib.h> // malloc
#include <string.h> // memcpy
#include <unistd.h> // seek

// CREDIT https://github.com/TheCodeArtist/elf-parser/blob/master/elf-parser.c

/**
 * reads all section headers defined in @param eh from @param fd to sh_table
 */
int read_section_header_table64(int32_t fd, Elf64_Ehdr eh,
                                Elf64_Shdr *sh_table) {

  // seek to header
  if (lseek(fd, (off_t)eh.e_shoff, SEEK_SET) != (off_t)eh.e_shoff) {
    return 1;
  };

  // read all headers at once
  const ssize_t combined_size = eh.e_shnum * eh.e_shentsize;
  if (read(fd, sh_table, combined_size) != combined_size) {
    return 1;
  }

  return 0;
}

// will malloc *dest; must be freed outside
static int read_section(int32_t fd, Elf64_Shdr sh, void **dest) {

  *dest = malloc(sh.sh_size);
  if (!dest) {
    printf("%s:Failed to allocate %ldbytes\n", __func__, sh.sh_size);
    return 1;
  }

  if (lseek(fd, (off_t)sh.sh_offset, SEEK_SET) != (off_t)sh.sh_offset) {
    return 1;
  };
  ssize_t r = read(fd, *dest, sh.sh_size);
  if (r == -1 || r == 0 || r == EOF || (size_t)r != sh.sh_size) {
    return 1;
  }
  return 0;
}

void find_section_offset(int32_t fd, Elf64_Ehdr eh, Elf64_Shdr sh_table[],
                         const char *needle, unsigned long *dest) {

  size_t len_needle = strlen(needle);

  /* Read section-header string-table */
  void *sh_str = NULL;
  read_section(fd, sh_table[eh.e_shstrndx], &sh_str);

  for (int i = 0; i < eh.e_shnum; i++) {
    char *name = sh_str + sh_table[i].sh_name;

    if (strncmp(name, needle, len_needle) == 0) {
      *dest = sh_table[i].sh_offset;
      break;
    }
  }
  free(sh_str);
}

void find_symbol_in_table(int32_t fd, Elf64_Ehdr eh, Elf64_Shdr sh_table[],
                          const char *symbol, Elf64_Sym *dest) {

  size_t symbol_len = symbol != NULL ? strlen(symbol) : 0;

  for (int i = 0; i < eh.e_shnum; i++) {
    if ((sh_table[i].sh_type != SHT_SYMTAB) &&
        (sh_table[i].sh_type != SHT_DYNSYM)) {
      continue;
    }

    Elf64_Sym *sym_tbl = {0};

    read_section(fd, sh_table[i], (void *)&sym_tbl);

    /* Read linked string-table
     * Section containing the string table having names of
     * symbols of this section
     */
    Elf64_Word str_tbl_ndx = sh_table[i].sh_link;
    char *str_tbl = NULL;
    read_section(fd, sh_table[str_tbl_ndx], (void *)&str_tbl);

    unsigned long symbol_count = sh_table[i].sh_size / sizeof(Elf64_Sym);

    for (unsigned long j = 0; j < symbol_count; j++) {

      const char *name = str_tbl + sym_tbl[j].st_name;
      // if we don't have a symbol(i.e. symbol len == 0),
      // or the current symbol is the required one
      if (symbol_len == 0 || strncmp(name, symbol, symbol_len) == 0) {
        memcpy(dest, &sym_tbl[j], sizeof(Elf64_Sym));
        break;
      }
    }
    free(str_tbl);
    free(sym_tbl);
  }
}

int read_elf_header(int32_t fd, Elf64_Ehdr *elf_header) {
  size_t size = sizeof(Elf64_Ehdr);
  char magic[] = {"\177ELF"};
  if (elf_header == NULL                                     // sanity
      || lseek(fd, (off_t)0, SEEK_SET) != (off_t)0           // seek to start
      || (size_t)read(fd, elf_header, size) != size          // read header
      || strncmp((char *)elf_header->e_ident, magic, 4) != 0 // check magic
      || elf_header->e_ident[EI_CLASS] != ELFCLASS64         // is elf64
  ) {
    return 1;
  }
  return 0;
}
