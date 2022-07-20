#ifndef MS_ERROR_H
#define MS_ERROR_H
typedef enum {
  E_SUCCESS = 0,
  E_INVALID_INPUT__ARG_WIDTH,
  E_INVALID_INPUT__BOUNDS_NULL,
  E_INVALID_INPUT__NUM_ARG_IN,
  E_INVALID_INPUT__NUM_ARG_OUT,
  E_INVALID_INPUT__CHUNK_SIZE,
  E_INVALID_INPUT__NUM_BATCHES,
  E_INVALID_INPUT__BATCH_SIZE,
  E_INVALID_INPUT__IN_TOO_LARGE,
  E_INVALID_INPUT__ASM_FUNCTION_A,
  E_INVALID_INPUT__ASM_FUNCTION_B,
  E_INVALID_INPUT__LIB_CHECK_FILE_NOT_ACCESSIBLE,
  E_INTERNAL_RANDOMNESS__AI__MALLOC,
  E_INTERNAL_RANDOMNESS__AI__OPEN_FILE,
  E_INTERNAL_RANDOMNESS__AI__READ,
  E_INTERNAL_RANDOMNESS__AI__CLOSE_FILE,
  E_INTERNAL_RANDOMNESS__UNINITIALIZED,
  E_INTERNAL_MEASURE__FREE_A,
  E_INTERNAL_MEASURE__FREE_B,
  E_INTERNAL_MEASURE__AI__DLCLOSE,
  E_INTERNAL_MEASURE__AI__DLSYM,
  E_INTERNAL_MEASURE__AI__DLOPEN,
  E_INTERNAL_MEASURE__AI__ALLOC,
} ERROR_NUMBER;

#endif
