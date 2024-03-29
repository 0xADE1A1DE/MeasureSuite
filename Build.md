# Build MeasureSuite

## Dependencies
- `make`, C compiler
- If you want to use ASM-strings, you need to install [AssemblyLine](https://github.com/0xADE1A1DE/AssemblyLine)
- For C-tests coverage `lcov` 
- For TS: [Node.js](https://nodejs.org/en/)

## Build for TS

1. Install dependencies (node, AssemblyLine)
1. Run `$ npm install` in `ts`
1. Enjoy `import {MeasureSuite} from "measuresuite";`

## Build for C-land

1. Install dependencies (make, clang, lcov, AssemblyLine)
1. Run `make`
1. Find `./lib/libmeasuresuite.{a,so}` and use the methods from [`./lib/src/include/measuresuite.h`](./lib/src/include/measuresuite.h)
1. Find `ms`, a small CLI-tool. Essentially a wrapper to load files into MeasureSuite. `./ms --help` for more info, but in a nutshell: `./ms ./my/file.asm ./my/secondfile.bin` prints the JSON.

## Run tests

1. For TypeScript tests `cd ts && npm i && npm test`
1. For C tests `make check -C lib`
1. Find the html versions of the test report in `{lib,ts}/coverage/index.html`

## Debug messages

To enable debug messages, you can pass `-DENABLE_DEBUG` when building
- C: `CPPFLAGS=-DENABLE_DEBUG make`
- TS: add `"ENABLE_DEBUG"` to `targets.defines` in `./ts/binding.gyp`, then run `npm install`

## Publish new version

Run all the checks
- `make check`
- `npm test`
- `npm run test-cov`
- `npm run lint-check`
- `npm run format-check`

Run the build to build js
- `npm run build`
