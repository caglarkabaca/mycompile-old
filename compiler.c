#include "./include/compiler.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void compile(const Token* tokenlist, int token_count)
{
    Var * varlist = (Var *)malloc(0);
    int varsize = 0;

    // bazı komutlar execute etmeden önce çalışmalı
    // örn setpos gibi
    // bu ilk bi grubu diğelerinden önce çalıştırmam lazım

    for (int tokenpos = 0; tokenpos < token_count; tokenpos++)
    {
        Token token = tokenlist[tokenpos];

        if (strcmp(token.name, "SETPOS") == 0)
        {
            int check = 0;
            int * current_token_pos = (int *)malloc(sizeof(int));
            *current_token_pos = tokenpos;

            for (int i = 0; i < varsize; i++)
            {
                if (strcmp(varlist[i].called, token.vars[0].called) == 0)
                {
                    check = 1;
                    varlist[i].type = INT;
                    varlist[i].ptr = (void *)current_token_pos;
                    break;
                }
            }
            
            if (!check)
            {
            varsize++;
            varlist = (Var *)realloc(varlist, sizeof(Var) * varsize);
            varlist[varsize - 1].called = token.vars[0].called;
            varlist[varsize - 1].type = INT;
            varlist[varsize - 1].ptr = (void *)current_token_pos;
            }
            continue;
        }

    }

    for (int tokenpos = 0; tokenpos < token_count; tokenpos++)
    {
        Token token = tokenlist[tokenpos];

        if (strcmp(token.name, "HLT") == 0)
            break;

        if (strcmp(token.name, "PRINT") == 0)
        {
            for (int i = 0; i < token.var_count; i++)
            {
                if (token.vars[i].called)
                {
                    for(int j = 0; j < varsize; j++)
                    {
                        if(strcmp(varlist[j].called, token.vars[i].called) == 0)
                            token.vars[i] = varlist[j];
                    }
                }

                if(token.vars[i].type == STRING)
                {
                    printf("%s", (char *)token.vars[i].ptr);
                }
                else if(token.vars[i].type == INT)
                {
                    printf("%d", *(int *)token.vars[i].ptr);
                }
            }
            continue;
        }

        if (strcmp(token.name, "PRINTLN") == 0)
        {
            for (int i = 0; i < token.var_count - 1; i++)
            {
                if (token.vars[i].called)
                {
                    for(int j = 0; j < varsize; j++)
                    {
                        if(strcmp(varlist[j].called, token.vars[i].called) == 0)
                            token.vars[i] = varlist[j];
                    }
                }

                if(token.vars[i].type == STRING)
                {
                    printf("%s", (char *)token.vars[i].ptr);
                }
                else if(token.vars[i].type == INT)
                {
                    printf("%d", *(int *)token.vars[i].ptr);
                }
            }

            int i = token.var_count - 1;
            if (token.vars[i].called)
            {
                for(int j = 0; j < varsize; j++)
                {
                    if(strcmp(varlist[j].called, token.vars[i].called) == 0)
                        token.vars[i] = varlist[j];
                }
            }

            if(token.vars[i].type == STRING)
            {
                printf("%s\n", (char *)token.vars[i].ptr);
            }
            else if(token.vars[i].type == INT)
            {
                printf("%d\n", *(int *)token.vars[i].ptr);
            }


            continue;
        }

        if (strcmp(token.name, "SET") == 0)
        {
            if (token.var_count == 2)
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
            }
            else if(token.var_count == 1)
            {
                int check = 0;

                for (int i = 0; i < varsize; i++)
                {
                    if (strcmp(varlist[i].called, token.vars[0].called) == 0)
                    {
                        check = 1;
                        break;
                    }
                }
                
                if (!check)
                {
                varsize++;
                varlist = (Var *)realloc(varlist, sizeof(Var) * varsize);
                varlist[varsize - 1].called = token.vars[0].called;
                }
            }
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

        if (strcmp(token.name, "MUL") == 0)
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

            *(int *)final->ptr = *(int *)addone->ptr * *(int *)addtwo->ptr;
            continue;
        }

        if (strcmp(token.name, "DIV") == 0)
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

            *(int *)final->ptr = *(int *)addone->ptr / *(int *)addtwo->ptr;
            continue;
        }

        if (strcmp(token.name, "GOTO") == 0)
        {
            Var * pos;

            for(int i = 0; i < varsize; i++)
            {
                if(strcmp(varlist[i].called, token.vars[0].called) == 0)
                    pos = &varlist[i];
            }

            tokenpos = *(int *)pos->ptr;
            continue;
        }

        if (strcmp(token.name, "GOGT") == 0)
        {
            // a > b ok
            Var * pos;
            Var * a;
            Var * b;

            for(int i = 0; i < varsize; i++)
            {
                if(strcmp(varlist[i].called, token.vars[0].called) == 0)
                    pos = &varlist[i];
            }

            if (token.vars[1].called)
            {
                for(int i = 0; i < varsize; i++)
                {
                    if(strcmp(varlist[i].called, token.vars[1].called) == 0)
                        a = &varlist[i];
                }
            }
            else
                a = &token.vars[1];

            if (token.vars[2].called)
            {
                for(int i = 0; i < varsize; i++)
                {
                    if(strcmp(varlist[i].called, token.vars[2].called) == 0)
                        b = &varlist[i];
                }
            }
            else
                b = &token.vars[2];

            if (*(int *)a->ptr > *(int *)b->ptr)
                tokenpos = *(int *)pos->ptr;
            continue;
        }

        if (strcmp(token.name, "GOLT") == 0)
        {
            // a < b ok
            Var * pos;
            Var * a;
            Var * b;

            for(int i = 0; i < varsize; i++)
            {
                if(strcmp(varlist[i].called, token.vars[0].called) == 0)
                    pos = &varlist[i];
            }

            if (token.vars[1].called)
            {
                for(int i = 0; i < varsize; i++)
                {
                    if(strcmp(varlist[i].called, token.vars[1].called) == 0)
                        a = &varlist[i];
                }
            }
            else
                a = &token.vars[1];

            if (token.vars[2].called)
            {
                for(int i = 0; i < varsize; i++)
                {
                    if(strcmp(varlist[i].called, token.vars[2].called) == 0)
                        b = &varlist[i];
                }
            }
            else
                b = &token.vars[2];

            if (*(int *)a->ptr < *(int *)b->ptr)
                tokenpos = *(int *)pos->ptr;
            continue;
        }

    }
}