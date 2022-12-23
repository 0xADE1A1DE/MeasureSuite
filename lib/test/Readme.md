# Overview C-Tests

This directory contains the tests for C-land

- the `all_*.c` are the ground truth libraries
- the `test_*.c` are the unit/e2e tests
- `helper.{c,h}` give some convenience methods for the tests

## What is the SIGILL\_SETUP

The more complex tests (fiat curves) may only run on hardware, which has support for `BMI2` and `ADX`.
The macro does that check and exits prematurely without failing the suite
Additionally, it will catch a SIGILL exception and fail gracefully.




