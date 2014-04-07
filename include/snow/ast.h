#ifndef AST_H
#define AST_H

#include <stdint.h>

enum {
    BLOCK_TYPE,
    BINOP_TYPE,
    UNOP_TYPE,
    DOT_TYPE,
    BIND_TYPE,
    LIST_TYPE,
    LAMBDA_TYPE,
    CALL_TYPE,
    CALL_LAMBDA_TYPE,
    INTEGER_TYPE,
    FLOAT_TYPE,
    SYMBOL_TYPE,
    STRING_TYPE
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
TreeNode* alloc_block_node(TreeNode* head, TreeNode* tail);
TreeNode* alloc_binop_node(char* op, TreeNode* arg0, TreeNode* arg1);
TreeNode* alloc_unop_node(char* op, TreeNode* arg0);
TreeNode* alloc_dot_node(TreeNode* arg0, char* attr);
TreeNode* alloc_bind_node(char* name, TreeNode* arg0);
TreeNode* alloc_lambda_node(TreeNode* params, TreeNode* body);
TreeNode* alloc_call_node(TreeNode* fun, TreeNode* args);
TreeNode* alloc_call_lambda_node(TreeNode* fun, TreeNode* arg,
        TreeNode* lambda);

#endif
