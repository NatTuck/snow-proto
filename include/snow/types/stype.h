#ifndef SNOW_STYPE_H
#define SNOW_STYPE_H

#include <stdint.h>
#include <stdbool.h>

typedef struct stype {
    char*        name;
    int64_t      size;
    struct smap* vtab;
} stype;

struct sctx;

stype* stype_get_by_name(struct sctx* ctx, const char* name);
stype* stype_alloc(struct sctx* ctx, const char* name);
sfun*  stype_get_method(stype* type, const char* name);
bool   stype_eq(stype* type0, stype* type1);

#endif
