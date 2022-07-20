#include "helper.h"
#include <measuresuite.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const char lib[] = {"./liball_lib.so"};
const char symbol[] = {"increment"};

int main() {

  char fa[] = {"mov rax, [rsi]\n"
               "add rax, 1\n"
               "mov [rdi], rax\n"
               "ret\n"};

  char fb[] = {"mov rax, [rsi]\n"
               "inc rax\n"
               "mov [rdi], rax\n"
               "ret\n"};

  /** I want at least ten measurements for each assembly function  */
  const int num_batches = 10;

  /** The functions are measures in a loop.
   * I want the total run time oft 4 iterations of this loop */
  const int batch_size = 4;

  /** I have one output pointer*/
  const int arg_num_out = 1;

  /** I have one input pointer*/
  const int arg_num_in = 1;

  /** My pointers in/out each point to an array of one element */
  const int arg_width = 1;

  /** I currently don't care about chunk counting*/
  const int chunksize = 0;

  /** The functions are called with random numbers.
   * If all numbers are valid, (like here) we want to mask them with
   * All ones'
   * If be set to 0xff, if the function is called with random values from [0,
   * 0xff], and the result is also only checked for one byte.
   * */
  const uint64_t bounds[] = {0xffffffffffffffff};

  /**
   * Measuresuite handle
   */
  measuresuite_t ms = NULL;

  /**
   * Initialize Measuresuite
   */
  if (ms_measure_init(&ms, arg_width, arg_num_in, arg_num_out, chunksize,
                      bounds, lib, symbol)) {
    error_handling_helper_template_str(ms,
                                       "Failed to measure_init. Reason: %s.");
    return 1;
  }

  /**
   * measure fa and fb
   */
  if (ms_measure(ms, fa, fb, batch_size, num_batches)) {
    error_handling_helper_template_str(ms, "Failed to measure. Reason: %s.");
    return 1;
  }

  /**
   * set up handles for the JSON output
   */
  const char *output = NULL;
  size_t jsonlen = 0;

  /**
   * get the JSON output
   * (the length of the string pointed to by output is written to jsonlen)
   */
  ms_getJson(ms, &output, &jsonlen);

  /**
   * print out all the output
   */
  printf("%s\n", output);

  /**
   * release all handles
   */
  if (ms_measure_end(ms)) {
    error_handling_helper_template_str(ms,
                                       "Failed to measure_end. Reason: %s.");
    return 1;
  }

  /**
   * profit.
   */
  return 0;
}
