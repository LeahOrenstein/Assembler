#include "errors.h"


/*Functions for handling with errors*/

/*Checks a data command. returns true if there is any error in it*/
int errorInData(char* line, char* inputFileName, int lineNumber)
{
    int error = false;
    char tempLine[MAX_LINE_LENGTH] = {0};

    /*Checks the data command type*/
    dataType type = retDataType(line);
    
    /*If the command name is not valid*/
    if (type == ERROR_DATA)
    {
        fprintf(stderr, "Error: Invalid data command. file: %s, line: %d\n", inputFileName, lineNumber);
        return true;
    }

    /*Skip the command*/
    line += type == DATA ? DATA_LENGTH : STRING_LENGTH;

    /*Normalizing the format of the line with trime and format string (Skipping uneeded white space and adding ' ' after each comma)*/
    trimAndFormatString(line, tempLine);
    line = tempLine;

    /*If the line is empty*/
    if (strlen(line) == 0)
    {
        fprintf(stderr, "Error: Empty data line. file: %s, line: %d\n", inputFileName, lineNumber);
        return true;
    }

    /*If there is a comma at the end of the line*/
    if (line[strlen(line) - 1] == ',')
    {
        fprintf(stderr, "Error: Comma at the end of the line. file: %s, line: %d\n", inputFileName, lineNumber);
        error = true;
    }

    /*If there is a comma at the beginning of the line*/
    if (line[0] == ',')
    {
        fprintf(stderr, "Error: Illegal comma. file: %s, line: %d\n", inputFileName, lineNumber);
        error = true;
    }

    /*If the string is not in the correct format*/
    if (type == STRING)
    {
        if (!isValidQuotedString(line))
        {
            fprintf(stderr, "Error: Invalid string format. file: %s, line: %d\n", inputFileName, lineNumber);
            return true;
        }
        return false;
    }

    /*If there are two commas in a row*/
    if (multipleCommas(line))
    {
        fprintf(stderr, "Error: Multiple commas. file: %s, line: %d\n", inputFileName, lineNumber);
        error = true;
    }

    /*If the operands are not separated by a comma*/
    if (hasAdjacentItemsWithoutComma(line))
    {
        fprintf(stderr, "Error: Adjacent items without comma. file: %s, line: %d\n", inputFileName, lineNumber);
        error = true;
    }

    /*If the operands are not the valid type*/
    if (!operandsAreIntegers(line))
    {
        fprintf(stderr, "Error: Invalid operand type. file: %s, line: %d\n", inputFileName, lineNumber);
        return true;
    }

    /*If the operands are not in valid range*/
    if (!operandsAreInRange(line))
    {
        fprintf(stderr, "Error: Operand out of range. file: %s, line: %d\n", inputFileName, lineNumber);
        error = true;
    }

    return error;
}

/*Checks a code command. returns true if there is any error in it*/
int errorInCode(char* line, char* inputFileName, int lineNumber)
{
    /*Declaring variables*/
    char tempLine[MAX_LINE_LENGTH] = {0};
    codeType type;
    const char* codeInstructions [] = CODE_INSTRUCTIONS_NAMES;
    const int numOfOperandsForCom[] = NUM_OF_OPERANDS_REQUIRED;
    int i;

    /*Variables to store the current operand checked*/
    char* operand, *endOfOperand; 
    char tempOperand[MAX_LABEL_LENGTH + 1] = {0}; /*The operand must not be longer than that*/

    /*Checks the code command type*/
    type = checkCodeType(line);

    /*If the command name is not valid*/
    if (type == ERROR_CODE)
    {
        fprintf(stderr, "Error: Invalid code command. file: %s, line: %d\n", inputFileName, lineNumber);
        return true;
    }

    /*Skip the command*/
    line += strlen(codeInstructions[type]);

    /*Normalizing the format of the line with trime and format string (Skipping uneeded white space and adding ' ' after each comma)*/
    trimAndFormatString(line, tempLine);
    line = tempLine;

    operand = line;

    /*If the line is empty*/
    if (strlen(line) == 0)
    {
        /*If the line should be empty - No errors*/
        if (type == rts || type == stop)
        {
            return false;
        }

        /*Else - Error: Missing parameters*/
        fprintf(stderr, "Error: Missing operand in code line. file: %s, line: %d\n", inputFileName, lineNumber);
        return true;
    }

    /*If the command has arguememts but it mist not have*/
    if (type == rts || type == stop)
    {
        fprintf(stderr, "Error: Command with no operands needed has operands. file: %s, line: %d\n", inputFileName, lineNumber);
        return true;
    }

    /*If there is a comma at the end of the line*/
    if (line[strlen(line) - 1] == ',')
    {
        fprintf(stderr, "Error: Comma at the end of the line. file: %s, line: %d\n", inputFileName, lineNumber);
        return true;
    }

    /*If there is a comma at the beginning of the line*/
    if (line[0] == ',')
    {
        fprintf(stderr, "Error: Illegal comma line. file: %s, line: %d\n", inputFileName, lineNumber);
        return true;
    }

    /*If there are two commas in a row*/
    if (multipleCommas(line))
    {
        fprintf(stderr, "Error: Multiple commas. file: %s, line: %d\n", inputFileName, lineNumber);
        return true;
    }

    /*If the operands are not separated by a comma*/
    if (hasAdjacentItemsWithoutComma(line))
    {
        fprintf(stderr, "Error: Adjacent items without comma. file: %s, line: %d\n", inputFileName, lineNumber);
        return true;
    }

    /*If the operands are not the valid type. For each operand - checks validation*/
    for (i = 0; i < numOfOperandsForCom[type]; i++)
    {
        if (*operand == ',') operand++;

        operand = getOperand(operand, &endOfOperand);

        /*If there is no operrand, an operand is missing*/
        if (*operand == '\0' || *operand == EOF ) 
        {
            fprintf(stderr, "Error: Missing operand in code line. file: %s, line: %d\n", inputFileName, lineNumber);
            return true;
        }

        /*If the operand found is too long (no valid type possible)*/
        if (endOfOperand - operand > MAX_LABEL_LENGTH)
        {
            fprintf(stderr, "Error: Invalid operand. file: %s, line: %d\n", inputFileName, lineNumber);
            return true;
        }

        /*Copy the operand to the temp operand without the rest of the line*/
        strncpy(tempOperand, operand, endOfOperand - operand);
        operand = tempOperand;

        /*Check validation of the operand*/
        if (!isValidOperand(operand, inputFileName, lineNumber))
        {
            return true;
        }
        
        operand = endOfOperand;
    }

    /*If there are extra chars after the legal command*/
    if (*operand != '\0' && *operand != EOF)
    {
        fprintf(stderr, "Error: Extra chars after the legal command. file: %s, line: %d\n", inputFileName, lineNumber);
        return true;
    }
    

    /*If the operands are not the valid adressing mode*/
    if (!validAdressingModes(line, type))
    {
        fprintf(stderr, "Error: Invalid adressing mode. file: %s, line: %d\n", inputFileName, lineNumber);
        return true;
    }

    return false;
}

