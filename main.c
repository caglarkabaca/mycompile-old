#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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


char * read_file(const char* path){
    FILE * fp = fopen(path, "r");
    fseek(fp, 0, SEEK_END);
    int size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char * buffer = (char *)malloc(sizeof(char) * (size + 1));
    fread(buffer, 1, size, fp);
    buffer[size] = '\0';
    fclose(fp);
    return buffer;

}

Token *parser(const char * file, int *ln){
    int file_index = 0;

    char buf[255];
    int buf_index = 0;

    int lines = 0; // her line bir komut diye düşünüyorum
    while (file[file_index] != '\0')
    {
        if (file[file_index] == '\n')
            lines++;
        file_index++;
    }
    lines++; // en sondaki komut için ekstra bir tane daha, her zaman tutmuyor ama
    file_index = 0;
    *ln = lines;

    Token *tokenlist = (Token *)malloc(sizeof(Token) * lines);
    int tokenlist_index = 0;
    
    Var *varlist = (Var *)malloc(0);
    int varlist_size = 0;

    while (1)
    {
        memset(buf, 0, buf_index);
        buf_index = 0;

        int string_reading = 0;

        while ( (file[file_index] != ' ' || string_reading) && file[file_index] != '\n' && file[file_index] != '\0')
        {
            buf[buf_index] = file[file_index];
            if (file[file_index] == '"')
                string_reading = 1;
            buf_index++;
            file_index++;
        }

        char * word = (char *)malloc(sizeof(char) * (buf_index + 1));
        for(int i = 0; i < buf_index; i++)
        {
            word[i] = buf[i];
        }
        word[buf_index] = '\0';

        //printf("%s\n", word);
        file_index++;

        if (word[buf_index - 1] == '"') // var olan tokenin
        {
            char * str = (char *)malloc(sizeof(char) * (buf_index - 1));
            for (int i = 1; i < buf_index - 1; i++)
            {
                str[i - 1] = word[i];
            }
            str[buf_index - 1] = '\0';
            int var_index = tokenlist[tokenlist_index - 1].var_count;
            if (var_index == 0)
                tokenlist[tokenlist_index - 1].vars = (Var *)malloc(sizeof(Var) * (var_index + 1));
            else
                tokenlist[tokenlist_index - 1].vars = (Var *)realloc(tokenlist[tokenlist_index - 1].vars, sizeof(Var) * (var_index + 1));
            tokenlist[tokenlist_index - 1].var_count++;
            tokenlist[tokenlist_index - 1].vars[var_index].type = STRING;
            tokenlist[tokenlist_index - 1].vars[var_index].ptr = str;
            //printf("added var %d of %s\n", tokenlist[tokenlist_index - 1].var.type, tokenlist[tokenlist_index - 1].name);
            continue;
        }

        if (word[0] == '#')
        {
            // char* to int
            int multby = 1;
            int *number = (int *)malloc(sizeof(int));
            for (int i = buf_index - 1; i > 0; i--)
            {
                *number += multby * (word[i] - '0');
                multby *= 10;
            }
            int var_index = tokenlist[tokenlist_index - 1].var_count;
            if (var_index == 0)
                tokenlist[tokenlist_index - 1].vars = (Var *)malloc(sizeof(Var) * (var_index + 1));
            else
                tokenlist[tokenlist_index - 1].vars = (Var *)realloc(tokenlist[tokenlist_index - 1].vars, sizeof(Var) * (var_index + 1));
            tokenlist[tokenlist_index - 1].var_count++;
            tokenlist[tokenlist_index - 1].vars[var_index].ptr = (void *)number;
            tokenlist[tokenlist_index - 1].vars[var_index].type = INT;
            tokenlist[tokenlist_index - 1].vars[var_index].called = 0;
            continue;
        }

        if (word[0] == '$')
        {
            char * var_name = (char *)malloc(sizeof(char) * (buf_index));
            for (int i = 1; i < buf_index; i++)
            {
                var_name[i - 1] = word[i];
            }
            var_name[buf_index] = '\0';
            
            Var var;
            int var_found = 0;
            for(int i=0; i < varlist_size; i++)
            {
                if (varlist[i].called == var_name)
                {
                    var = varlist[i];
                    var_found = 1;
                }
            }

            if (!var_found)
            {
                varlist_size++;
                varlist = (Var *)realloc(varlist, sizeof(Var) * varlist_size);
                varlist[varlist_size - 1].called = var_name;
                var = varlist[varlist_size - 1];
            }

            int var_index = tokenlist[tokenlist_index - 1].var_count;
            if (var_index == 0)
                tokenlist[tokenlist_index - 1].vars = (Var *)malloc(sizeof(Var) * (var_index + 1));
            else
                tokenlist[tokenlist_index - 1].vars = (Var *)realloc(tokenlist[tokenlist_index - 1].vars, sizeof(Var) * (var_index + 1));
            tokenlist[tokenlist_index - 1].var_count++;
            tokenlist[tokenlist_index - 1].vars[var_index] = var;
            continue;

        }

        tokenlist[tokenlist_index].name = word;
        tokenlist_index++;
        //printf("added token %s\n", token.name);
        
        if (file[file_index] == '\0') // dosyanın sonu
            break;

    }

    return tokenlist;
}

void compile(const Token* tokenlist, int token_count)
{
    Var * varlist = (Var *)malloc(0);
    int varsize = 0;

    for (int i = 0; i < token_count; i++)
    {
        Token token = tokenlist[i];

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
            varsize++;
            varlist = (Var *)realloc(varlist, sizeof(Var) * varsize);
            varlist[varsize - 1].called = token.vars[0].called;
            varlist[varsize - 1].type = token.vars[1].type;
            varlist[varsize - 1].ptr = token.vars[1].ptr;
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
        }

        if (strcmp(token.name, "HLT") == 0)
        {
            break;
        }

    }
}

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