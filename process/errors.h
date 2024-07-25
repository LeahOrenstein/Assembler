#ifndef ERRORS_H
#define ERRORS_H

#include <stdio.h>

#include "process/preassembler.h"
#include "utilsPass.h"

/*Error functions*/
int errorInData(char* line, char* inputFileName, int lineNumber);

int errorInCode(char* line, char* inputFileName, int lineNumber);

int errorInLabel(char* label, char* inputFileName, int lineNumber);

int errorInExtern(char* label, char* inputFileName, int lineNumber);

int errorInEntry(char* label, char* inputFileName, int lineNumber);

#endif 