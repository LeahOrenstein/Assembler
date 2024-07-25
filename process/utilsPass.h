#ifndef UTILSPASS_H
#define UTILSPASS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "errors.h"
#include "utils.h"
#include "tableStructure/list.h"

#define DATA_INSTRUCTIONS {".data", ".string"}
#define CODE_INSTRUCTIONS_NAMES {"mov", "cmp", "add", "sub", "lea", "clr", "not", "inc", "dec", "jmp", "bne", "red", "prn", "jsr", "rts", "stop"}
typedef enum {FALSE, TRUE} boolean;


int isDataLable(char* lable);

int isCodeLable(char* lable);

int isExternLable(char* lable);

int isEntryLable(char* lable);

int numOfOperands(char* line);

int processDataInstruction(char* line, ptrNode *dataImage);

int isAlphanumeric(const char *str);

int numOfMemWord(char* line);

int processCodeInstruction(char* line, ptrNode *codeImage);

#endif 