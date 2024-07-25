#ifndef MEMORYWORD_H
#define MEMORYWORD_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MEMORY_WORD_LENGTH 15


/*Definig a structure for a word in the memory, in order to keep it after the first pass*/
typedef struct 
{
    char value[MEMORY_WORD_LENGTH + 1];
}memWord;

/*Defining a pointer to a meory word structure*/
typedef memWord* ptrMemWord;

ptrMemWord createMemWord(char value[]);

void freeMemWord(void* ptr);


#endif