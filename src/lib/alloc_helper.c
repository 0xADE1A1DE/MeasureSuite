
#include "alloc_helper.h"
#include "ms_error.h"
#include <errno.h>    // errno
#include <stdlib.h>   // realloc
#include <string.h>   // strerror
#include <sys/mman.h> // mmap...

int realloc_or_fail(struct measuresuite *ms, void **dest, size_t new_len) {
  *dest = realloc(*dest, new_len);
  if (*dest == NULL) {
    ms->errorno = E_INTERNAL_MEASURE__AI__ALLOC;
    ms->additional_info = strerror(errno);
    return 1;
  }
  return 0;
}

int alloc_rwx_or_fail(struct measuresuite *ms, void **dest, size_t new_len) {
  *dest = mmap(NULL, new_len, PROT_READ | PROT_WRITE | PROT_EXEC,
               MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
  if (*dest == NULL) {
    ms->errorno = E_INTERNAL_MEASURE__AI__ALLOC;
    ms->additional_info = strerror(errno);
    return 1;
  }
  return 0;
}

int realloc_rwx_or_fail(struct measuresuite *ms, void **dest, size_t old_len,
                        size_t new_len) {
  // not using mremap here, because it  may clash with errno (and USE_GNU)
  if (munmap(*dest, old_len)) {
    ms->errorno = E_INTERNAL_MEASURE__AI__ALLOC;
    ms->additional_info = strerror(errno);
    return 1;
  }
  return alloc_rwx_or_fail(ms, *dest, new_len);
}

int unmap(struct measuresuite *ms, void **dest, size_t old_len) {
  if (munmap(*dest, old_len)) {
    ms->errorno = E_INTERNAL_MEASURE__AI__ALLOC;
    ms->additional_info = strerror(errno);
    return 1;
  }
  return 0;
}

int init_arithmetic_results(measuresuite_t ms, struct function_tuple *t) {
  /**                                                             */
  /** +---------------------------------------------------------+ */
  /** |                  Arithmetic Results                     | */
  /** +---------------------------------------------------------+ */
  /**   ^-- 2 * ArithmeticResult                                  */

  /** Arithmetic Results: */
  /** +---------------------------------------------------------+ */
  /** | Arithmetic Res (for first) | Arithmetic Res (for seond) | */
  /** +---------------------------------------------------------+ */
  /**   ^--- #argOut * sizeof(Out)                                */

  /** Arithmetic Res */
  /** +---------------------------------------------------------+ */
  /** |         out1 , out2, ... , out[#numArgOut]              | */
  /** +---------------------------------------------------------+ */
  /**     ^---   out1 * arg_width */

  /** Out1  each sizeof(u64)*/
  /** +---------------------------------------------------------+ */
  /** |         out1[0] , out1[1], ... , out1[#arg_width]       | */
  /** +---------------------------------------------------------+ */

  const int amount_results = 2; // one from asm, one from the check function

  t->arithmetic_results_size_u64 =
      ms->arg_width * amount_results * ms->num_arg_out;
  size_t size_arith_res_b = t->arithmetic_results_size_u64 * sizeof(uint64_t);

  t->arithmetic_results = malloc(size_arith_res_b);
  if (t->arithmetic_results == NULL) {
    ms->errorno = E_INTERNAL_MEASURE__AI__ALLOC;
    ms->additional_info = strerror(errno);
    return 1;
  }
  return 0;
}
