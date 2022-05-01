#ifndef PARSER_H
#define PARSER_H

#include "structs.h"

char * read_file(const char* path);
Token *parser(const char * file, int *ln);

#endif