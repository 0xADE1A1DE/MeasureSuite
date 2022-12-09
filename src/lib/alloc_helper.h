
#include "struct_measuresuite.h"
#include <inttypes.h>

int realloc_or_fail(struct measuresuite *ms, void **dest, size_t new_len);
int alloc_rwx_or_fail(struct measuresuite *ms, void **dest, size_t new_len);
int realloc_rwx_or_fail(struct measuresuite *ms, void **dest, size_t old_len,
                        size_t new_len);
int unmap(struct measuresuite *ms, void **dest, size_t old_len);
int init_arithmetic_results(measuresuite_t ms, struct function_tuple *t);
