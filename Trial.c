#include "tableStructure/list.h"
#include "structures/command.h"
#include "structures/macro.h"
#include "structures/memWord.h"
#include "process/preassembler.h"
#include "process/firstPass.h"
#include "testing.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {inputFileName, baseName, amFile, obFile, entFile, extFile};



/*Notes:
שם הקובץ צריך להיעבר כפרמטר בלי סיומת*/

int main(int argc, char *argv[]) 
{

    int i, j;

    int suffix[] = {3, 0, 3, 3, 4, 4};

    char* fileNames[6];

    ptrNode symbolList = NULL;

    ptrNode memoryImage = NULL;

    char* fileNamesForPrinting[] = {"inputFileName", "baseName", "amFile", "obFile", "entFile", "extFile"};

    


    printf("checking validation of label: %d\n", errorInLabel("22abelvvvv vvvvv:vvs", "file name", 1));

    if (argc < 2) 
    {
        fprintf(stderr, "Usage: %s <file1.as> <file2.as> ...\n", argv[0]);
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
            fprintf(stderr, "Error in pre-assembler stage for file %s\n", inputFileName);
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
    

