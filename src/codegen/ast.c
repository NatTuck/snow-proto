
#include <stdlib.h>
#include <assert.h>
#include <gc/gc.h>

#include "drip/carp.h"
#include "drip/lstring.h"

#include "snow/ast.h"

TreeNode*
alloc_tree_node(int type)
{
    TreeNode* tn = GC_malloc(sizeof(TreeNode));
    tn->type = type;
    return tn;
}

TreeNode*
alloc_integer_node(int64_t xx)
{
    TreeNode* tn = alloc_tree_node(INTEGER_TYPE);
    tn->data = GC_malloc_atomic(sizeof(int64_t));
    *((int64_t*)tn->data) = xx;
    return tn;
}

TreeNode* 
alloc_float_node(double xx)
{
    TreeNode* tn = alloc_tree_node(FLOAT_TYPE);
    tn->data = GC_malloc_atomic(sizeof(double));
    *((double*)tn->data) = xx;
    return tn;
}

TreeNode* 
alloc_symbol_node(const char* name)
{
    TreeNode* tn = alloc_tree_node(SYMBOL_TYPE);
    tn->data = (void*) lstrdup(name);
    return tn;
}

TreeNode* 
alloc_string_node(const char* name)
{
    TreeNode* tn = alloc_tree_node(STRING_TYPE);
    tn->data = (void*) lstrdup(name);
    return tn;
}

TreeNode*
alloc_list_node(TreeNode* head, TreeNode* tail)
{
    if (head == NULL)
        carp("Can't have null CAR in list.");

    TreeNode* tn = alloc_tree_node(LIST_TYPE);
    tn->arg0 = head;
    tn->arg1 = tail;
    return tn;
}

TreeNode* 
alloc_binop_node(const char* op, TreeNode* arg0, TreeNode* arg1)
{
    TreeNode* tn = alloc_tree_node(BINOP_TYPE);
    tn->name = lstrdup(op);
    tn->arg0 = arg0;
    tn->arg1 = arg1;
    return tn;
}

TreeNode* 
alloc_unop_node(const char* op, TreeNode* arg0)
{
    TreeNode* tn = alloc_tree_node(UNOP_TYPE);
    tn->name = lstrdup(op);
    tn->arg0 = arg0;
    return tn;
}

TreeNode* 
alloc_dot_node(TreeNode* arg0, TreeNode* attr)
{
    TreeNode *tn = alloc_tree_node(DOT_TYPE);
    tn->name = lstrdup((char*)attr->data);
    tn->arg0 = arg0;
    return tn;
}

TreeNode* 
alloc_bind_node(TreeNode* name, TreeNode* arg0)
{
    assert(name->type == SYMBOL_TYPE);

    TreeNode *tn = alloc_tree_node(BIND_TYPE);
    tn->name = lstrdup((char*)name->data);
    tn->arg0 = arg0;
    return tn;
}

TreeNode*
alloc_fun_node(const char* rtype, const char* name, TreeNode* params, TreeNode* body)
{
    char* rcvr = 0;

    if (rtype) {
        rcvr = lstrdup(rtype);
    }

    TreeNode* tn = alloc_tree_node(FUN_TYPE);
    tn->name = lstrdup(name);
    tn->data = rcvr;
    tn->arg0 = params;
    tn->arg1 = body;
    return tn;
}

TreeNode* 
alloc_lambda_node(TreeNode* params, TreeNode* body)
{
    TreeNode* tn = alloc_tree_node(LAMBDA_TYPE);
    tn->arg0 = params;
    tn->arg1 = body;
    return tn;
}

TreeNode* 
alloc_call_node(TreeNode* fun, TreeNode* args)
{
    TreeNode* tn = alloc_tree_node(CALL_TYPE);
    tn->arg0 = fun;
    tn->arg1 = args;
    return tn;
}

TreeNode* 
alloc_call_lambda_node(TreeNode* fun, TreeNode* args,
        TreeNode* lambda)
{
    TreeNode* tn = alloc_tree_node(CALL_LAMBDA_TYPE);
    tn->arg0 = fun;
    tn->arg1 = args;
    tn->arg2 = lambda;
    return tn;
}

TreeNode* 
reverse_list_node(TreeNode* xs)
{
    assert(xs->type == LIST_TYPE);

    TreeNode* ys = 0;

    for (TreeNode* ii = xs; ii != NULL; ii = ii->arg1) {
        ys = alloc_list_node(ii->arg0, ys);
    }

    return ys;
}

char*
pretty_print_tree(TreeNode* node)
{
    return pretty_print_list_items(node, "\n\n", 0);
}

