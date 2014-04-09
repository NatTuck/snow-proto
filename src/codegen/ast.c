
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
alloc_block_node(TreeNode* exprs)
{
    TreeNode* tn = alloc_tree_node(BLOCK_TYPE);
    tn->arg0 = exprs;
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

    for (TreeNode* ii = xs; ii->arg0 != NULL; ii = ii->arg1) {
        ys = alloc_list_node(ii->arg0, ys);
    }

    return ys;
}

char*
pretty_print_tree(TreeNode* node)
{
    return pretty_print_any(node, 0);
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
    case BLOCK_TYPE:
        return pretty_print_block(node, dd);
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
    return lsprintf("\"\"\"%s\"\"\"", (char*)ss->data);
}

char*
pretty_print_binop(TreeNode* binop, int dd)
{
    char* arg0 = pretty_print_any(binop->arg0, dd);
    char* arg1 = pretty_print_any(binop->arg1, dd);
    return lsprintf("(%s %s %s)", arg0, binop->name, arg1);
}

char*
pretty_print_unop(TreeNode* unop, int dd)
{
    char* arg0 = pretty_print_any(unop->arg0, dd);
    return lsprintf("(%s %s)", unop->name, arg0);
}

char*
pretty_print_dot(TreeNode* dot, int dd)
{
    assert(dot->type == DOT_TYPE);
    char* arg0 = pretty_print_any(dot->arg0, dd);
    char* arg1 = pretty_print_any(dot->arg1, dd);
    return lsprintf("%s.%s", arg0, arg1);
}

char*
pretty_print_bind(TreeNode* bind, int dd)
{
    assert(bind->type == BIND_TYPE);
    char* symb = bind->name;
    char* arg0 = pretty_print_any(bind->arg0, dd);
    return lsprintf("%s = %s", symb, arg0);
}

static
char*
pretty_print_list_items(TreeNode* list)
{
    char* text = lstrdup("");

    for (TreeNode* ii = list; ii != NULL; ii = ii->arg1) {
        char* item = pretty_print_any(ii->arg0, 0);
        text = lsprintf("%s%s, ", text, item);
    }

    return text;
}

char*
pretty_print_list(TreeNode* list, int dd)
{
    char* items = pretty_print_list_items(list);
    return lsprintf("[%s]", items);
}

char*
pretty_print_block(TreeNode* block, int dd)
{
    char* text = lstrcat(indent(dd), "{{\n");

    TreeNode* ii = block->arg0;

    for (; ii != NULL; ii = ii->arg1) {
        text = lstrcat(text, indent(dd + 1));
        text = lstrcat(text, pretty_print_any(ii->arg0, dd + 1));
        text = lstrcat(text, "\n");
    }

    text = lstrcat(text, indent(dd));
    return lstrcat(text, "}}\n");
}

char*
pretty_print_lambda(TreeNode* lambda, int dd)
{
    char* params = pretty_print_list_items(lambda->arg0);
    char* body   = pretty_print_block(lambda->arg1, dd + 1);
    return lsprintf("|%s| ->\n%s\n%s;;\n", params, body, indent(dd));
}

char*
pretty_print_call(TreeNode* call, int dd)
{
    char* fun  = pretty_print_any(call->arg0, dd);
    char* args = pretty_print_list_items(call->arg1);
    return lsprintf("%s(%s)", fun, args);
}

char*
pretty_print_call_lambda(TreeNode* call, int dd)
{
    char* fun  = pretty_print_any(call->arg0, dd);
    char* args = pretty_print_list_items(call->arg1);
    char* lamb = pretty_print_lambda(call->arg2, dd);
    return lsprintf("%s(%s) %s", fun, args, lamb);
}



