#include "secondPass.h"


/*For each symbol, if data symbol - increase the position*/
int symbolPositionUpdate(ptrNode symbolList, int IC)
{
    ptrSymbol symbol = NULL;

    /*For each data symbol, updates the location with the final IC*/
    while (symbolList != NULL)
    {
        symbol = (ptrSymbol)(symbolList->ptrVal);

        if (symbol->type == DATA)  /*Data symbol found*/
        {
            symbol->position += IC;
        }

        symbolList = symbolList->next;
    }

    /*Success*/
    return true;
}

/*For each entry symbol, updates the adress according to its value in the symbolList*/
int updateEnSymbolsAdress(ptrNode symbolList, ptrNode entryList)
{
    ptrSymbol symbol = NULL;
    ptrNode tempNode = NULL;

    while (entryList != NULL)
    {
        tempNode = searchKey(symbolList, entryList->key);

        if (tempNode == NULL)  /*If the symbol is defined in the symbol list*/
        {
            return false;
        }

        symbol = (ptrSymbol)(tempNode->ptrVal);
        symbol->type = ENTRY;
        entryList->ptrVal = symbol; /*Update the entry list with the symbol and its adress*/

        entryList = entryList->next;
    }

    /*Success*/
    return true;
}

/*Create the .ext file*/
int createExFile(char* outputFileName, ptrNode symbolList, ptrNode symbolAppearance)
{
    FILE* externFile = NULL;
    ptrSymbol symbol = NULL;

    /*Open the extern file for writing*/
    externFile = fopen(outputFileName, "w");
    if (externFile == NULL)
    {
        fprintf(stderr, "Error: could not create extern file. file: %s\n", outputFileName);
        return false;
    }
    
    while (symbolList != NULL)
    {
        symbol = (ptrSymbol)(symbolList->ptrVal);
        if (symbol->type == EXTERN)  /*If the symbol is external*/
        {
            fprintf(externFile, "%s %04d\n", symbolList->key, symbol->position);
        }

        symbolList = symbolList->next;
    }

    /*Close the file*/
    fclose(externFile);

    /*Success*/
    return true;
}

/*Create the .ent file*/
int createEnFile(char* outputFileName, ptrNode symbolList, ptrNode entryList)
{
    FILE* entryFile = NULL;
    
    /*Open the entry file for writing*/
    entryFile = fopen(outputFileName, "w");
    if (entryFile == NULL)
    {
        fprintf(stderr, "Error: could not create entry file. file: %s\n", outputFileName);
        return false;
    }

    /*For each entry symbol - prints it and its adress to the .ent file*/
    while (entryList != NULL)
    {
        fprintf(entryFile, "%s %04d\n", entryList->key, ((ptrSymbol)(entryList->ptrVal))->position);
        entryList = entryList->next;
    }

    /*Close the file*/
    fclose(entryFile);

    /*Success*/
    return true;
}

/*Create the .ob file*/
int createObFile(char* outputFileName, ptrNode memoryImage, int IC, int DC)
{
    FILE* obFile = NULL;
    int i;
    long int decimalMemoryWord;
    
    /*Open the ob file for writing*/
    obFile = fopen(outputFileName, "w");
    if (obFile == NULL)
    {
        fprintf(stderr, "Error: could not create ob file. file: %s\n", outputFileName);
        return false;
    }

    /*Prints the IC & DC counters*/
    fprintf(obFile, "%d %d\n", IC - 100, DC);

    /*For each memory word - prints it to the .ob file with the adress*/
    for (i = 100; i < IC + DC; i++)
    {
        decimalMemoryWord = strtol(memoryImage->key, NULL, 2);
        fprint(obFile, "%04d %05o", i, (unsigned int)decimalMemoryWord);

        memoryImage = memoryImage->next;
    }

    /*Close the file*/
    fclose(obFile);

    /*Success*/
    return true;
}

/*Checks the validation of the ex - en symbols and the symbols apearanse*/







































































































int symbolPositionUpdate(ptrNode symbolList, int IC)
{
    ptrNode tempNode = symbolList;
    ptrSymbol symbol;

    /*For each data pointer symbol in the symbol list - increase its position in DC*/
    while (tempNode != NULL)
    {
        symbol = (ptrSymbol)(tempNode->ptrVal);
        if (symbol -> type == DATA)   /*If it is a data pointer symbol*/
        {
            symbol->position += IC;
        }

        tempNode = tempNode->next;
    }
    return true;
}


