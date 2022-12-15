#include "elf_parser.h"
#include "../error/error.h"

#include "elf_file.h"
#include "elf_memory.h"

#include <assert.h> // assert
#include <elf.h>    // Elf64_Ehdr
#include <errno.h>  // errno
#include <fcntl.h>  // open
#include <stdint.h> // int32_t's
#include <stdlib.h> // malloc
#include <string.h> // strncmp
#include <unistd.h> // lseek/read/SEEK_SET

int elf_load_symbol(measuresuite_t ms, void *dest, size_t dest_size,
                    const char *filename, const char *symbol) {

  // open file
  int file = open(filename, O_RDONLY | O_SYNC);
  if (file < 0) {
    ms->errorno = E_LOAD__ELF_FILE_IO;
    ms->additional_info = strerror(errno);
    return 1;
  }

  Elf64_Ehdr eh64; /* elf-header is fixed size */
  /* ELF header : at start of file */
  if (read_elf_header(file, &eh64)) {
    ms->errorno = E_LOAD__ELF_FILE_INVALID_ELF;
    return 1;
  }

  /* Section header table :  */
  Elf64_Shdr *sh_tbl = malloc(eh64.e_shentsize * eh64.e_shnum);
  if (!sh_tbl || read_section_header_table64(file, eh64, sh_tbl)) {
    ms->errorno = E_LOAD__ELF_FILE_MALLOC;
    return 1;
  }

  unsigned long offset = 0; // get offset of .text first
  find_section_offset(file, eh64, sh_tbl, ".text", &offset);

  Elf64_Sym sym = {0};
  find_symbol_in_table(file, eh64, sh_tbl, symbol, &sym);
  free(sh_tbl);

  // then add the offset of the symbol within the section
  offset += sym.st_value;

  // check if destination buffer is big enough
  Elf64_Xword size = sym.st_size;
  assert(sym.st_size <= dest_size);

  // read code into *dest
  lseek(file, (long)offset, SEEK_SET);
  read(file, dest, size);

  return 0;
}

int elf_load_symbol_mem(measuresuite_t ms, void *dest, size_t dest_size,
                        const uint8_t *src, const char *symbol) {
  // read elf header
  // read section header table
  // find .text - section
  // find symbol
  // 	-- read all sections from table
  // 	-- skip sections which are not SHT_SYMTAB / SHT_DYNSYM
  // 	-- read SHT_SYMTAB / SHT_DYNSYM

  Elf64_Ehdr eh64; /* elf-header is fixed size */
  /* ELF header : at start of file */
  if (read_elf_header_mem(src, &eh64)) {
    ms->errorno = E_LOAD__ELF_MEM_INVALID_ELF;
    return 1;
  }

  /* Section header table :  */
  Elf64_Shdr *sh_tbl = malloc(eh64.e_shentsize * eh64.e_shnum);
  if (!sh_tbl || read_section_header_table64_mem(src, eh64, sh_tbl)) {
    ms->errorno = E_LOAD__ELF_FILE_MALLOC;
    return 1;
  }

  unsigned long offset = 0; // get offset of .text first
  find_section_offset_mem(src, eh64, sh_tbl, ".text", &offset);

  Elf64_Sym sym = {0};
  find_symbol_in_table_mem(&sym, src, sh_tbl, eh64.e_shnum, symbol);
  free(sh_tbl);

  // then add the offset of the symbol within the section
  offset += sym.st_value;

  // check if destination buffer is big enough
  Elf64_Xword size = sym.st_size;
  assert(sym.st_size <= dest_size);

  // read code into *dest
  memcpy(dest, src + offset, size);

  return 0;
};
