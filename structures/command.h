#ifndef COMMAND_H
#define COMMAND_H

#include <stdio.h>
#include <stdlib.h>


/*Definition of the command structure*/
typedef struct
{
    char comLine [80];
}command;

/*Poiter to a command*/
typedef command* ptrCommand;

/* Function prototypes */
void printCommand(void* ptr);
void freeCommand(void* ptr);






#endif