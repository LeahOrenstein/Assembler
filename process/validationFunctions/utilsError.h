#ifndef UTILSERROR_H
#define UTILSERROR_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

#include "utils.h"
#include "definitions/definitions.h"
#include "utilsPass.h"

/*Prototype functions*/
int hasAdjacentItemsWithoutComma(char* str);
int operandsAreIntegers(char* line);
int operandsAreInRange(char* line);
int isValidQuotedString(char* str);
int isValidInteger(char* str);
int isNumberInRange(char* str);
codeType checkCodeType(char* line);
adressingMode checkAdressingMode(char* line);
int multipleCommas(char* line);
int isRegister(char* str);
int validAdressingModes(char* line, codeType type);
int isValidOperand(char* operand, char* inputFileName, int lineNumber);
int isRegisterOutOfRange(char* str);
int isImmediateOutOfRange(char* str);
int errorInLabelAsOperand(char* line);

#endif 