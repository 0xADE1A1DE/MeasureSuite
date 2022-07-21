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