int symbolValidation(char* inputFileName, ptrNode symbolList, ptrNode memAppearList, ptrNode externList, ptrNode entryList)
{
    ptrNode tempNode = NULL;
    ptrNode externListTemp = NULL;
    boolean error = false;

    /*For each node of the extern list - checkes if not defined in the current file*/
    while (externList != NULL)
    {
        tempNode = searchKey(symbolList, externList->key);
        if (tempNode != NULL)   /*If the symbol is defined in the file*/
        {
            fprintf(stderr, "Error: symbol %s is defined in the file. file: %s\n", externList->key, inputFileName); /*Add a line number*/
            error = true;
        }

        externList = externList->next;
    }

    /*For each node of the entry list - checkes if defined in the current file*/
    while (entryList != NULL)
    {
        tempNode = searchKey(symbolList, entryList->key);
        if (tempNode == NULL)   /*If the symbol is not defined in the file*/
        {
            fprintf(stderr, "Error: entry symbol %s is not defined in the file. file: %s\n", entryList->key, inputFileName); /*Add a line number*/
            error = true;
        }

        entryList = entryList->next;
    }
    
    /*For each node of the symbol appearance list - checkes if defined in the file (or external)*/
    while (memAppearList != NULL)   
    {
        tempNode = searchKey(symbolList, memAppearList->key);
        externListTemp = searchKey(externList, memAppearList->key);
        
        if (tempNode == NULL && externListTemp == NULL)   /*If the symbol is not defined in the file or external*/
        {
            fprintf(stderr, "Error: symbol %s is not defined. file: %s\n", memAppearList->key, inputFileName); /*Add a line number*/
            error = true;
        }

        memAppearList = memAppearList->next;
    }

    return error? false : true;
}


int createExternFile(char* inputFileName, char* outputFileName, ptrNode symAppearMem, ptrNode externList)
{
    FILE* externFile = NULL;
    ptrNode tempNode = NULL;
    ptrSymbol symbol = NULL;
    char* externFileName = NULL;

    /*Open the extern file for writing*/
    externFile = fopen(outputFileName, "w");
    if (externFile == NULL)
    {
        fprintf(stderr, "Error: could not open extern file. file: %s\n", inputFileName);
        return false;
    }

    /*For each external node of the symbol appearance list - write the symbol and its position to the extern file*/
    while (symAppearMem != NULL)
    {
        tempNode = searchKey(externList, symAppearMem->key);
        if (tempNode != NULL)   /*If the symbol is defined as external*/
        {
            symbol = (ptrSymbol)(tempNode->ptrVal);
            fprintf(externFile, "%s %04d\n", symAppearMem->key, symbol->position);
        }

        symAppearMem = symAppearMem->next;
    }

    /*Success*/
    return true;
}


int createEntryFile(char* inputFileName, char* outputFileName, ptrNode entryList, ptrNode symbolList)
{
    FILE* entryFile = NULL;
    ptrNode tempNode = NULL;
    ptrSymbol symbol = NULL;

    /*Open the entry file for writing*/
    entryFile = fopen(outputFileName, "w");
    if (entryFile == NULL)
    {
        fprintf(stderr, "Error: could not open entry file. file: %s\n", inputFileName);
        return false;
    }

    /*For each node of the entry list - write the symbol and its position to the entry file*/
    while (entryList != NULL)
    {
        tempNode = searchKey(symbolList, entryList->key);
        if (tempNode != NULL)   /*If the symbol is defined in the file */
        {
            symbol = (ptrSymbol)(tempNode->ptrVal);
            fprintf(entryFile, "%s %04d\n", entryList->key, symbol->position);
        }

        entryList = entryList->next;
    }

    /*Success*/
    return true;
}


int secondPass(char* inputFileName, char* exOutputFileName, char* entOutputFileName, ptrNode memoryImage, ptrNode symbolList, ptrNode externList, ptrNode enteryList, ptrNode symAppearMem, int IC)
{
    int error = false;
    boolean toCreateExtern = false;

    /*Update the position of the data symbols in the symbol list*/
    if (symbolPositionUpdate(symbolList, IC) == false)  error = true;

    /*Check if all the symbols in the memory appearance list are defined in the file*/
    if (symbolValidation(inputFileName, symbolList, symAppearMem, externList, enteryList) == false)  error = false;

    /*Create the extern file*/
    if (createExternFile(inputFileName, exOutputFileName, symAppearMem, externList, &toCreateExtern) == false && toCreateExtern == true) 
    {
        fprintf(stderr, "Error: could not create extern file. file: %s\n", inputFileName);
        return false;
    }

    /*Success*/
    return true;
}