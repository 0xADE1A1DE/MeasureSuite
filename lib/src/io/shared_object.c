/**
 * Copyright 2023 University of Adelaide
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
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
