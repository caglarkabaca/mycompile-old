#include "./include/structs.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// opcodes
#define HLT 0
#define PRINT 1
#define PRINTLN 2
#define ADD 3
#define SUB 4
#define GETINT 5
#define SET 6

int return_opcode(char * name)
{
    if (strcmp(name, "HLT") == 0)
        return HLT;
    else if (strcmp(name, "PRINT") == 0)
        return PRINT;
    else if (strcmp(name, "PRINTLN") == 0)
        return PRINTLN;
    else if (strcmp(name, "ADD") == 0)
        return ADD;
    else if (strcmp(name, "SUB") == 0)
        return SUB;
    else if (strcmp(name, "GETINT") == 0)
        return GETINT;
    else if (strcmp(name, "SET") == 0)
        return SET;
    else
        return -1;
}