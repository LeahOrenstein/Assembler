#ifndef SYMBOLAPPEARANCE_H
#define SYMBOLAPPEARANCE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "definitions/definitions.h"


/*A structure for keeping the symbol appearance in the memory - words list for use in the second pass*/
typedef struct 
{
    int position;
}symbolAppearance;

typedef symbolAppearance *ptrSymbolAppearance;

ptrSymbolAppearance createSymbolAppearance(int position);

void freeSymbolAppearance(void* ptr);

void printSymbolAppearance(void* ptr);





#endif
