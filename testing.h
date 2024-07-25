#ifndef TESTING_H
#define TESTING_H

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "process\preassembler.h"


/*File for testing the outputs*/

int compareFiles(const char* file1, const char* file2);
void printDifferences(const char* file1, const char* file2);


#endif