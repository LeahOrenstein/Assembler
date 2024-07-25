#ifndef MACRO_H
#define MACRO_H

#include <stdio.h>

#include "tableStructure/list.h"
#include "command.h"


/*Definition of the macro structure*/
typedef struct 
{
    /*pointer to the macro's command's list*/
    ptrNode commandList;
}macro;

/*Pointer to a macro*/
typedef macro*  ptrMacro;

/* Function prototypes */
void printMacroCommands(void* ptr);
void freeMacro(void* ptr);


#endif