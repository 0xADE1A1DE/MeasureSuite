
#include "../struct_measuresuite.h"

int so_load_file(struct measuresuite *ms, struct function_tuple *t,
                 const char *filename);
int so_load_symbol(struct measuresuite *ms, struct function_tuple *t,
                   const char *symbol);
int so_unload_file(struct measuresuite *ms, struct function_tuple *t);
