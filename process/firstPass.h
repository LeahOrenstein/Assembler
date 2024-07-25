#ifndef FIRSTPASS_H
#define FIRSTPASS_H

#include <stdio.h>

#include "structures/symbol.h"
#include "tableStructure/list.h"
#include "errors.h"
#include "utilsPass.h"
#include "utils.h"

#define MAX_LINE_LENGTH 81


/*Functions for the first pass*/

int firstPass(const char* inputFileName, ptrNode* memoryImage, ptrNode* symbolListPtr);

int processLine(FILE* inputFile, char* inputFileName, char* line, ptrNode* symbolListPtr, ptrNode* codeImage, ptrNode* dataImage, int* IC, int* DC, int lineNumber);





#endif