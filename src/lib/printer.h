#include <stdint.h>
/**
 * prints the given number in binary to stdout
 */
void printbin_single_number(uint64_t);

/**
 * prints two numbers if they are the same in green and red if they are
 * diffeerent
 */
void printbin(uint64_t const *a, uint64_t const *b, int len, int l);
/**
 * same but in hex
 */
void printhex(uint64_t const *a, uint64_t const *b, int len, int l);