/*Checks a label. returns true if there is any error in it*/
int errorInLabel(char* label, char* inputFileName, int lineNumber, ptrNode symbolList)
{
    int error = false;

    /*If label is empty*/
    if (strlen(label) == 0)
    {
        fprintf(stderr, "Error: Empty label. file: %s, line: %d\n", inputFileName, lineNumber);
        free(label);
        return true;
    }

    /*If label name is used already*/
    if (searchKey(symbolList, label))
    {
        fprintf(stderr, "Error: Label name is already used. Error is. file: %s, line: %d\n", inputFileName, lineNumber);
        free(label);
        return true;
    }

    /*If label is too long*/
    if (strlen(label) > MAX_LABEL_LENGTH)
    {
        fprintf(stderr, "Error: Label is too long. file: %s, line: %d\n", inputFileName, lineNumber);
        error = true;
    }

    /*If label does not start with a letter*/
    if (!isalpha(label[0]))
    {
        fprintf(stderr, "Error: Label does not start with a letter. file: %s, line: %d\n", inputFileName, lineNumber);
        error = true;
    }

    /*If label ends with white space*/
    if (label[strlen(label) - 1] == ' ' || label[strlen(label) - 1] == '\t')
    {
        fprintf(stderr, "Error: Label ends with white space. file: %s, line: %d\n", inputFileName, lineNumber);
        return true;
    }

    /*If not all charecters are letters / numbers*/
    if (!isAlphanumeric(label))
    {
        fprintf(stderr, "Error: Label contains non-alphanumeric charecters. file: %s, line: %d\n", inputFileName, lineNumber);
        error = true;
    }

    return error;
}


/*Checks an extern command. returns true if there is any error in it*/
int errorInExEn(char* line, char* inputFileName, int lineNumber)
{
    char tempLine[MAX_LINE_LENGTH] = {0};
    char* endOfOperand;
    int commandTypeLength[] = LENGTH_OF_EX_EN;
    char* exEnCommands[] = EXTERN_ENTRY_COMMANDS;
    int type;

    /*Normalizing the format of the line with trime and format string (Skipping uneeded white space and adding ' ' after each comma)*/
    trimAndFormatString(line, tempLine);
    line = tempLine;
    type = retExEnType(line);

    if (*line != '.' || type == ERROR_EXTERN_ENTRY)
    {
        fprintf(stderr, "Error: Invalid command. file: %s, line: %d\n", inputFileName, lineNumber);
        return true;
    }

    /*Skip the command*/
    line += commandTypeLength[type];

    /*If there is an ilegal comma in the line*/
    if (line[strlen(line) - 1] == ',' || line[0] == ',')
    {
        fprintf(stderr, "Error: Illegal comma. file: %s, line: %d\n", inputFileName, lineNumber);
        return true;
    }

    /*Skipping white spaces*/
    while (isspace((unsigned char)*line)) line++;

    /*If the operand is too long*/
    if (strlen(line) > MAX_LABEL_LENGTH)
    {
        fprintf(stderr, "Error: Operand is an invalid label. file: %s, line: %d\n", inputFileName, lineNumber);
        return true;
    }

    /*If the operand is empty*/
    if (strlen(line) == 0)
    {
        fprintf(stderr, "Error: Empty operand. file: %s, line: %d\n", inputFileName, lineNumber);
        return true;
    }

    getOperand(line, &endOfOperand);

    /*If there are extra charecters after the end of the line operands*/
    if( *endOfOperand != '\0' && *endOfOperand != EOF)
    {
        fprintf(stderr, "Error: Extra charecters or invalid number of operands. file: %s,  line: %d\n", inputFileName, lineNumber);
        return true;
    }

    /*If the operand is not a valid label*/
    if (errorInLabelAsOperand(line))
    {
        fprintf(stderr, "Error: Operand is an invalid label in an %s command. file: %s, line: %d\n", exEnCommands[type],inputFileName, lineNumber);
        return true;
    }

    return false;
}





