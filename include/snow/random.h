#ifndef SNOW_RANDOM_H
#define SNOW_RANDOM_H

#include <stdint.h>

uint8_t* secure_random_bytes(int64_t nn);
uint64_t secure_random64();

#endif
