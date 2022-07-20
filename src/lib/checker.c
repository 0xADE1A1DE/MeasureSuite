#include "checker.h"
#include "printer.h"
#include <stdio.h>

/*
 * checks len * sizeof(uint64) bytes
 * returns 0 if *(b+n) == *(a+n) for all n in [0, len]
 */
enum CORRECTNESS { OK = 0, WRONG = 1 };
int check(int len, const uint64_t *a, const uint64_t *b) {
  int l = len;
  int res = OK;
  a += len;
  b += len;
  // check first.
  while (len--) {
    res |= (*(--a) != *(--b));
  }

  // if where is a mistake, print all
  if (res == WRONG) {
    while (++len < l) {
#if PRINT_BIN
      printbin(a, b, len, l);
#else
      printhex(a, b, len, l);
#endif
      a++;
      b++;
    }
  }
  // and return the result anyway
  return res;
}
