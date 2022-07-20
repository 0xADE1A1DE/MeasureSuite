#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "struct_measuresuite.h"
/**
 * executes the functions in a R3 fashion.
 * writes the results to json in @param ms
 * @returns 0 on success, 1 on fail
 */
int run_measurement(struct measuresuite *ms);
#endif
