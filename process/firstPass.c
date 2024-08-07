#include "firstPass.h"

/* Function for managing the first pass */
int firstPass(char* inputFileName, ptrNode* memoryImage, ptrNode* symbolListPtr, ptrNode* entryList)
{
    /*Declaring variables*/

    /*Counters*/
    int IC = 100;
    int DC = 0;
    int lineNumber = 0;

    /*Flags*/
    int error = false;
    int isErrorInLine = false;

    char line[MAX_LINE_LENGTH];

    /*Lists*/
    ptrNode symbolList = NULL;
    ptrNode symAppearMem = NULL;
    ptrNode dataImage = NULL;
    ptrNode codeImage = NULL;

    /* Opening the am file*/
    FILE* inputFile = fopen(inputFileName, "r");
    if (inputFile == NULL)
    {
        fprintf(stderr, "Error: Could not open file %s\n", inputFileName);
        return false;
    }

    /*Reading the file line by line and processing it*/
    while (fgets(line, MAX_LINE_LENGTH, inputFile) != NULL)
    {
        lineNumber++;
        isErrorInLine = processLine(inputFileName, line, &symbolList, &entryList, &codeImage, &dataImage, &symAppearMem, &IC, &DC, lineNumber);
        /*If an error found in the line*/
        if (!isErrorInLine)
        {
            error = true;
        }
    }

    /*Close file*/
    fclose(inputFile);
    /*Free allocated memory!!*/

    return error? false : true;

}


int processLine(char* inputFileName, char* line, ptrNode* symbolListPtr, ptrNode entryList, ptrNode* codeImage, ptrNode* dataImage, ptrNode* symAppearMem, int* IC, int* DC, int lineNumber)
{
    /*Declaring variables*/
    char labelName[MAX_LABEL_LENGTH] = {0};
    char labelNameTemp[MAX_LINE_LENGTH] = {0};
    char tempLine[MAX_LINE_LENGTH] = {0};
    int error = false;
    int labelFound = false;
    int L = 0;
    int i = 0;

    /*Checking if it is a note line*/
    if (line[0] == ';')
    {
        /*If it is a note line - skip it*/
        return 1;
    }

    /* Clearing the line from extra white spaces in the end and begining, using the temporary line */
    trimWhitespace(line, tempLine, MAX_LINE_LENGTH);  
    line = tempLine;

    /*Look for a label declaration*/
    while (i < strlen(line) && line[i] != ':')  i++; 
    
    if (line[i] == ':')
    {
        /*Label found, updates the labels flag and checks if valid and if so adding it to the symbols table*/
        labelFound = true;

        /*Checking if the label name is valid*/

        /*Clearing only the begining of the label name from white spaces*/
        sprintf(labelNameTemp,"%.*s\0", i + 1, line);
        trimWhitespace(labelNameTemp, labelNameTemp, MAX_LINE_LENGTH);
        sprintf(labelNameTemp,"%.*s\0", strlen(labelNameTemp) - 1, labelNameTemp);

        if (errorInLabel(labelNameTemp , inputFileName, lineNumber, *symbolListPtr))
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
            if (!errorInData(line + i + 1, inputFileName, lineNumber) && !error)
            {
                /*Adding the label to the symbols table*/
                appendNode(symbolListPtr, createNode(labelName ,createSymbol(*DC, SYMBOL_TYPE_DATA)));
            }
            else
                error = true;
        }

        /*If it is a code instruction*/
        else if (isCodeLable(line + i + 1))
        {   
            /*And it is a valid code instruction*/
            if (!errorInCode(line + i + 1, inputFileName, lineNumber) && !error)
            {
                /*Adding the label to the symbols table*/
                appendNode(symbolListPtr, createNode(labelName ,createSymbol(*IC, SYMBOL_TYPE_CODE)));
            }
            else
                error = true;
        }

        /*If it is an extern instruction*/
        else if (isExternLable(line + i + 1))
        {
            /*And it is a valid extern instruction*/
            if (errorInExEn(line + i + 1, inputFileName, lineNumber) && !error)
            {
                /*Adding the label to the extern list*/
                appendNode(symbolListPtr, createNode(labelName ,createSymbol(0, SYMBOL_TYPE_BEFORE_EX_EN)));
            } 
            else
                error = true;  
        }

        /*If it is an entry instruction*/
        else if (isEntryLable(line + i + 1))
        {
            /*And it is a valid entry instruction*/
            if (!errorInExEn(line + i + 1, inputFileName, lineNumber) && !error)
            {
                /*Adding the label to the entry list*/
                appendNode(symbolListPtr, createNode(labelName ,createSymbol(0, SYMBOL_TYPE_BEFORE_EX_EN)));
            }
            else
                error = true;
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
            return false;
        }
        i++;
    }

    if (error)
    {
        /******************Debug */
        printf("Error in line\n");
        return false;
    }

    /*If there is no label in the line*/
    if (!labelFound)
        i = 0;
    
    line += i;
    line = skipWhitespace(line);

    if (isDataLable(line))
    {
        /*If it is a valid data instruction*/
        if (!errorInData(line, inputFileName, lineNumber))
        {
            /*Processing the data instruction and adding it to the memory*/
            processDataInstruction(line, dataImage, &L);
            *DC += L;  /*Updating the DC*/
        }
    }

    else if (isCodeLable(line))
    {
        /*If it is a valid code instruction*/
        if (!errorInCode(line, inputFileName, lineNumber))
        {
            /*Processing the code instruction and adding it to the memory*/
            processCodeInstruction(line, codeImage, *symbolListPtr, symAppearMem, &L, *IC);

            /*Updating the IC*/
            *IC += L;
            L = 0;
        }
    }

    else if (isExternLable(line))
    {
        /*If it is a valid extern instruction*/
        if (!errorInExEn(line, inputFileName, lineNumber))
        {
            if(!processExternInstruction(line, symbolListPtr))   error = true;  /*Process the extern line*/
        }   
    }

    else if (isEntryLable(line))
    {
        /*If it is a valid entry instruction*/
        if (!errorInExEn(line, inputFileName, lineNumber))
        {
            if(!processEntryInstruction(line, entryList))   error = true;  /*Process the entry line*/
        }
    }

    /*If it is not a code, data, extern or entry command*/
    else
    {
        /*Error - invalid instruction*/
        fprintf(stderr, "Error: Instruction is not valid in line %d file %s\n", lineNumber, inputFileName);
        error = true;
    }

    return error? false : true;
}

