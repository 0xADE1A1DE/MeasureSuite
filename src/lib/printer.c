#include "printer.h"
#include <stdio.h>
void printbin_single_number(uint64_t n) {

  const int bitwitdh_uint64 = 64;

  int width = bitwitdh_uint64; // bits
  uint64_t mask = (uint64_t)1 << (bitwitdh_uint64 - 1);
  while (width--) {
    if (n & mask)
      printf("1");
    else
      printf("0");

    mask >>= 1;
  }
  printf("\n");
}
static const int color_grn = 32;

void printbin(uint64_t const *a, uint64_t const *b, int len, int l) {
  int color = color_grn - (*a != *b); // col 32 when its equal, grn
  printf("\n\x1b[%dm @ %d/%d: \n"
         "a:0b",
         color, len, l);
  printbin_single_number(*a);
  printf("b:0b");
  printbin_single_number(*b);
  printf("\x1b[0m");
}

void printhex(uint64_t const *a, uint64_t const *b, int len, int l) {
  int color = color_grn - (*a != *b); // col 32 when its equal, grn
  printf("\n\x1b[%dm @ %d/%d: \n"
         "a:0x%016lx\n"
         "b:0x%016lx\x1b[0m\n",
         color, len, l, *a, *b);
}
