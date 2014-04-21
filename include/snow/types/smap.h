#ifndef SNOW_SMAP_H
#define SNOW_SMAP_H

#include "snow/types/stype.h"

typedef struct smap {
    int64_t  size;
    stype*   ktype;
    stype*   vtype;
    uint8_t* data;
} smap;

smap* smap_alloc(int64_t size, stype* ktype, stype* vtype);
void* smap_get(smap* map, void* key, stype* ktype, stype* vtype);
smap* smap_set(smap* map0, void* key, void* val, stype* ktype, stype* vtype);
uint8_t smap_contains(smap* map, void* key, stype* ktype);

