#include "utilsPass.h"

/*Function to check if the line contains a valid data instruction name*/
int isDataLable(char* lable)
{
    /* Clearing the line from extra white spaces in the end and begining */
    trimWhitespace(lable);

    /*If the line contains a valid data instriction - return 1*/
    if (strncmp(lable, ".data", 5) == 0 || strncmp(lable, ".string", 7) == 0)
    {
        return 1;
    }

    return 0;
}


/*Function to check if the line contains a valid code instruction name*/
int isCodeLable(char* lable)
{
    /*Declaring variables*/
    int i = 0;
    const char* codeInstructions[] = CODE_INSTRUCTIONS_NAMES;

    /* Clearing the line from extra white spaces in the end and begining */
    trimWhitespace(lable);

    /*If the line contains a valid code instriction - return 1*/
    for (i = 0; i < 16; i++)
    {
        if (strncmp(lable, codeInstructions[i], strlen(codeInstructions[i])) == 0)
        {
            return 1;
        }
    }

    return 0;
}


int isExternLable(char* lable)
{
    /* Clearing the line from extra white spaces in the end and begining */
    trimWhitespace(lable);

    /*If the line contains a valid code instriction - return 1*/
    if (strncmp(lable, ".extern", 7) == 0)
    {
        return 1;
    }

    return 0;
}


int isEntryLable(char* lable)
{
    /* Clearing the line from extra white spaces in the end and begining */
    trimWhitespace(lable);

    /*If the line contains a valid code instriction - return 1*/
    if (strncmp(lable, ".entry", 6) == 0)
    {
        return 1;
    }

    return 0;
}



int processDataInstruction(char* line, ptrNode *dataImage)
{
    return 1;
}


int isAlphanumeric(const char *str) 
{
    while (*str) 
    {
        if (!isalnum((unsigned char)*str)) 
        {
            return 0;  /*We found a non-alphanumeric charecters*/
        }
        str++;
    }
    return 1;  /*All charecters are alphanumeric*/
}

int numOfOperands(char* line)
{
    return 1;
}


int numOfMemWord(char* line)
{
    return 1;
}


int processCodeInstruction(char* line, ptrNode *codeImage)
{
    return 1;
}