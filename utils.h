#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 81

/*Helper functions*/

void trimWhitespace(const char* str, char* result, size_t result_size);

char* AllocateMemFileName(const char* fileName, size_t size);

char* skipWhitespace(char* str);

void trimAndFormatString(const char *input, char output[MAX_LINE_LENGTH]);


#endif