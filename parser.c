#include "./include/parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    Token *tokenlist = (Token *)malloc(sizeof(Token));
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
                string_reading = !string_reading;
            buf_index++;
            file_index++;
        }

        char * word = (char *)malloc(sizeof(char) * (buf_index + 1));
        for(int i = 0; i < buf_index; i++)
        {
            word[i] = buf[i];
        }
        word[buf_index] = '\0';
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
            //printf("added var %d of %s\n", tokenlist[tokenlist_index - 1].vars[var_index].type, tokenlist[tokenlist_index - 1].name);
            continue;
        }

        if (word[0] == '#')
        {
            // char* to int
            int multby = 1;
            int end_index = 0;

            if (word[1] == '-')
            {
                multby = -1; 
                end_index = 1;
            }

            int *number = (int *)malloc(sizeof(int));
            for (int i = buf_index - 1; i > end_index; i--)
            {
                *number += multby * (word[i] - '0');
                multby *= 10;
            }
            int var_index = tokenlist[tokenlist_index - 1].var_count;
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
            tokenlist[tokenlist_index - 1].vars = (Var *)realloc(tokenlist[tokenlist_index - 1].vars, sizeof(Var) * (var_index + 1));
            tokenlist[tokenlist_index - 1].var_count++;
            tokenlist[tokenlist_index - 1].vars[var_index] = var;
            continue;
        }

        tokenlist[tokenlist_index].name = word;
        tokenlist[tokenlist_index].vars = (Var *)malloc(sizeof(Var));
        tokenlist_index++;
        tokenlist = (Token *)realloc(tokenlist, sizeof(Token) * (tokenlist_index + 1));

        if (file[file_index] == '\0') // dosyanın sonu
            break;

    }

    *ln = tokenlist_index;
    return tokenlist;
}

char *to_machinefile(Token * tokenlist, int token_count)
{
    char * machine_code = (char *)malloc(sizeof(char));
    int size_machine = 0;
    int index = 0;
    for (int i = 0; i < token_count; i++)
    {

        Token tkn = tokenlist[i];
        Var* vars = tkn.vars;
        int var_count = tkn.var_count;

        // 4 => opcode
        // 15 => her var için ( 14 + 1 / ' ' + ptr) 
        int size = (4 + 15 * var_count);
        char *buf = (char *)malloc(sizeof(char) * (size + 1));
        size_machine += size + 1;
        machine_code = (char *)realloc(machine_code, sizeof(char) * size_machine);
        int opcode = return_opcode(tkn.name);

        sprintf(buf, "%04x", opcode);
        //printf("%04x ", opcode);
        buf[4] = ' ';

        for (int j = 0; j < var_count; j++)
        {
            if (vars[j].ptr)
                sprintf(buf + 5 + (j*15), "%p ", vars[j].ptr);
                //printf(" %p", vars[j].ptr);
            else if(vars[j].called)
                sprintf(buf + 5 + (j*15), "%p ", &vars[j].called);
                //printf(" %p", &vars[j].called);
        }

        buf[size] = '\n';
        //printf("%s", buf);
        sprintf(machine_code + index, "%s", buf);
        index += size + 1;

        free(buf);
    }
    machine_code[size_machine] = '\0';
    return machine_code;
}