# MeasureSuite
![Unit Tests](https://github.com/0xADE1A1DE/MeasureSuite/actions/workflows/check.yml/badge.svg)
![Code Style](https://github.com/0xADE1A1DE/MeasureSuite/actions/workflows/clang-format-check.yml/badge.svg)
<!-- ![Version](https://img.shields.io/github/v/release/0xADE1A1DE/MeasureSuite?logo=github&style=flat) -->

This library measures the execution time of code.

## Features
- You can load `.o`, `.so`, `.bin`, `.asm` files and out comes a `JSON` with cycle counts. 
- Runs all loaded programs in a random order with random inputs.
- Can check if the results matches the results of a the other loaded methods.
- C-interface
- TypeScript-interface
- Supports functions of the C-like type `void A(uint64_t *out, const uint64_t *in)` (up to six parameters)
- It assembles assembly code using [AssemblyLine](https://github.com/0xADE1A1DE/AssemblyLine)
- Reports chunk size counting. (i.e. How many instructions of a function beaks a chunk boundary, if in use with AssemblyLine)
- Returns a JSON string with the measurement metrics.
- Uses Performance Counters (PMC), falls back to `RDTSC` if PMC are unavailable.
- cli-tools `ms`, takes files in and outputs `JSON` measurements

## Examples

###TODO: better examples

### Increment a number (C-land)


- suppose we have an `add_two_numbers`-function (as we do in [the test library](./lib/test/test_data/all.c)) like this:
```c
void add_two_numbers(uint64_t *out0, const uint64_t *in0, const uint64_t *in1) {
  *out0 = *in0 + *in1;
}
```

- and we want to measure equivalent asm-code with measurewuite
```c

#include <measuresuite.h>
#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

int main (){

  // properties of the function
  const int arg_width = 1;   // each param points to only one element
  const int arg_num_in = 2;
  const int arg_num_out = 1;

  // asm to measure
  char add_two_asm[] = {"mov rax, [rsi]\n"
                        "add rax, [rdx]\n"
                        "mov [rdi], rax\n"
                        "ret\n"};

  // our measuresuite handle
  measuresuite_t ms = NULL;

  // initializing the measuresuite
  ms_initialize(&ms, arg_width, arg_num_in, arg_num_out);

  // id =- means we want to load to the next free spot.
  // it will be set to the spot taken by the loaded function.
  int id = -1;
  ms_load_data(ms,                     // handle
               ASM,                    // type of input data is assembly
               (uint8_t *)add_two_asm, // pointer to input data
               strlen(add_two_asm),    // length of input data
               NULL,                   // symbol (ignored for BIN/ASM, optional for ELF, required for SHARED_OBJECT))
               &id);                   // ID (in/out)

  // first spot (subsequent loads will load to 1, 2, ...)
  assert(id == 0);

  const int batch_size = 100;
  const int number_of_batches = 10;

  // run the measurement
  ms_measure(ms, batch_size, number_of_batches);

  // prepare got JSON collection
  const char *json = NULL;
  size_t len = 0;
  ms_get_json(ms, &json, &len);

  assert(json != NULL);
  assert(len != 0);

  //prints the result json
  printf("%s\n",json);

  ms_terminate(ms);

  return 0;
}
```

### Plus 1 (TS-land)

- Find the `functionA` and `functionB` in the [functions.ts](./ts/test/test_data/functions.ts)
- Both functions increment a number.
- We set up the boilerplate to use MeasureSuite from TypeScript-land in the [Plus 1 Test](./ts/test/plus1.test.ts)
- And analyze the measurement Result

## Dependencies
- `make`, C-compiler
- [AssemblyLine](https://github.com/0xADE1A1DE/AssemblyLine) (Can be skipped if builing with `NO_AL=1`, then MeasureSuite will not only be able to handle `asm` inputs.)
- Note: If you want to use the ts-wrapper without AssemblyLine, remove the `defines:["USE_ASSEMBLYLINE"]` and `libraries:["-lassemblyline"]` in `ts/binding.gyp`, and then `npm install` it.
- For C-tests coverage `lcov` 
- For TS: [Node.js](https://nodejs.org/en/)

## Build for TS-land

1. Install dependencies
1. Run `$ npm install` in `ts`

## Build for C-land

1. Install dependencies
1. Run `make`
1. Find `./lib/libmeasuresuite.{a,so}` and use the methods from [`./lib/src/include/measuresuite.h`](./lib/src/include/measuresuite.h)
1. Find `ms`, a small CLI-tool. Essentially a wrapper to load files into Measuresuite. `./ms --help` for more info, but in a nutshell: `./ms ./my/file.asm ./my/secondfile.bin` prints the json.

## Run tests

1. For TypeScript-land tests `cd ts && npm i && npm test`
1. For C-land tests `make check -C lib`
1. Find the html versions of the test report in `{lib,ts}/coverage/index.html`

## Use cases


## Acknowledgements
#### This project was supported by:  
* The Air Force Office of Scientific Research (AFOSR) under award number FA9550-20-1-0425
* An ARC Discovery Early Career Researcher Award (project number DE200101577) 
* An ARC Discovery Project (project number DP210102670)  
* The Blavatnik ICRC at Tel-Aviv University  
* the Defense Advanced Research Projects Agency (DARPA) and Air Force Research Laboratory (AFRL) under contracts FA8750-19-C-0531 and HR001120C0087
* the National Science Foundation under grant CNS-1954712
* Gifts from AMD, Google, and Intel  
