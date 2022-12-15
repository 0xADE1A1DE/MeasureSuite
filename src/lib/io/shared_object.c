#include "shared_object.h"
#include "../error/error.h"
#include <dlfcn.h>  // dlopen
#include <errno.h>  // errno
#include <string.h> // strerror
#include <unistd.h> // access|F_OK...

int so_load_file(struct measuresuite *ms, struct function_tuple *t,
                 const char *filename) {

  if (access(filename, F_OK | X_OK | R_OK) != 0) {
    ms->errorno = E_LOAD__SO_FILE;
    ms->additional_info = strerror(errno);
    return 1;
  }

  dlerror(); // clear error

  if ((t->lib_handle = dlopen(filename, RTLD_NOW | RTLD_LOCAL)) == NULL) {
    ms->errorno = E_INTERNAL_MEASURE__AI__DLOPEN;
    ms->additional_info = dlerror();
    return 1;
  }

  return 0;
}

int so_load_symbol(struct measuresuite *ms, struct function_tuple *t,
                   const char *symbol) {

  // sanity check  the handle
  if (t->lib_handle == NULL) {
    return 1;
  }

  dlerror(); // clear error
  if ((t->code = dlsym(t->lib_handle, symbol)) == NULL) {
    ms->errorno = E_INTERNAL_MEASURE__AI__DLSYM;
    ms->additional_info = dlerror();
    return 1;
  }

  return 0;
}

int so_unload_file(struct measuresuite *ms, struct function_tuple *t) {

  dlerror(); // clear error
  if (dlclose(t->lib_handle) != 0) {
    ms->errorno = E_INTERNAL_MEASURE__AI__DLCLOSE;
    ms->additional_info = dlerror();
    return 1;
  }

  return 0;
}
