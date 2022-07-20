#ifndef RANDOMIZER_H
#define RANDOMIZER_H

#include "struct_measuresuite.h"
#include <stdint.h> // uint64_t

int init_random(struct measuresuite *);
int end_random(struct measuresuite *);
int randomize(struct measuresuite *);

int get_random_byte(struct measuresuite *, uint8_t *dest);

#endif
