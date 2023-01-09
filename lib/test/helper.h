/**
 * Copyright 2023 University of Adelaide
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

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

void assert_string_in_json(measuresuite_t ms, const char *needle);

// a skipped test returns with 77 (based on Auto tools convention).
enum exit_codes {
  OK = 0,
  FAIL = 1,
  SKIP = 77,
  FATAL = 99,
};

// Bit position of flag from CPUID, according to Intel manual
enum ise_bits {
  ADX = 19,
  BMI2 = 8,
};

/**
 * @returns 1 if the bit is set
 */
int check_ise_bit(int bit_no);
// the cpuid trick does not work (reliably) on the GH-CI. So we will need to use
// the SIGILL handler. Which needs a pointer to a function.
#include <assert.h> // __ASSERT_FUNCTION
#include <signal.h> //  sigaction
#include <stdlib.h>

void exit_skip();

#if __USE_POSIX199309
#define SIGILL_SETUP()                                                         \
  do {                                                                         \
    if (!check_ise_bit(BMI2) || !check_ise_bit(ADX))                           \
      exit_skip();                                                             \
    struct sigaction siga = {.sa_sigaction = &exit_skip};                      \
    sigaction(SIGILL, &siga, NULL);                                            \
  } while (0)
#else
#define SIGILL_SETUP()                                                         \
  do {                                                                         \
    if (!check_ise_bit(BMI2) || !check_ise_bit(ADX))                           \
      exit_skip();                                                             \
  } while (0)
#endif

// do not use. use the macro ms_assert like you would use <assert.h>
void assert_print_ms_error(measuresuite_t ms, char *file, int lineno,
                           const char *func, const char *s_exp, int exp);

#define ms_assert_ok(exp)                                                      \
  if ((exp) != 0) {                                                            \
    assert_print_ms_error(ms, __FILE__, __LINE__, __ASSERT_FUNCTION, #exp,     \
                          ((exp) == 0));                                       \
  }

#define ms_assert(exp)                                                         \
  if (!(exp)) {                                                                \
    assert_print_ms_error(ms, __FILE__, __LINE__, __ASSERT_FUNCTION, #exp,     \
                          exp);                                                \
  }

#endif
