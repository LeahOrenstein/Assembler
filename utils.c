#include "utils.h"


/* Helper function to trim whitespace */
void trimWhitespace(char* str) 
{
    char* end;
    char* src;
    char* dst;

    /*Trim leading space*/ 
    src = str;
    while(isspace((unsigned char)*src)) src++;

    /* If all spaces, make it an empty string and return*/ 
    if(*src == 0)  
    {
        *str = '\0';
        return;
    }

    /*Trim trailing space*/ 
    end = src + strlen(src) - 1;
    while(end > src && isspace((unsigned char)*end)) end--;
    *(end+1) = 0;

    /*Shift the string to the beginning of the input*/ 
    dst = str;
    while(*src)
    {
        *dst++ = *src++;
    }
    *dst = '\0';
}


/*Function for initializing the file name vatiables*/
char* AllocateMemFileName(char* fileName, size_t size)
{
    /*Allocating memory for the variable*/
    char* string = malloc(sizeof(char)* size);
    if (string == NULL)
    {
        fprintf(stderr, "Error: can not allocate memory for a file name\n");
        exit(1);
    }   

    /*Updating the variable*/  
    strncpy(string, fileName, size);

    /*Returning*/
    return string;
}
