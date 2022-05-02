#ifndef PARSER_H
#define PARSER_H

#include "structs.h"

char * read_file(const char* path);
Token *parser(const char * file, int *ln);

char *to_machinefile(Token * tokenlist, int token_count);

#endif