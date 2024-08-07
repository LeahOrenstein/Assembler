#include "symbolAppearance.h"


ptrSymbolAppearance createSymbolAppearance(int position)
{
    ptrSymbolAppearance newSymbolAppearance = (ptrSymbolAppearance)malloc(sizeof(symbolAppearance));
    if (newSymbolAppearance == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    newSymbolAppearance->position = position;
    return newSymbolAppearance;
}

void freeSymbolAppearance(void* ptr)
{
    free((ptrSymbolAppearance)ptr);
}

void printSymbolAppearance(void* ptr)
{
    printf("position: %d\n", ((ptrSymbolAppearance)ptr)->position);
}





