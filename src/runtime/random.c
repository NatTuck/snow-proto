
#include <stdio.h>

#include "snow/random.h"

uint8_t*
secure_random_bytes(int64_t nn)
{
    uint64_t* bs = GC_malloc(nn);

    FILE* urand = fopen("/dev/urandom", "r");
    fread(bs, nn, 1, urand);
    fclose(urand);

    return bs;
}

uint64_t secure_random64()
{
    uint64_t rv;

    FILE* urand = fopen("/dev/urandom", "r");
    fread(&rv, sizeof(rv), 1, urand);
    fclose(urand);

    return rv;
}

