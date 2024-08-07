#ifndef SECONDPASS_H
#define SECONDPASS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tableStructure/list.h"
#include "definitions/definitions.h"
#include "structures/memWord.h"
#include "structures/symbol.h"
#include "process/validationFunctions/errors.h"
#include "process/utilsPass.h"
#include "process/processingFunctions/processingLineFunct.h"



/*Functions for the second pass process*/

int symbolPositionUpdate(ptrNode symbolList, int IC);  /*For each symbol, if data symbol - increase the position*/
int symbolValidation(char* inputFileName, ptrNode symbolList, ptrNode memAppearList, ptrNode entryList); /*Check if all symbols are valid defined in the file*/
int updateEnSymbolsAdress(ptrNode symbolList, ptrNode entryList); /*For each label, if it is in the entry list - update the symbol type*/
int createExFile(char* outputFileName, ptrNode symbolList, ptrNode symbolAppearance); /*Create the .ext file*/
int createEnFile(char* outputFileName, ptrNode symbolList, ptrNode entryList); /*Create the .ent file*/
int createObFile(char* outputFileName, ptrNode memoryImage, int IC, int DC); /*Create the .ob file*/
int secondPass(char* inputFileName, ptrNode memoryImage, ptrNode symbolList, ptrNode enteryList, ptrNode symAppearMem);



#endif