#ifndef ERRORS_H
#define ERRORS_H

#include <stdio.h>

#include "utilsError.h"
#include "process/preassembler.h"
#include "tableStructure/list.h"
#include "utilsPass.h"
#include "definitions/definitions.h"

/*Main error functions, prototypes*/
int errorInData(char* line, char* inputFileName, int lineNumber);
int errorInCode(char* line, char* inputFileName, int lineNumber);
int errorInLabel(char* label, char* inputFileName, int lineNumber, ptrNode symbolList);
int errorInExEn(char* line, char* inputFileName, int lineNumber);

#endif 