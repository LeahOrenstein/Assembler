#include "firstPass.h"

/* Function for managing the first pass */
int firstPass(const char* inputFileName, ptrNode* memoryImage, ptrNode* symbolListPtr)
{
    /*Declaring variables*/

    /*Counters*/
    int IC = 100;
    int DC = 0;
    int L = 0;
    int lineNumber = 0;

    /*Flags*/
    int error = 0;
    int errorInLine = 0;
    char line[MAX_LINE_LENGTH];

    /*Lists*/
    ptrNode symbolList = NULL;
    ptrNode dataImage = NULL;
    ptrNode codeImage = NULL;
    ptrNode externList = NULL;
    ptrNode entryList = NULL;
    ptrNode tempNode = NULL;

    /* Opening the am file*/
    FILE* inputFile = fopen(inputFileName, "r");
    if (inputFile == NULL)
    {
        fprintf(stderr, "Error: Could not open file %s\n", inputFileName);
        return 0;
    }

    while (fgets(line, MAX_LINE_LENGTH, inputFile) != NULL)
    {
        lineNumber++;
        errorInLine = processLine(inputFile, inputFileName, line, &symbolList, &codeImage, &dataImage, &IC, &DC, lineNumber);
        if (errorInLine)
        {
            error = 1;
        }
    }

    
    return error? 0 : 1;

}


int processLine(FILE* inputFile, char* inputFileName, char* line, ptrNode* symbolListPtr, ptrNode* codeImage, ptrNode* dataImage, int* IC, int* DC, int lineNumber)
{
    /*Declaring variables*/
    ptrNode symbolList;
    char labelName[MAX_LABEL_LENGTH];
    char lineAfterLabel[MAX_LINE_LENGTH];
    char* labelNameTemp;
    ptrSymbol label;
    int error = false;
    int L = 0;
    int i = 0;

    /* Clearing the line from extra white spaces in the end and begining */
    trimWhitespace(line);

    /*Look for a label declaration*/
    while (i < strlen(line) && line[i] != ':')  i++; 
    
    if (line[i] == ':')
    {
        /*Label found, checks if valid and if so adding it to the symbols table*/

        /*Checking if the label name is valid*/
        sprintf(labelNameTemp,"%.*s\0", i, line);
        if (errorInLabel(labelNameTemp , inputFileName, lineNumber))
        {
            /*Error - invalid label name*/
            fprintf(stderr, "Error: Invalid label name in line %d file %s\n", lineNumber, inputFileName);
            error = true;
        }
        else
        {
            /*Copying the label name to a new string*/
            sprintf(labelName, "%.*s\0", i, line);
        }

        /*Checking if the command after the label is valid*/

        /*If it is a data instruction*/
        if (isDataLable(line + i + 1))
        {
            /*And it is a valid data instruction*/
            if (!errorInData(line + i + 1, inputFileName, lineNumber))
            {
                /*Update L to be the number of the operands in the data instruction*/
                L = numOfOperands(line + i + 1);/***********לא ממומש */

                /*Processing the data instruction and adding it to the memory*/
                processDataInstruction(line + i + 1, dataImage);/********לא ממומש */

                /*Adding the label to the symbols table*/
                createSymbol(*DC, SYMBOL_TYPE_DATA);

                /*Updating the DC counter*/
                *DC += L;
                L = 0;

                /*Adding the label to the symbols table*/
                appendNode(&symbolList, createNode(labelName ,label));
            }
        }

        /*If it is a code instruction*/
        else if (isCodeLable(line + i + 1))
        {   
            /*And it is a valid code instruction*/
            if (!errorInCode(line + i + 1, inputFileName, lineNumber))
            {
                /*Update L to be the number of the operands in the code instruction*/
                L = numOfMemWord(line + i + 1);/***********לא ממומש */

                /*Processing the code instruction and adding it to the memory*/
                processCodeInstruction(line + i + 1, &codeImage);/********לא ממומש */

                /*Adding the label to the symbols table*/
                createSymbol(*IC, SYMBOL_TYPE_CODE);

                /*Updating the IC counter*/
                *IC += L;
                L = 0;

                /*Adding the label to the symbols table*/
                appendNode(&symbolList, createNode(labelName ,label));
            }
        }

        /*If it is an extern instruction*/
        else if (isExternLable(line + i + 1))
        {
            /*And it is a valid extern instruction*/
            if (!errorInExtern(line + i + 1, inputFileName, lineNumber))
            {
                /*Creating a new symbol*/
                label = createSymbol(0, SYMBOL_TYPE_EXTERN);

                /*Adding the label to the extern list*/
                appendNode(&symbolList, createNode(labelName ,label));
            }   
        }

        /*If it is an entry instruction*/
        else if (isEntryLable(line + i + 1))
        {
            /*And it is a valid entry instruction*/
            if (!errorInEntry(line + i + 1, inputFileName, lineNumber))
            {
                /*Creating a new symbol*/
                label = createSymbol(0, SYMBOL_TYPE_ENTRY);

                /*Adding the label to the entry list*/
                appendNode(&symbolList, createNode(labelName ,label));
            }
            
        }

        /*If there is nothing after the label*/
        else if (i + 1 == strlen(line))
        {
            /*Label without a command after it*/
            fprintf(stderr, "Error: Label without a command after it in line %d file %s\n", lineNumber, inputFileName);
            error = true;
        }
            
        else
        {
            /*Error - invalid command after the label*/
            fprintf(stderr, "Error: Invalid command after the label in line %d file %s\n", lineNumber, inputFileName);
            return 1;
        }
        i++;
    }

    /*If there is no label in the line*/
    else
    {
        /*Checking if the command is valid*/

        /*If it is a data instruction*/

    }

    return 1;
}