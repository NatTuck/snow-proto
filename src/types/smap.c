
#include <assert.h>
#include <gc/gc.h>

#include "snow/types/smap.h"
#include "snow/types/snil.h"
#include "snow/hash.h"

smap*
smap_alloc(int64_t size, stype* ktype, stype* vtype)
{
    smap* map = GC_malloc(sizeof(smap));
    map->size  = size;
    map->ktype = ktype;
    map->vtype = vtype;

    if (size == 0) {
        map->data = 0
    }
    else {
        int64_t item_size = ktype->size + vtype->size;
        map->data = GC_malloc(2 * item_size);
    }

    return map;
}

void* 
smap_get(smap* map, void* key, stype* ktype, stype* vtype)
{
    assert(stype_eq(ktype, map->ktype) && stype_eq(vtype, map->vtype));

    = stype_get_method(ktype, "hash");

}

smap*
smap_set(smap* map0, void* key, void* val, stype* ktype, stype* vtype)
{
    assert(stype_eq(ktype, map->ktype) && stype_eq(vtype, map->vtype));

}

uint8_t 
smap_contains(smap* map, void* key, stype* ktype)
{
    assert(stype_eq(ktype, map->ktype));

}

