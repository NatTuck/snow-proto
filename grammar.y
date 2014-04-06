
%include {#include <assert.h>} 
%include {#include <string.h>} 
%include {#include <stdlib.h>} 

%parse_failure 
{
    printf("Giving up. Parser is hopelessly lost...\n");
}

module ::= block.

block(Y) ::= expr(A).
{
    Y = A;
}

block(Y) ::= expr(A) SEMI.
{
    Y = A;
}

block(Y) ::= expr(A) SEMI block(B).
{
    printf("block %s %s\n", A, B);
    Y = A;
}

expr(Y) ::= NUMBER(A). 
{ 
    printf("number = %s\n", A);
    Y = A;
}

expr(Y) ::= SYMBOL(A).
{
    printf("symbol = %s\n", A);
    Y = A;
}

expr(Y) ::= STRING(A).
{
    printf("string = %s\n", A);
    Y = A;
}

expr(Y) ::= expr(A) DOTOP(B) SYMBOL(C).
{
    printf("%s %s %s\n", B, A, C);
    Y = B;
}

expr(Y) ::= expr(A) POWOP(B) expr(C).
{ 
    printf("%s %s %s\n", B, A, C);
    Y = B;
}

expr(Y) ::= expr(A) MULOP(B) expr(C). 
{ 
    printf("%s %s %s\n", B, A, C); 
    Y = B;
}

expr(Y) ::= expr(A) ADDOP(B) expr(C). 
{ 
    printf("%s %s %s\n", B, A, C); 
    Y = B;
}

expr(Y) ::= expr(A) SUBOP(B) expr(C).
{
    printf("%s %s %s\n", B, A, C); 
    Y = B;
}

expr(Y) ::= SYMBOL(A) BIND expr(B).
{
    printf("Bind %s <- %s\n", A, B);
    Y = B;
}

expr(Y) ::= UNARY(A) expr(B).
{
   printf("unary %s (%s)\n", A, B);
   Y = B;
}

expr(Y) ::= SUBOP expr(A). [UNARY]
{
    printf("Neg %s\n", A);
    Y = A;
}

/*
expr(Y) ::= LPAREN expr(A) RPAREN.
{
    printf("Parens (%s)\n", A);
    Y = A;
}
*/

params(Y) ::= SYMBOL(A).
{
    printf("sym %s\n", A);
    Y = strdup("args(1)");
}

lambda(Y) ::= BAR params BAR ARROW(W) block END.
{
    printf("%s\n", W);
    Y = W;
}

expr(Y) ::= lambda(A).
{
    Y = A;
}

args(Y) ::= expr(A).
{
    Y = A;
}

args(Y) ::= args(A) COMMA expr(B).
{
    printf("Multiple args %s\n", A);
    Y = B;
}

expr(Y) ::= SYMBOL(A) LPAREN args(B) RPAREN.
{
    printf("call %s(%s)\n", A, B);
    Y = B;
}

expr(Y) ::= expr(A) LPAREN args(B) RPAREN.
{
    printf("call %s(%s)\n", A, B);
    Y = B;
}

expr(Y) ::= expr(A) LPAREN RPAREN.
{
    printf("call %s()\n", A);
    Y = A;
}

expr(Y) ::= expr(A) LPAREN args(B) COMMA RPAREN.
{
    printf("call %s(%s)\n", A, B);
    Y = B;
}

expr(Y) ::= expr(A) LPAREN args(B) RPAREN lambda(L).
{
    printf("call %s(%s) %s\n", A, B, L);
    Y = B;
}

expr(Y) ::= expr(A) LPAREN RPAREN lambda(L).
{
    printf("call %s()\n", A, L);
    Y = A;
}

expr(Y) ::= expr(A) LPAREN args(B) COMMA RPAREN lambda(L).
{
    printf("call %s(%s)\n", A, B, L);
    Y = B;
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

