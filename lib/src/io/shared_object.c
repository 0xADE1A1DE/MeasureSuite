#include "shared_object.h"
#include "../error/error.h"
#include <dlfcn.h>  // dlopen
#include <errno.h>  // errno
#include <string.h> // strerror
#include <unistd.h> // access|F_OK...

int so_load_file(struct measuresuite *ms, struct function_tuple *fct,
                 const char *filename) {

  if (access(filename, F_OK | X_OK | R_OK) != 0) {
    ms->errorno = E_LOAD__SO_FILE;
    ms->additional_info = strerror(errno);
    return 1;
  }

  // clear error
  dlerror();

  // open
  fct->lib_handle = dlopen(filename, RTLD_NOW | RTLD_LOCAL);

  // check
  if (fct->lib_handle == NULL) {
    ms->errorno = E_INTERNAL_MEASURE__AI__DLOPEN;
    ms->additional_info = dlerror();
    return 1;
  }

  return 0;
}

int so_load_symbol(struct measuresuite *ms, struct function_tuple *fct,
                   const char *symbol) {

  // sanity check  the handle
  if (fct->lib_handle == NULL) {
    return 1;
  }

  // clear error
  dlerror();

  // load
  fct->code = dlsym(fct->lib_handle, symbol);

  /// check
  if (fct->code == NULL) {
    ms->errorno = E_INTERNAL_MEASURE__AI__DLSYM;
    ms->additional_info = dlerror();
    return 1;
  }

  return 0;
}

int so_unload_file(struct measuresuite *ms, struct function_tuple *fct) {
  // clear error
  dlerror();

  // close and check
  if (dlclose(fct->lib_handle) != 0) {
    ms->errorno = E_INTERNAL_MEASURE__AI__DLCLOSE;
    ms->additional_info = dlerror();
    return 1;
  }

  return 0;
}
