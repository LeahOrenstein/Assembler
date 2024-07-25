#ifndef PREASSEMBLER_H
#define PREASSEMBLER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "structures/macro.h"
#include "structures/command.h"
#include "tableStructure/list.h"
#include "utils.h"

enum {false, true};

#define MAX_LINE_LENGTH 81
#define MAX_LABEL_LENGTH 31

/* Function prototypes */
int processMacroDefinitions(FILE* inputFile, FILE* outputFile, ptrNode *ptrMacroList, const char* inputFileName);
int expandMacros(FILE* inputFile, FILE* outputFile, ptrNode macroList);
int preprocessFile(const char* inputFileName, const char* outputFileName);

#endif