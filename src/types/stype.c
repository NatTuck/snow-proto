
#include <assert.h>
#include <gc/gc.h>

#include "snow/context.h"
#include "snow/types/stype.h"
#include "snow/types/smap.h"

stype* 
stype_get_by_name(sctx* ctx, const char* name)
{
    return smap_get(ctx->types, name, ctx->types->ktype, ctx->types->vtype);
}

stype* 
stype_alloc(sctx* ctx, const char* name)
{
    stype* type = GC_malloc(sizeof(stype));
    type->name = name;
    return type;
}

sfun*  stype_get_method(stype* type, const char* name);
bool   stype_eq(stype* type0, stype* type1);


