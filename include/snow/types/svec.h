#ifndef SNOW_SVEC_H
#define SNOW_SVEC_H

#include "snow/types/stype.h"

typedef struct svec {
    int64_t  size;
    stype*   etype;
    uint8_t* data;
} svec;

svec* svec_alloc(int size, stype* etype);
void* svec_get(svec* vec, int64_t nn, stype* etype);
svec* svec_set(svec* vec0, int64_t nn, void* vv, stype* etype);
svec* svec_push(svec* vec0, void* vv, stype* etype);
svec* svec_reverse(sVec* vec0);
svec* svec_op_add(sVec* vec0, sVec* vec1);

#endif
