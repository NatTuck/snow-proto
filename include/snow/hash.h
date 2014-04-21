#ifndef SNOW_HASH_H
#define SNOW_HASH_H

#include <stdint.h>
#include <stdbool.h>

uint32_t hash32(const void *data, size_t nbytes);
uint64_t hash64(const void* data, size_t nbytes);

// retbuf must be at least 16 bytes long
bool hash128(const void *data, size_t nbytes, void *retbuf);

#endif
