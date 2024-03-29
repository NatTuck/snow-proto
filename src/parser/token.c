
#include <gc/gc.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "drip/lstring.h"
#include "drip/carp.h"

#include "snow/token.h"

#include "grammar.h"

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

    case '(':
        token->code = LPAREN;
        token->text = lstrdupn(text + *pos, 1);
        break;

    case ')':
        token->code = RPAREN;
        token->text = lstrdupn(text + *pos, 1);
        break;

    case ',':
        token->code = COMMA;
        token->text = lstrdupn(text + *pos, 1);
        break;

    case '.':
        token->code = DOTOP;
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
            char* sym = token_get_symbol(text, *pos);

            if (streq(sym, "fun")) {
                token->code = FUN;
                token->text = sym;
            }
            else {
                token->code = SYMBOL;
                token->text = sym;
            }
        }
    }

    if (token->text == 0) {
        fprintf(stderr, "Unknown token here:\n  %s\n\n", text + *pos);
        carp("Tokenizer is giving up.");
    }

    *pos += strlen(token->text);

    //printf("token: %s (%d)\n", token->text, token->code);

    return token;
}

