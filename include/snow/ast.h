#ifndef AST_H
#define AST_H

#include <stdint.h>

enum {
    INTEGER_TYPE,
    FLOAT_TYPE,
    SYMBOL_TYPE,
    STRING_TYPE,
    BINOP_TYPE,
    UNOP_TYPE,
    DOT_TYPE,
    BIND_TYPE,
    LIST_TYPE,
    FUN_TYPE,
    BLOCK_TYPE,
    LAMBDA_TYPE,
    CALL_TYPE,
    CALL_LAMBDA_TYPE
};

typedef struct TreeNode {
    int type;
    char* name;
    struct TreeNode* arg0;
    struct TreeNode* arg1;
    struct TreeNode* arg2;
    void* data;
} TreeNode;

TreeNode* alloc_tree_node(int type);
TreeNode* alloc_integer_node(int64_t xx);
TreeNode* alloc_float_node(double xx);
TreeNode* alloc_symbol_node(const char* name);
TreeNode* alloc_string_node(const char* name);
TreeNode* alloc_list_node(TreeNode* head, TreeNode* tail);
TreeNode* alloc_binop_node(const char* op, TreeNode* arg0, TreeNode* arg1);
TreeNode* alloc_unop_node(const char* op, TreeNode* arg0);
TreeNode* alloc_dot_node(TreeNode* arg0, TreeNode* attr);
TreeNode* alloc_bind_node(TreeNode* name, TreeNode* arg0);
TreeNode* alloc_fun_node(const char* rtype, const char* name, TreeNode* params, TreeNode* body);
TreeNode* alloc_lambda_node(TreeNode* params, TreeNode* body);
TreeNode* alloc_call_node(TreeNode* fun, TreeNode* args);
TreeNode* alloc_call_lambda_node(TreeNode* fun, TreeNode* arg,
        TreeNode* lambda);

TreeNode* reverse_list_node(TreeNode* xs);
char* pretty_print_list_items(TreeNode* node, const char* sep, int dd);

char* pretty_print_tree(TreeNode* node);
char* pretty_print_any(TreeNode* node, int dd);
char* pretty_print_integer(TreeNode* node, int dd);
char* pretty_print_float(TreeNode* node, int dd);
char* pretty_print_symbol(TreeNode* node, int dd);
char* pretty_print_string(TreeNode* node, int dd);
char* pretty_print_binop(TreeNode* node, int dd);
char* pretty_print_unop(TreeNode* node, int dd);
char* pretty_print_dot(TreeNode* node, int dd);
char* pretty_print_bind(TreeNode* node, int dd);
char* pretty_print_list(TreeNode* node, int dd);
char* pretty_print_fun(TreeNode* node, int dd);
char* pretty_print_lambda(TreeNode* node, int dd);
char* pretty_print_call(TreeNode* node, int dd);
char* pretty_print_call_lambda(TreeNode* node, int dd);

#endif
