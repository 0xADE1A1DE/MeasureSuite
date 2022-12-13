#ifndef ELF_PARSER_H
#define ELF_PARSER_H
#include "../struct_measuresuite.h"

int elf_load_symbol(measuresuite_t ms, void *dest, size_t dest_size,
                    const char *filename, const char *symbol);
int elf_load_symbol_mem(measuresuite_t ms, void *dest, size_t dest_size,
                        const uint8_t *src, const char *symbol);
#endif
