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

## Organization

This repository contains
- the C-library `libmeasuresuite` in [lib](./lib)
- a cli-tool `ms` in [bin](./bin); use like `./ms ./fileA.asm ./fileB.o`, out comes `JSON`.
- a TypeScript-Wrapper in [ts](./ts), around `libmeasuresuite` built with `node-gyp`.

More detailed in `Readme.md`'s in the respecive sub directory.
*Build*-instructions in [Build.md](./Build.md).

## Examples

Find C and TS examples in the [examples](./examples) directory. Some nees AssemblyLine installed.


### Sneak Peak C-lib

```c
#include <measuresuite.h>

/*
 * void add_two_numbers(uint64_t *out0, const uint64_t *in0, const uint64_t *in1) {
 *    *out0 = *in0 + *in1;
 * }
 */
char add_two_asm[] = {"mov rax, [rsi]\n"
                      "add rax, [rdx]\n"
                      "mov [rdi], rax\n"
                      "ret\n"};


  const int arg_width = 1;
  const int arg_num_out = 1;
  const int arg_num_in = 2;

  // our measuresuite handle
  measuresuite_t ms = NULL;

  // initializing the measuresuite
  ms_initialize(&ms, arg_width, arg_num_in, arg_num_out);

  int id = -1;
  ms_load_data(ms,                     // handle
               ASM,                    // type of input data is assembly
               (uint8_t *)add_two_asm, // pointer to input data
               strlen(add_two_asm),    // length of input data
               NULL, // symbol (ignored for BIN/ASM, optional for ELF, required
                     // for SHARED_OBJECT)
               &id); // ID (in/out)

  const int number_of_batches = 10; // 10 batches of
  const int batch_size = 100;       // 100 iterations of the function-unter-test (add_two_asm), each

  ms_measure(ms, batch_size, number_of_batches);

  const char *json = NULL;
  size_t len = 0;
  ms_get_json(ms, &json, &len);

  assert(json != NULL);
  assert(len != 0);

  printf("%s\n", json);
  // prints:
  //
  // {
  // "stats": {
  //   "numFunctions": 1,
  //   "runtime": 0,
  //   "incorrect": 0
  // },
  // "functions": [ { "type": "ASM", "chunks": 0 } ],
  // "cycles": [ [ 1352, 890, 895, 884, 888, 886, 886, 886, 884, 888 ] ]
  // }


  ms_terminate(ms);
  return 0;
}
```

### Sneak Peak CLI


```bash
$ make
$ make -B -C ./examples/elf/add_two_numbers.o
$ ./ms -n 3 ./examples/elf/add_two_numbers.o ./examples/elf/add_two_numbers.asm | jq
``` 

```json
{
  "stats": {
    "numFunctions": 2,
    "runtime": 1,
    "incorrect": 0
  },
  "functions": [
    {
      "type": "ELF"
    },
    {
      "type": "ASM",
      "chunks": 0
    }
  ],
  "cycles": [
    [ 7074, 7705, 7358 ],
    [ 7640, 7259, 7858 ]
  ]
}

```

### Sneak Peak C

```ts
import { type MeasureResult, Measuresuite } from "measuresuite";

/**
 * our assembly strings to measure, same as in ./add_two_numbers.c
 */

const functionA = [
  "mov rax, [rsi]",
  "add rax, [rdx]",
  "mov [rdi], rax",
  "ret",
].join("\n");

const functionB = [
  "mov rax, [rsi]",
  "push rbx",
  "mov rbx, [rdx]",
  "lea rax, [rbx + rax]",
  "mov [rdi], rax",
  "pop rbx",
  "ret",
].join("\n");

const arg_width = 1;
const arg_num_out = 1;
const arg_num_in = 2;

// create a Measuresuite object
const ms = new Measuresuite(arg_width, arg_num_in, arg_num_out);
ms.enableChecking();

const nob = 50;
const batchSize = 10000;

// measure
const measurementResult: MeasureResult | null = ms.measure(batchSize, nob, [ functionA, functionB ]);



console.log( `The Measurement took ${measurementResult.stats.runtime}ms to complete`);

const [functionARes, functionBRes] = measurementResult.cycles;
console.log(`Function A's cycles: ${functionARes.join(",")}`);
console.log(`Function B's cycles: ${functionBRes.join(",")}`);

const medianA = functionARes.sort().at(Math.floor(nob / 2));
const medianB = functionBRes.sort().at(Math.floor(nob / 2));

console.log(`Function A's median: ${medianA}`);
console.log(`Function B's median: ${medianB}`);

console.log(
  `Function A is ${medianA < medianB ? "" : "not"} faster than Function B`
);
```

## Acknowledgements
#### This project was supported by:  
* The Air Force Office of Scientific Research (AFOSR) under award number FA9550-20-1-0425
* An ARC Discovery Early Career Researcher Award (project number DE200101577) 
* An ARC Discovery Project (project number DP210102670)  
* The Blavatnik ICRC at Tel-Aviv University  
* the Defense Advanced Research Projects Agency (DARPA) and Air Force Research Laboratory (AFRL) under contracts FA8750-19-C-0531 and HR001120C0087
* the National Science Foundation under grant CNS-1954712
* Gifts from AMD, Google, and Intel  
