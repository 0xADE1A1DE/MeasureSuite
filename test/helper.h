#ifndef HELPER_H
#define HELPER_H
#include <measuresuite.h>
/**
 * this function prints ms's errors to stderror.
 */
void error_handling_helper(measuresuite_t ms);

/*
 * same as error_handling_helper but uses given @param tpl_str instead of the
 * default.
 */
void error_handling_helper_template_str(measuresuite_t ms, const char *tpl_str);

// a skipped test returns with 77 (based on Auto tools convention).
#define SKIP 77

// Bit position of flag from CPUID, according to Intel manual
#define ADX 19
#define BMI2 8

/**
 * @returns 1 if the bit is set
 */
int check_ise_bit(int bit_no);
// the cpuid trick does not work (reliably) on the GH-CI. So we will need to use
// the SIGILL handler. Which needs a pointer to a function.
#include <signal.h> //  sigaction
#include <stdlib.h>

void exit_skip();

#define SIGILL_SETUP()                                                         \
  do {                                                                         \
    if (!check_ise_bit(BMI2) || !check_ise_bit(ADX))                           \
      exit_skip();                                                             \
    struct sigaction sa;                                                       \
    sa.sa_sigaction = &exit_skip;                                              \
    sigaction(SIGILL, &sa, NULL);                                              \
  } while (0)

#endif
