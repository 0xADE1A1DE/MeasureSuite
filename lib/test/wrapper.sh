#!/usr/bin/env bash
## Copyright 2022 University of Adelaide

## Licensed under the Apache License, Version 2.0 (the "License");
## you may not use this file except in compliance with the License.
## You may obtain a copy of the License at

##    http://www.apache.org/licenses/LICENSE-2.0

## Unless required by applicable law or agreed to in writing, software
## distributed under the License is distributed on an "AS IS" BASIS,
## WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
## See the License for the specific language governing permissions and
## limitations under the License.

#

# This file will execute $1.
# It writes the success to the terminal
# It returns 1 on failure, 0 else.

#file to test
filename="${1#test/}"
out_filename="./${filename}.out"
err_filename="./${filename}.err"

#directory of where libmeasuresuite.so resides
libpath=..
trap fail SIGABRT

fail() {
  printf "\r\033[31m FAIL \033[0m\nStderr:\n"
  cat "${err_filename}"
  echo "Stdout:"
  cat "${out_filename}"
  exit 1
}

pushd "test" >/dev/null || exit 2

printf "\033[33m RUN  \033[0m%s" "${filename}"
LD_LIBRARY_PATH=${libpath} "./${filename}" 2>"${err_filename}" 1>"${out_filename}"

case ${?} in
0)
  printf "\r\033[32m  OK  \033[0m\n"
  exit 0
  ;;
77)
  printf "\r\033[33m SKIP \033[0m\n"
  exit 0
  ;;
1 | *)
  fail
  ;;
esac
