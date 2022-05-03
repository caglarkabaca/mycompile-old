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
#define DIV 7
#define MUL 8
#define SETPOS 9
#define GOTO 10
#define GOGT 11
#define GOLT 12

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
    else if (strcmp(name, "DIV") == 0)
        return DIV;
    else if (strcmp(name, "MUL") == 0)
        return MUL;
    else if (strcmp(name, "SETPOS") == 0)
        return SETPOS;
    else if (strcmp(name, "GOTO") == 0)
        return GOTO;
    else if (strcmp(name, "GOGT") == 0)
        return GOGT;
    else if (strcmp(name, "GOLT") == 0)
        return GOLT;
    else
        return -1;
}