char*
pretty_print_any(TreeNode* node, int dd)
{
    int64_t vv_i;
    double  vv_d;

    switch (node->type) {
    case INTEGER_TYPE:
        vv_i = *((int64_t*)node->data);
        return lsprintf("%ld", vv_i);
    case FLOAT_TYPE:
        vv_d = *((double*)node->data);
        return lsprintf("%f", vv_d);
    case SYMBOL_TYPE:
        return (char*)node->data;
    case STRING_TYPE:
        return pretty_print_string(node, dd);
    case BINOP_TYPE:
        return pretty_print_binop(node, dd);
    case UNOP_TYPE:
        return pretty_print_unop(node, dd);
    case DOT_TYPE:
        return pretty_print_dot(node, dd);
    case BIND_TYPE:
        return pretty_print_bind(node, dd);
    case LIST_TYPE:
        return pretty_print_list(node, dd);
    case FUN_TYPE:
        return pretty_print_fun(node, dd);
    case LAMBDA_TYPE:
        return pretty_print_lambda(node, dd);
    case CALL_TYPE:
        return pretty_print_call(node, dd);
    case CALL_LAMBDA_TYPE:
        return pretty_print_call_lambda(node, dd);
    default:
        carp("pretty_print_tree(): Bad node type.");
    }

    abort();
}

static
char*
indent(int dd)
{
    char* text = GC_malloc(2 * dd + 1);

    for (int ii = 0; ii < 2 * dd; ++ii)
        text[ii] = ' ';

    text[2*dd] = 0;
    return text;
}

char*
pretty_print_string(TreeNode* ss, int dd)
{
    assert(ss->type == STRING_TYPE);
    return lsprintf("\"\"\"%s\"\"\"", (char*)ss->data);
}

char*
pretty_print_binop(TreeNode* binop, int dd)
{
    assert(binop->type == BINOP_TYPE);
    char* arg0 = pretty_print_any(binop->arg0, dd);
    char* arg1 = pretty_print_any(binop->arg1, dd);
    return lsprintf("(%s %s %s)", arg0, binop->name, arg1);
}

char*
pretty_print_unop(TreeNode* unop, int dd)
{
    assert(unop->type == UNOP_TYPE);
    char* arg0 = pretty_print_any(unop->arg0, dd);
    return lsprintf("(%s %s)", unop->name, arg0);
}

char*
pretty_print_dot(TreeNode* dot, int dd)
{
    assert(dot->type == DOT_TYPE);
    char* arg0 = pretty_print_any(dot->arg0, dd);
    return lsprintf("%s.%s", arg0, dot->name);
}

char*
pretty_print_bind(TreeNode* bind, int dd)
{
    assert(bind->type == BIND_TYPE);
    char* symb = bind->name;
    char* arg0 = pretty_print_any(bind->arg0, dd);
    return lsprintf("%s = %s", symb, arg0);
}

char*
pretty_print_list_items(TreeNode* list, const char* sep, int dd)
{
    assert(list->type == LIST_TYPE);
    char* text = lstrdup("");

    for (TreeNode* ii = list; ii != NULL; ii = ii->arg1) {
        char* item = pretty_print_any(ii->arg0, 0);
        text = lsprintf("%s%s%s%s", indent(dd), text, item, sep);
    }

    return text;
}

char*
pretty_print_list(TreeNode* list, int dd)
{
    assert(list->type == LIST_TYPE);
    char* items = pretty_print_list_items(list, ", ", 0);
    return lsprintf("[%s]", items);
}

char*
pretty_print_fun(TreeNode* fun, int dd)
{
    assert(fun->type == FUN_TYPE);
    char* params = pretty_print_list_items(fun->arg0, ", ", 0);
    char* body   = pretty_print_list_items(fun->arg1, ";\n", dd + 1);

    if (fun->data) {
        char* rcvr = (char*) fun->data;
        return lsprintf(
            "fun (%s) %s(%s)\n%s;;\n", 
            rcvr,
            fun->name,
            params,
            body
        );
    }
    else {
        return lsprintf(
            "fun %s(%s)\n%s;;\n",
            fun->name,
            params,
            body
        );
    }
}

char*
pretty_print_lambda(TreeNode* lambda, int dd)
{
    assert(lambda->type == LAMBDA_TYPE);
    char* params = pretty_print_list_items(lambda->arg0, ", ", 0);
    char* body   = pretty_print_list_items(lambda->arg1, ";\n", dd + 1);
    return lsprintf("|%s| ->\n%s%s;;\n", params, body, indent(dd));
}

char*
pretty_print_call(TreeNode* call, int dd)
{
    assert(call->type == CALL_TYPE);
    char* fun  = pretty_print_any(call->arg0, dd);
    char* args = pretty_print_list_items(call->arg1, ", ", 0);
    return lsprintf("%s(%s)", fun, args);
}

char*
pretty_print_call_lambda(TreeNode* call, int dd)
{
    assert(call->type == CALL_LAMBDA_TYPE);
    char* fun  = pretty_print_any(call->arg0, dd);
    char* args = pretty_print_list_items(call->arg1, ", ", 0);
    char* lamb = pretty_print_lambda(call->arg2, dd);
    return lsprintf("%s(%s) %s", fun, args, lamb);
}



