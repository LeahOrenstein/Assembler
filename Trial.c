#include "tableStructure/list.h"
#include "structures/command.h"
#include "structures/macro.h"
#include "structures/memWord.h"
#include "process/preassembler.h"
#include "process/firstPass.h"
#include "testing.h"
#include "definitions/definitions.h"
#include "process/processingFunctions/processingLineFunct.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {inputFileName, baseName, amFile, obFile, entFile, extFile};


/*Notes:
שם הקובץ צריך להיעבר כפרמטר בלי סיומת*/

int main(int argc, char *argv[]) 
{

    int i, j;

    int L = 0;

    int DC = 0;

    int IC = 100;

    int suffix[] = {3, 0, 3, 3, 4, 4};

    char* fileNames[6];

    ptrNode memoryImage = NULL;

    ptrNode symbolList = NULL;

    ptrNode codeImage = NULL;

    ptrNode dataImage = NULL;

    ptrNode symAppearMem = NULL;

    
    char line[MAX_LINE_LENGTH] = {0};

    char* fileNamesForPrinting[] = {"inputFileName", "baseName", "amFile", "obFile", "entFile", "extFile"};

    strncpy(line, " END: stop", MAX_LINE_LENGTH);

    printf("In trial. line: %s\n", line);

    /*MAX_VALUE 16383*/
    
    printf("checking validation of processLine: %d\n", processLine("file1",  line,  &symbolList, &codeImage, &dataImage, &symAppearMem, &IC, &DC, L));

    printListStructure(codeImage);
    printListStructureAndVal(symbolList, printSymbol);
    printListStructureAndVal(symAppearMem, printSymbolAppearance);

    printf("IC: %d\n", IC);
    printf("DC: %d\n", DC);


    if (argc < 2) 
    {
        fprintf(stderr, "Usage: %s <file1> <file2> ...\n", argv[0]);
        exit(1);
    }

    for (i = 1; i < argc; i++) 
    {

        /*Allocating memory and initializing the file names variables*/
        for (j = 0; j < 6; j++)
        {
            fileNames[j] = AllocateMemFileName(argv[i], strlen(argv[i]) + suffix[j]);
        }

        /*Generate output file names*/
        sprintf(fileNames[inputFileName], "%s.as\0", fileNames[baseName]);
        sprintf(fileNames[amFile], "%s.am\0", fileNames[baseName]);
        sprintf(fileNames [obFile], "%s.ob\0", fileNames [baseName]);
        sprintf(fileNames [entFile], "%s.ent\0", fileNames[baseName]);
        sprintf(fileNames [extFile], "%s.ext\0", fileNames[baseName]);

        for (j = 0; j < 6; j++)
        {
            printf("%s that accepted: %s\n", fileNamesForPrinting[j], fileNames[j]);
        }

        /* Step 1: Pre-assembler (macro expansion)*/
        if (!preprocessFile(fileNames [inputFileName], fileNames [amFile])) 
        {
            fprintf(stderr, "Error in pre-processor stage for file %s\n", inputFileName);
            continue;
        }

        printf("Assembly of %s completed successfully.\n", fileNames [inputFileName]);
        /* Step 2: First pass */
        if (!firstPass(fileNames[amFile], &memoryImage, &symbolList)) 
        {
            fprintf(stderr, "Error in first pass for file %s\n", fileNames[inputFileName]);
            continue;
        }

        /*3rd pass*/

        /* Free allocated memory */
        freeList(&symbolList, freeSymbol);
        for (j = 0; j < 6; j++) 
        {
            free(fileNames[j]);
        }

    }

    return 0;
}
    

