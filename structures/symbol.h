#ifndef SYMBOL_H
#define SYMBOL_H

#include "process/preassembler.h"

#include <string.h>

typedef enum {
    SYMBOL_TYPE_CODE,
    SYMBOL_TYPE_DATA,
    SYMBOL_TYPE_ENTRY,
    SYMBOL_TYPE_EXTERN,
    SYMBOL_TYPE_BEFORE_EX_EN
} symbolType;

/*Defining the symbol structure*/
typedef struct 
{
    int position;
    symbolType type;
}symbol;

/*Defining a pointer to the symbol structure*/
typedef symbol *ptrSymbol;

ptrSymbol createSymbol(int position, symbolType type);

void printSymbol(void* symbol);

void freeSymbol(void *ptr);






#endif