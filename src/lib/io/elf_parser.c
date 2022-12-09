#include "elf_parser.h"
#include "ms_error.h"

#include "elf_file.h"

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
  int fd = open(filename, O_RDONLY | O_SYNC);
  if (fd < 0) {
    ms->errorno = E_LOAD__ELF_FILE_IO;
    ms->additional_info = strerror(errno);
    return 1;
  }

  Elf64_Ehdr eh64; /* elf-header is fixed size */
  /* ELF header : at start of file */
  if (read_elf_header(fd, &eh64)) {
    ms->errorno = E_LOAD__ELF_FILE_INVALID_ELF;
    return 1;
  }

  /* Section header table :  */
  Elf64_Shdr *sh_tbl = malloc(eh64.e_shentsize * eh64.e_shnum);
  if (!sh_tbl || read_section_header_table64(fd, eh64, sh_tbl)) {
    ms->errorno = E_LOAD__ELF_FILE_MALLOC;
    return 1;
  }

  unsigned long offset = 0; // get offset of .text first
  find_section_offset(fd, eh64, sh_tbl, ".text", &offset);

  Elf64_Sym s = {0};
  find_symbol_offset(fd, eh64, sh_tbl, symbol, &s);
  free(sh_tbl);

  // then add the offset of the symbol within the section
  offset += s.st_value;

  // check if destination buffer is big enough
  Elf64_Xword size = s.st_size;
  assert(s.st_size > dest_size);

  // read code into *dest
  lseek(fd, (long)offset, SEEK_SET);
  read(fd, dest, size);

  return 0;
}
