#include "elf_file.h"
#include <elf.h>
#include <stdio.h>     // printf
#include <stdlib.h>    // malloc
#include <string.h>    // memcpy
#include <sys/types.h> // off_t

// CREDIT https://github.com/TheCodeArtist/elf-parser/blob/master/elf-parser.c

/**
 * reads all section headers defined in @param eh from @param fd to sh_table
 */
int read_section_header_table64_mem(const uint8_t *src, Elf64_Ehdr hdr,
                                    Elf64_Shdr *sh_table) {

  memcpy(sh_table, src + hdr.e_shoff, hdr.e_shentsize * hdr.e_shnum);

  return 0;
}

// will malloc *dest; must be freed outside
static int read_section_mem(const uint8_t *src, Elf64_Shdr *sect_hdr,
                            void **dest) {

  *dest = malloc(sect_hdr->sh_size);
  if (!dest) {
    printf("%s:Failed to allocate %ldbytes\n", __func__, sect_hdr->sh_size);
    return 1;
  }

  memcpy(*dest, src + (off_t)sect_hdr->sh_offset, sect_hdr->sh_size);
  return 0;
}

void find_section_offset_mem(const uint8_t *src, Elf64_Ehdr hdr,
                             Elf64_Shdr sh_table[], const char *needle,
                             unsigned long *dest) {

  size_t len_needle = strlen(needle);

  /* Read section-header string-table */
  void *sh_str = NULL;
  read_section_mem(src, &sh_table[hdr.e_shstrndx], &sh_str);

  for (int i = 0; i < hdr.e_shnum; i++) {
    char *name = sh_str + sh_table[i].sh_name;

    if (strncmp(name, needle, len_needle) == 0) {
      *dest = i;
      break;
    }
  }
  free(sh_str);
}

void find_symbol_in_table_mem(Elf64_Sym *dest, const uint8_t *src,
                              Elf64_Shdr sh_table[], Elf64_Half sh_table_len,
                              const char *symbol) {

  size_t symbol_len = symbol != NULL ? strlen(symbol) : 0;
  Elf64_Shdr *last = NULL;
  Elf64_Shdr *entry = NULL;

  for (last = sh_table + sh_table_len * sizeof(Elf64_Shdr), // find end
       entry = sh_table;                                    // set first end
       entry != last;                                       // check not last
       entry++                                              // next
  ) {

    if ((entry->sh_type != SHT_SYMTAB) && (entry->sh_type != SHT_DYNSYM)) {
      continue;
    }

    Elf64_Sym *sym_tbl = {0};

    read_section_mem(src, entry, (void *)&sym_tbl);

    /* Read linked string-table
     * Section containing the string table having names of
     * symbols of this section
     */
    Elf64_Word str_tbl_ndx = entry->sh_link;
    char *str_tbl = NULL;
    read_section_mem(src, &sh_table[str_tbl_ndx], (void *)&str_tbl);

    unsigned long symbol_count = entry->sh_size / sizeof(Elf64_Sym);

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

int read_elf_header_mem(const uint8_t *src, Elf64_Ehdr *elf_header) {
  size_t size = sizeof(Elf64_Ehdr);
  char magic[] = {"\177ELF"};
  if (elf_header == NULL                                     // sanity
      || memcpy(elf_header, src, size) == NULL               // read header
      || strncmp((char *)elf_header->e_ident, magic, 4) != 0 // check magic
      || elf_header->e_ident[EI_CLASS] != ELFCLASS64         // is elf64
  ) {
    return 1;
  }
  return 0;
}
