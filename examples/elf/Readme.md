# Object-file / Elf-file  / shared object examples

- The `Makefile` will compile the asm to an object.
- Then this file is being loaded into the program and measured.

## C example
- Find the example `./add_two_numbers.c` and the `./add_two_numbers.asm`.
- Run `make example-c-elf` to assemble `./add_two_numbers.asm`, build and run the example to use libmeasuresuite with an object file string.

## TS exmaple
- If you don't have AssemblyLine installed, note the "Use Typescript without AssemblyLine" instructions in [ BUILD.md ](../../Build.md)
- Needs `npm` to be in `$PATH`
- Find the example `./add_two_numbers.ts` 
- Run `make example-ts-elf` to install dependencies, transpile, and run the test as an example to use the typescript-wrapper and with an an object file.
