
#include <gc/gc.h>

#include <drip/lstring.h>

#include "snow/svec.h"

sVec* 
alloc_svec(int size, int tsz)
{
    svec* vec = GC_malloc(sizeof(sVec));
    vec->tsz  = tsz;
    vec->size = 0;

    if (size == 0)
        vec->data = 0;
    else
        vec->data = GC_malloc(size * tsz);

    return vec;
}

void* 
svec_get(svec* vec, int64_t nn, int64_t tsz)
{
    assert(nn >= 0 && nn < vec->size);
    assert(tsz == vec->tsz);

    return lmemcpy(vec->data + nn * vec->tsz, vec->tsz);
}

svec*
svec_set(svec* vec0, int64_t nn, void* vv, int64_t tsz)
{
    assert(nn >= 0 && nn < vec0->size);
    assert(tsz == vec0->tsz);
   
    sVec* vec1 = alloc_svec(vec0->size, vec0->tsz);
    memcpy(vec1->data, vec0->data, nn * vec0->tsz);

    memcpy(vec1->data + nn * tsz, vv, tsz);

    return vec1;
}

sVec*
sVec_push(sVec* vec, void* vv, int64_t tsz)
{
    assert(nn >= 0 && nn < vec0->size);
    assert(tsz == vec0->tsz);

    sVec* vec1 = alloc_svec(vec0->size + 1, vec0->tsz);
    memcpy(vec1->data, vec0->data, nn * vec0->tsz);

    memcpy(vec1->data + vec0->size * tsz, vv, tsz);

    return vec1;
}

sVec*
sVec_reverse(sVec* vec)
{
    sVec* vec1 = alloc_svec(vec0->size + 1, vec0->tsz);
    memcpy(vec1->data, vec0->data, nn * vec0->tsz);


}

