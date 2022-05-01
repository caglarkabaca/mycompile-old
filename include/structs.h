#ifndef STRUCTS_H
#define STRUCTS_H

#define INT 0
#define STRING 1

struct Var
{
    int type;
    void * ptr;
    char * called;
};
typedef struct Var Var;

struct Token
{
    char * name;
    Var * vars;
    int var_count;
};
typedef struct Token Token;

#endif