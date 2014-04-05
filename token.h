#ifndef TOKEN_H
#define TOKEN_H

typedef struct Token {
    int   code;
    char* text;
    char* file;
    int   line;
} Token;

Token* alloc_token();
Token* next_token(const char* text, int* pos);

#endif
