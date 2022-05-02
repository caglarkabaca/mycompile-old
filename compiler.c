#include "./include/compiler.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void compile(const Token* tokenlist, int token_count)
{
    Var * varlist = (Var *)malloc(0);
    int varsize = 0;

    for (int i = 0; i < token_count; i++)
    {
        Token token = tokenlist[i];

        if (strcmp(token.name, "PRINT") == 0)
        {
            if (token.vars[0].called)
            {
                for(int i = 0; i < varsize; i++)
                {
                    if(strcmp(varlist[i].called, token.vars[0].called) == 0)
                        token.vars[0] = varlist[i];
                }
            }

            if(token.vars[0].type == STRING)
            {
                printf("%s", (char *)token.vars[0].ptr);
            }
            else if(token.vars[0].type == INT)
            {
                printf("%d", *(int *)token.vars[0].ptr);
            }
            continue;
        }

        if (strcmp(token.name, "PRINTLN") == 0)
        {
            if (token.vars[0].called)
            {
                for(int i = 0; i < varsize; i++)
                {
                    if(strcmp(varlist[i].called, token.vars[0].called) == 0)
                        token.vars[0] = varlist[i];
                }
            }

            if(token.vars[0].type == STRING)
            {
                printf("%s\n", (char *)token.vars[0].ptr);
            }
            else if(token.vars[0].type == INT)
            {
                printf("%d\n", *(int *)token.vars[0].ptr);
            }
            continue;
        }

        if (strcmp(token.name, "SET") == 0)
        {
            int check = 0;

            for (int i = 0; i < varsize; i++)
            {
                if (strcmp(varlist[i].called, token.vars[0].called) == 0)
                {
                    check = 1;
                    varlist[i].type = token.vars[1].type;
                    varlist[i].ptr = token.vars[1].ptr;
                    break;
                }
            }
            
            if (!check)
            {
            varsize++;
            varlist = (Var *)realloc(varlist, sizeof(Var) * varsize);
            varlist[varsize - 1].called = token.vars[0].called;
            varlist[varsize - 1].type = token.vars[1].type;
            varlist[varsize - 1].ptr = token.vars[1].ptr;
            }
            continue;
        }

        if (strcmp(token.name, "ADD") == 0)
        {
            Var * final;
            Var * addone;
            Var * addtwo;

            for(int i = 0; i < varsize; i++)
            {
                if(strcmp(varlist[i].called, token.vars[0].called) == 0)
                    final = &varlist[i];
            }

            if (token.vars[1].called)
            {
                for(int i = 0; i < varsize; i++)
                {
                    if(strcmp(varlist[i].called, token.vars[1].called) == 0)
                        addone = &varlist[i];
                }
            }
            else
            {
                addone = &token.vars[1];
            }

            if (token.vars[2].called)
            {
                for(int i = 0; i < varsize; i++)
                {
                    if(strcmp(varlist[i].called, token.vars[2].called) == 0)
                        addtwo = &varlist[i];
                }
            }
            else
            {
                addtwo = &token.vars[2];
            }

            *(int *)final->ptr = *(int *)addone->ptr + *(int *)addtwo->ptr;
            continue;
        }

        if (strcmp(token.name, "GETINT") == 0)
        {
            int* data = (int *)malloc(sizeof(int));
            scanf("%d", data);

            int check = 0;

            for (int i = 0; i < varsize; i++)
            {
                if (strcmp(varlist[i].called, token.vars[0].called) == 0)
                {
                    check = 1;
                    varlist[i].type = INT;
                    varlist[i].ptr = data;
                    break;
                }
            }
            
            if (!check)
            {
                varsize++;
                varlist = (Var *)realloc(varlist, sizeof(Var) * varsize);
                varlist[varsize - 1].called = token.vars[0].called;
                varlist[varsize - 1].type = INT;
                varlist[varsize - 1].ptr = data;
            }
            
            continue;
        }

        if (strcmp(token.name, "SUB") == 0)
        {
            Var * final;
            Var * addone;
            Var * addtwo;

            for(int i = 0; i < varsize; i++)
            {
                if(strcmp(varlist[i].called, token.vars[0].called) == 0)
                    final = &varlist[i];
            }

            if (token.vars[1].called)
            {
                for(int i = 0; i < varsize; i++)
                {
                    if(strcmp(varlist[i].called, token.vars[1].called) == 0)
                        addone = &varlist[i];
                }
            }
            else
            {
                addone = &token.vars[1];
            }

            if (token.vars[2].called)
            {
                for(int i = 0; i < varsize; i++)
                {
                    if(strcmp(varlist[i].called, token.vars[2].called) == 0)
                        addtwo = &varlist[i];
                }
            }
            else
            {
                addtwo = &token.vars[2];
            }

            *(int *)final->ptr = *(int *)addone->ptr - *(int *)addtwo->ptr;
            continue;
        }

        if (strcmp(token.name, "HLT") == 0)
        {
            break;
        }

    }
}