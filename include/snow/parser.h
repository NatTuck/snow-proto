#ifndef PARSER_H
#define PARSER_H

#include "snow/ast.h"

void* ParseAlloc(void* fn);
void  ParseFree(void* pp, void* fn);
void  Parse(void* pp, int tt, char* ss, TreeNode** nn);

#endif
