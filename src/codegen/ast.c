
#include <gc/gc.h>

#include "ast.h"

TreeNode*
alloc_tree_node(int type)
{
    TreeNode* tn = GC_malloc(sizeof(TreeNode));
    tn->type = type;
    return tn;
}

TreeNode* 
alloc_block_node(TreeNode* head, TreeNode* tail)
{
    TreeNode* tn = alloc_tree_node(BLOCK_TYPE);
    tn->arg0 = head;
    tn->arg1 = tail;
    return tn;
}

TreeNode* 
alloc_binop_node(char* op, TreeNode* arg0, TreeNode* arg1)
{
    TreeNode* tn = alloc_tree_node(BINOP_TYPE);
    tn->name = op;
    tn->arg0 = arg0;
    tn->arg1 = arg1;
    return tn;
}

TreeNode* 
alloc_unop_node(char* op, TreeNode* arg0)
{
    TreeNode* tn = alloc_tree_node(UNOP_TYPE);
    tn->name = op;
    tn->arg0 = arg0;
    return tn;
}

TreeNode* 
alloc_dot_node(TreeNode* arg0, char* attr)
{
    TreeNode *tn = alloc_tree_node(DOT_TYPE);
    tn->name = attr;
    tn->arg0 = arg0;
    return tn;
}

TreeNode* 
alloc_bind_node(char* name, TreeNode* arg0)
{
    TreeNode *tn = alloc_tree_node(BIND_TYPE);
    tn->name = attr;
    tn->arg0 = arg0;
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
alloc_lambda_node(TreeNode* params, TreeNode* body)
{
    TreeNode *tn = alloc_tree_node(BIND_TYPE);
    tn->arg0 = params;
    tn->arg1 = body;
    return tn;
}

TreeNode* 
alloc_call_node(TreeNode* fun, TreeNode* args)
{

}

TreeNode* 
alloc_call_lambda_node(TreeNode* fun, TreeNode* arg, 
        TreeNode* lambda)
{

}


