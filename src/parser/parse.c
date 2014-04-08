
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include <readline/readline.h>
#include <readline/history.h>

#include "snow/parser.h"
#include "snow/token.h"
#include "snow/ast.h"

#include "grammar.h"

int
main(int argc, char* argv[])
{

    for (;;) {
        char* line = readline("> ");
        if (line == NULL)
            break;

        printf("Read: %s\n", line);

        void* parser = ParseAlloc(malloc);

        Token* tt;
        int nn = 0;

        TreeNode* root = 0;

        while ((tt = next_token(line, &nn))) {
            Parse(parser, tt->code, tt->text, &root);
        }

        Parse(parser, 0, 0, &root);

        ParseFree(parser, free);

        free(line);

        assert(root != 0);
        printf("%s\n", pretty_print_tree(root));
    }


    printf("\nEOF\n");

    return 0;
}
