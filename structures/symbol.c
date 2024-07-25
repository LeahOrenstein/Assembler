#include "symbol.h"


/*Creating a symbol from the given values*/
ptrSymbol createSymbol(int position, symbolType type)
{
    /*Initializing the values*/
    ptrSymbol ptr = malloc(sizeof(symbol));
    if (ptr == NULL)
    {
        fprintf(stderr, "Error: can not allocate memory for a new symbol\n");
        exit(1);
    }

    /*Updating relevant values*/
    ptr->position = position;
    ptr->type = type;

    return ptr;
}

/*Function to free a symbol*/
void freeSymbol(void* ptr)
{   
    free((ptrSymbol)ptr);
}