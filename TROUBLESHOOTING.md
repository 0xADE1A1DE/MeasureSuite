## Building for TS

- When running `npm i`, node-gyp errors out with
```
../src/binding/measuresuite_binding.c:18:10: fatal error: node/node_api.h: No such file or directory
   18 | #include <node/node_api.h>
      |          ^~~~~~~~~~~~~~~~~
compilation terminated.
```
- This means that the `node/node_api.h`-header file could not be found.
- Try using `find / -type f -name 'node_api.h'` to find the file and  
    - either add the path to the `node` folder to the `include_dirs` in `binding.gyp` in the `measuresuite` target;
    - or use `CFLAGS=-I/path/to/node npm i` while installing.
- If `node/node_api.h` could not be found, get the node-package from [the node.js website](https://nodejs.org/en/download/current/) extract, find the `node_api.h` in there and set the paths accordingly.



## Running C Tests

- When running `make check`
- Some tests are skipped.
- Reason: Those require the CPU flags `BMI2` and `ADX`.
- Resolution: You can check with `lscpu | grep -e bmi2 -e adx` if they are available. If yes, [open a new Github Issue](https://github.com/0xADE1A1DE/MeasureSuite/issues/new). If not, run the tests on a different CPU.
 

## Running TS Tests

- When running `npm test`
- Error: `jest: command not found`
- Reason: Node.js dependencies are not installed (i.e. `node_modules` does not exist)
- Resolution: `npm i`


- When running `npm test`
- Some tests are skipped.
- Reason: we check, if `uiCA` is initialized correctly and skip those test if not.
- Resolution: `make install-uiCA` and run `npm test` again

- When running the uiCA-test (implicitly through `npm test`) the output says `ModuleNotFoundError: No module named 'xed'`
- Reason: This happens when the `uiCA` directory is corrupt (`xed.cpythong.*.so` is not present).
- Resolution: `make install-uiCA` and run `npm test` again



