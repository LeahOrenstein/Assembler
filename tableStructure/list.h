#ifndef TABLE_H
#define TABLE_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*Forward declaration*/
struct node;

/*Define ptrNode as a pointer to struct node*/ 
typedef struct node* ptrNode;

/*Full definition of the node structure*/ 
struct node {
    char key[80];
    void *ptrVal;
    ptrNode next;
};

/* Function prototypes */
ptrNode createNode(char key[], void* val);
void addNodeAtBeginning(ptrNode* head, char key[], void* val);
void addNodeAtEnd(ptrNode* head, char key[], void* val);
void appendNode(ptrNode* head, ptrNode nodeToAppend);
ptrNode searchKey(ptrNode head, char key[]);
void printKeys(ptrNode head);
void printValues(ptrNode head, void (*ptrPrintFunc)(void*));
void freeList(ptrNode* head, void (*freeValue)(void*));
void printListStructure(ptrNode head);



#endif