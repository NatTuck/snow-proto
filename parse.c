
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "parser.h"
#include "grammar.h"
#include "token.h"
// calmphoenix400

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

        while ((tt = next_token(line, &nn))) {
            Parse(parser, tt->code, tt->text);
        }

        Parse(parser, 0, 0);

        ParseFree(parser, free);

        free(line);
    }


    printf("\nEOF\n");

    return 0;
}
