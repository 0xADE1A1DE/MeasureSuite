#include "helper.h"
#include <stdio.h>
#include <stdlib.h>

void error_handling_helper(measuresuite_t ms) {
  error_handling_helper_template_str(ms, "Failed. Reason: %s\n");
}

void error_handling_helper_template_str(measuresuite_t ms,
                                        const char *tpl_str) {
  const int len = 1000;
  char *s = calloc(1, len * sizeof(char));
  ms_str_full_error(ms, s, len);
  fprintf(stderr, tpl_str, s);
  free(s);
}

void exit_skip() { exit(SKIP); }
/**
 * @returns 1 if the bit is set
 */
int check_ise_bit(int bit_no) {
  // EAX value for getting the ISE's from cpu id is 07h
  int r = 0;
  int checkBit = 1 << bit_no;

  asm volatile("mov $7, %%eax \n\t"
               "mov $0, %%ecx \n\t"
               "cpuid\n\t"
               "and %%ebx, %[bit]\n\t"
               "mov %%ebx, %[ret]\n\t"
               : [ret] "=&m"(r)
               : [bit] "m"(checkBit)
               : "rax", "rbx", "rcx", "rdx");
  return r;
};
