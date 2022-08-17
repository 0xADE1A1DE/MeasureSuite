# MeasureSuite
![Unit Tests](https://github.com/0xADE1A1DE/MeasureSuite/actions/workflows/check.yml/badge.svg)
![Code Style](https://github.com/0xADE1A1DE/MeasureSuite/actions/workflows/clang-format-check.yml/badge.svg)
<!-- ![Version](https://img.shields.io/github/v/release/0xADE1A1DE/MeasureSuite?logo=github&style=flat) -->

This library measures the execution time for code.
In a nutshell, input is two assembly strings and a symbol in a shared object and the output is robust timing measures.
It can also predict the throughput of a Assembly program with the help of [uiCA (uops.info Code Analyzer)](https://github.com/andreas-abel/uiCA)

## Features
- It assembles assembly code using [AssemblyLine](https://github.com/0xADE1A1DE/AssemblyLine)
- Runs two assembly programs in a random fashion with random inputs.
- Checks if the results matches the results of a dynamically loaded method.
- Prediction of the throughput without running the code.
- C-interface
- TypeScript-interface
- Supports functions of the C-like type `void A(uint64_t *out, const uint64_t *in)` (up to three out and three in parameters)
- Reports chunk size counting. (i.e. how many instructions of a function beaks a chunk boundary)
- Returns a JSON string with the measurement metrics.
- Uses Performance Counters (PMC), falls back to `RDTSC` if PMC are unavailable.
- Features a measure-lib-only mode: Only provide a shared object file and a symbol. Be Aware: no checking and no random measurement possible (as there is nothing to inerleave / check against)

## Examples

### Increment a number (C-land)

- Find `increment`-function in [the test library](./test/all_lib.c)
```c
void increment(long *d, const long *s) {
    *d = *s + 1;
}
```
- Next, find the [`increment`-test](./test/test_increment.c)
- We see an assembly version of a program which adds one to the second parameter and writes the result to the first parameter. (`char fa[]`)
- We see the initialization of our measure parameters, the measurement and printing the JSON to the console.

### Plus 1 (TS-land)

- Find the `functionA` and `functionB` in the [functions.ts](./test/ts/functions.ts)
- Both functions increment a number.
- We set up the boilerplate to use MeasureSuite from TypeScript-land in the [Plus 1 Test](./test/ts/plus1.test.ts)
- And analyze the measurement Result

### uiCA: Curve25519 throughput estimation (TS-land)

- Find two implementations of the Curve25519-SQ method as `functionA` and `functionB` in the [functions-sq.ts](./test/ts/functions_sq.ts)
- MeasureSuite can be called from TypeScript-land in the [ui CA test](./test/ts/uica.test.ts)
- Note that the implementations use instructions, which are not supported in Sandy bridge CPUS.
- We see two tests, we call the static `measure_uiCA` method on the MeasureSuite class and get the estimation of the throughput for both functions.

## Dependencies
- [AssemblyLine](https://github.com/0xADE1A1DE/AssemblyLine) (Can be skipped if builing with `NO_AL=1`, then MeasureSuite will only be able to measure runtime of a symbol in a shared object)
- `git`, `make`
- For C-tests coverage `lcov` 
- For TS: [Node.js](https://nodejs.org/en/)

## Build for TS-land

1. Install dependencies
1. Run `$ npm install`

## Build for C-land

1. Install dependencies
1. Run `make`
1. Find `./libmeasuresuite.{a,so}` and use the methods from [`./src/include/measuresuite.h`](./src/include/measuresuite.h)

## Run tests

1. For TypeScript-land tests `npm i && npm test`
1. For C-land tests `make check`
1. Find the html versions of the test report in `coverage{,-c}/index.html`

## Acknowledgements
#### This project was supported by:  
* The Air Force Office of Scientific Research (AFOSR) under award number FA9550-20-1-0425
* An ARC Discovery Early Career Researcher Award (project number DE200101577) 
* An ARC Discovery Project (project number DP210102670)  
* The Blavatnik ICRC at Tel-Aviv University  
* the Defense Advanced Research Projects Agency (DARPA) and Air Force Research Laboratory (AFRL) under contracts FA8750-19-C-0531 and HR001120C0087
* the National Science Foundation under grant CNS-1954712
* Gifts from AMD, Google, and Intel  
