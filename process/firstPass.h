#ifndef FIRSTPASS_H
#define FIRSTPASS_H

#include <stdio.h>

#include "structures/symbol.h"
#include "structures/symbolAppearance.h"
#include "tableStructure/list.h"
#include "validationFunctions/errors.h"
#include "processingFunctions/processingLineFunct.h"
#include "utilsPass.h"
#include "utils.h"

#define MAX_LINE_LENGTH 81


/*Functions for the first pass*/

int firstPass(char* inputFileName, ptrNode* memoryImage, ptrNode* symbolListPtr, ptrNode* entryList);

int processLine(char* inputFileName, char* line, ptrNode* symbolListPtr, ptrNode entryList, ptrNode* codeImage, ptrNode* dataImage, ptrNode* symAppearMem, int* IC, int* DC, int lineNumber);




#endif