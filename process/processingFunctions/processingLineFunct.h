#ifndef PROCESSLINEFUNCT_H
#define PROCESSLINEFUNCT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utilsError.h"
#include "process/preassembler.h"
#include "tableStructure/list.h"
#include "utilsPass.h"
#include "utils.h"
#include "definitions/definitions.h"
#include "structures/memWord.h"
#include "structures/symbol.h"
#include "validationFunctions/errors.h"
#include "structures/symbolAppearance.h"


int processDataInstruction(char* line, ptrNode *dataImage, int* L);
int processCodeInstruction(char* line, ptrNode *codeImage, ptrNode symbolList, ptrNode* symbolMemApearance, int* L, int IC);
int processExternInstruction(char* line, ptrNode *symbolList);
int processEntryInstruction(char* line, ptrNode *entryList);
int processSrcMemWord(char* srcOp, char* dstOp, char srcMem[MEMORY_WORD_LENGTH], adressingMode srcAdMode, adressingMode dstAdMode, ptrNode symbolList, boolean twoRegisters);
int processDstMemWord(char* dstOp, char dstMem[MEMORY_WORD_LENGTH], adressingMode dstAdMode);

#endif