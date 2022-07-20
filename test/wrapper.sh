#!/usr/bin/env bash

# This file will execute $1.
# It writes the success to the terminal
# It returns 1 on failure, 0 else.

#file to test
filename=$(basename "${1}")

#directory of where libmeasuresuite.so resides
libpath=..

cd test && LD_LIBRARY_PATH=${libpath} "./${filename}" >/dev/null 2>&1
case ${?} in
0)
  printf "\033[32m  OK  \033[0m%s\n" "${filename}"
  exit 0
  ;;
77)
  printf "\033[33m SKIP \033[0m%s\n" "${filename}"
  exit 0
  ;;
1 | *)
  printf "\033[31m FAIL \033[0m%s\n" "${filename}"
  exit 1
  ;;
esac
