#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./include/structs.h"
#include "./include/parser.h"
#include "./include/compiler.h"

int main(int argc, char* argv[])
{
    if (argc == 3 && (strcmp(argv[1], "--compile") == 0))
    {
        const char * file = read_file(argv[2]);

        int * ln;
        Token *tokenlist = parser(file, ln);

        printf("------output------\n");
        compile(tokenlist, *ln);

        free(tokenlist);
    }

    return 0;
}