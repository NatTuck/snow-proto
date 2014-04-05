
%include {#include <assert.h>} 
%include {#include <string.h>} 

%parse_failure 
{
    printf("Giving up.  Parser is hopelessly lost...\n");
}

module ::= expr.

expr(Y) ::= NUMBER(A). 
{ 
    printf("(%s)\n", A);
    Y = A;
}

expr(Y) ::= SYMBOL(A).
{
    printf("%s\n", A);
    Y = A;
}

expr(Y) ::= expr(A) DOTOP(B) expr(C).
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

expr(Y) ::= expr SEMI expr.
{
    printf("semi\n");
    Y = strdup(";");
}

args(Y) ::= SYMBOL(A).
{
    printf("sym %s\n", A);
    Y = strdup("args(1)");
}

expr(Y) ::= BAR args BAR ARROW(W) expr END.
{
    printf("%s\n", W);
    Y = W;
}

%left SEMI.
%left ADDOP.
%left MULOP.
%left POWOP.
%left DOTOP.

