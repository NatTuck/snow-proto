
#include <gc/gc.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "snow/token.h"

#include "grammar.h"

char*
lstrdupn(const char* aa, int nn)
{
    char* bb = GC_malloc(nn + 1);
    
    for (int ii = 0; ii < nn; ++ii) {
        bb[ii] = aa[ii];
    }

    bb[nn] = 0;
    return bb;
}

char*
lstrdup(const char* aa)
{
    return lstrdupn(aa, strlen(aa));
}

char*
token_get_number(const char* text, int p0)
{
    int p1 = p0;

    while (isdigit(text[p1])) {
        p1++;
    }

    return lstrdupn(text + p0, p1 - p0);
}

char*
token_get_symbol(const char* text, int p0)
{
    int p1 = p0;

    while (isalpha(text[p1])) {
        p1++;
    }

    return lstrdupn(text + p0, p1 - p0);
}

Token* 
alloc_token()
{
    return GC_malloc(sizeof(Token));
}

Token* 
next_token(const char* text, int* pos)
{
    while (isspace(text[*pos])) {
        ++*pos;
    }
    
    if (text[*pos] == 0) {
        return 0;
    }

    Token* token = alloc_token();

    switch (text[*pos]) {

    case '~':
    case '@':
    case '!':
        token->code = UNARY;
        token->text = lstrdupn(text + *pos, 1);
        break;

    case '-':
        if (text[*pos+1] == '>') {
            token->code = ARROW;
            token->text = lstrdupn(text + *pos, 2);
        }
        else {
            token->code = SUBOP;
            token->text = lstrdupn(text + *pos, 1);
        }
        break;

    case '+':
        token->code = ADDOP;
        token->text = lstrdupn(text + *pos, 1);
        break;

    case '*':
    case '/':
    case '%':
        token->code = MULOP;
        token->text = lstrdupn(text + *pos, 1);
        break;
        
    case '^':
        token->code = POWOP;
        token->text = lstrdupn(text + *pos, 1);
        break;

    case '|':
        token->code = BAR;
        token->text = lstrdupn(text + *pos, 1);
        break;

    case ';':
        if (text[*pos + 1] == ';') {
            token->code = END;
            token->text = lstrdupn(text + *pos, 2);
        }
        else {
            token->code = SEMI;
            token->text = lstrdupn(text + *pos, 1);
        }
        break;

    case '=':
        token->code = BIND;
        token->text = lstrdupn(text + *pos, 1);
        break;

    default: 
        if (isdigit(text[*pos])) {
            token->code = NUMBER;
            token->text = token_get_number(text, *pos);
        }
        else if (isalpha(text[*pos])) {
            token->code = SYMBOL;
            token->text = token_get_symbol(text, *pos);
        }
    }

    assert(token->text != 0);

    *pos += strlen(token->text);

    return token;
}

