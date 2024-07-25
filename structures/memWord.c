#include "memWord.h"


/*Function for creating a memory word, gets a string that represents the word in binary*/
ptrMemWord createMemWord(char value[])
{
    /*Initializing a memory word struct*/
    ptrMemWord ptr = malloc(sizeof(memWord));
    if (ptr == NULL)
    {
        fprintf(stderr, "Memory allocation failed for memory word structure\n");
        exit(1);
    }

    /*Updating the value*/
    strncpy(ptr->value, value, MEMORY_WORD_LENGTH + 1);
    ptr->value[MEMORY_WORD_LENGTH] = '\0';

    return ptr;
}


/*Function for freeing a memory word structure*/
void freeMemWord(void* ptr)
{
    free((ptrMemWord)ptr);
}
