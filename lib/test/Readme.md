
## What is the SIGILL\_SETUP

The more complex tests (fiat curves) may only run on hardware, which has support for `BMI2` and `ADX`.
The macro does that check and exits prematurely without failing the suite
Additionally, it will catch a SIGILL exception and fail gracefully (if supported by OS)




