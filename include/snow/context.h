
#ifndef SNOW_CONTEXT_H
#define SNOW_CONTEXT_H

struct smap;

typedef struct sctx {
    struct smap* types;
    uint64_t hash_seed;
} sctx;

sctx* sctx_alloc();

#endif

