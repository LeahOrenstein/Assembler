#ifndef UTILSPASS_H
#define UTILSPASS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "tableStructure/list.h"
#include "definitions/definitions.h"
#include "validationFunctions/utilsError.h"


int isDataLable(char* lable);
int isCodeLable(char* lable);
int isExternLable(char* lable);
int isEntryLable(char* lable);
int numOfOperands(char* line);
int isAlphanumeric(const char *str);
int numOfMemWord(char* line);
char* getOperand(char* line, char** endOfOperand);
externEntryType retExEnType(const char* line);
int isImmediate(char* str);
int isDirect(char* str);
int isDirectRegister(char* str);
int isInDirectRegister(char* str);
dataType retDataType(char* line);
codeType retCodeType(char* line);
void intToBinaryString(int num, char* result, int length);
char* getOpCode(codeType codeType);


#endif 