#include "errors.h"


/*Functions for handling with errors*/

int errorInData(char* line, char* inputFileName, int lineNumber)
{
    int error = 0;
    error = 1;
    return error;
}

int errorInCode(char* line, char* inputFileName, int lineNumber)
{
    int error = 0;
    error = 1;
    return error;
}

int errorInLabel(char* label, char* inputFileName, int lineNumber)
{
    int error = 0;
    int prevLength = strlen(label);

    /*If label is empty*/
    if (strlen(label) == 0)
    {
        fprintf(stderr, "Error: Empty label in file %s in line %d\n", inputFileName, lineNumber);
        error = 1;
    }

    /*If label is too long*/
    if (strlen(label) > MAX_LABEL_LENGTH)
    {
        fprintf(stderr, "Error: Label is too long in file %s in line %d\n", inputFileName, lineNumber);
        error = 1;
    }

    /*If label does not start with a letter*/
    if (!isalpha(label[0]))
    {
        fprintf(stderr, "Error: Label does not start with a letter in file %s in line %d\n", inputFileName, lineNumber);
        error = 1;
    }

    /*If not all charecters are letters / numbers*/
    if (!isAlphanumeric(label))
    {
        fprintf(stderr, "Error: Label contains non-alphanumeric charecters in file %s in line %d\n", inputFileName, lineNumber);
        error = 1;
    }

    trimWhitespace(label);
    if (strlen(label) != prevLength)
    {
        fprintf(stderr, "Error: Label ends with white spaces in file %s in line %d\n", inputFileName, lineNumber);
        error = 1;
    }

    return error;
}



int errorInExtern(char* label, char* inputFileName, int lineNumber)
{
    return 1;
}


int errorInEntry(char* label, char* inputFileName, int lineNumber)
{
    return 1;
}

