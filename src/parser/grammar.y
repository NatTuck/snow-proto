
%include {#include <assert.h>} 
%include {#include <string.h>} 
%include {#include <stdlib.h>} 

%include {#include "snow/ast.h"}

%parse_failure 
{
    printf("Giving up. Parser is hopelessly lost...\n");
}

%extra_argument { TreeNode** root }

%type module {TreeNode*}

module ::= funs(A).
{
    *root = A;
}

funs(Y) ::= fun(A).
{
    Y = alloc_list_node(A, 0);
}

funs(Y) ::= fun(A) funs(AS).
{
    Y = alloc_list_node(A, AS);
}

%type fun {TreeNode*}

fun(Y) ::= FUN SYMBOL(N) LPAREN params(PS) RPAREN block(B) END.
{
    Y = alloc_fun_node(0, N, PS, B);
}

fun(Y) ::= FUN LPAREN SYMBOL(T) RPAREN SYMBOL(N) LPAREN params(PS) RPAREN block(B) END.
{
    Y = alloc_fun_node(T, N, PS, B);
}

%type block {TreeNode*}

block(Y) ::= expr(A).
{
    Y = alloc_list_node(A, 0);
}

block(Y) ::= expr(A) SEMI.
{
    Y = alloc_list_node(A, 0);
}

block(Y) ::= expr(A) SEMI block(B).
{
    Y = alloc_list_node(A, B);
}

%type expr {TreeNode*}

expr(Y) ::= NUMBER(A). 
{
    Y = alloc_integer_node(atoi(A));
}

expr(Y) ::= SYMBOL(A).
{
    Y = alloc_symbol_node(A);
}

expr(Y) ::= STRING(A).
{
    Y = alloc_string_node(A);
}

expr(Y) ::= expr(A) DOTOP SYMBOL(C).
{
    TreeNode* sym = alloc_symbol_node(C);
    Y = alloc_dot_node(A, sym);
}

expr(Y) ::= expr(A) POWOP(B) expr(C).
{ 
    Y = alloc_binop_node(B, A, C);
}

expr(Y) ::= expr(A) MULOP(B) expr(C). 
{ 
    Y = alloc_binop_node(B, A, C);
}

expr(Y) ::= expr(A) ADDOP(B) expr(C). 
{ 
    Y = alloc_binop_node(B, A, C);
    printf("addop!\n");
}

expr(Y) ::= expr(A) SUBOP(B) expr(C).
{
    Y = alloc_binop_node(B, A, C);
}

expr(Y) ::= SYMBOL(A) BIND expr(B).
{
    TreeNode* sym = alloc_symbol_node(A);
    Y = alloc_bind_node(sym, B);
}

expr(Y) ::= UNARY(A) expr(B).
{
   Y = alloc_unop_node(A, B);
}

expr(Y) ::= SUBOP expr(A). [UNARY]
{
    Y = alloc_unop_node("-", A);
}

expr(Y) ::= LPAREN expr(A) RPAREN.
{
    Y = A;
}

params(Y) ::= SYMBOL(A).
{
    TreeNode* sym = alloc_symbol_node(A);
    Y = alloc_list_node(sym, 0);
}

params(Y) ::= SYMBOL(A) COMMA.
{
    TreeNode* sym = alloc_symbol_node(A);
    Y = alloc_list_node(sym, 0);
}

params(Y) ::= SYMBOL(A) COMMA params(AS).
{
    TreeNode* sym = alloc_symbol_node(A);
    Y = alloc_list_node(sym, AS);
}

lambda(Y) ::= BAR params(A) BAR ARROW block(B) END.
{
    Y = alloc_lambda_node(A, B);
}

expr(Y) ::= lambda(A).
{
    Y = A;
}

args(Y) ::= expr(A).
{
    Y = alloc_list_node(A, 0);
}

args(Y) ::= args(A) COMMA expr(B).
{
    Y = alloc_list_node(B, A);
}

expr(Y) ::= expr(A) LPAREN RPAREN.
{
    Y = alloc_call_node(A, 0);
}

expr(Y) ::= expr(A) LPAREN args(B) RPAREN.
{
    Y = alloc_call_node(A, reverse_list_node(B));
}

expr(Y) ::= expr(A) LPAREN args(B) COMMA RPAREN.
{
    Y = alloc_call_node(A, reverse_list_node(B));
    Y = B;
}

expr(Y) ::= expr(A) LPAREN RPAREN lambda(L).
{
    Y = alloc_call_lambda_node(A, 0, L);
}

expr(Y) ::= expr(A) LPAREN args(B) RPAREN lambda(L).
{
    Y = alloc_call_lambda_node(A, reverse_list_node(B), L);
}

expr(Y) ::= expr(A) LPAREN args(B) COMMA RPAREN lambda(L).
{
    Y = alloc_call_lambda_node(A, reverse_list_node(B), L);
}

%left SEMI.
%left COMMA.
%left BIND.
%left ADDOP SUBOP.
%left MULOP.
%left POWOP.
%right UNARY.
%right SYMBOL. // A call
%right DOTOP.
%right LPAREN.

