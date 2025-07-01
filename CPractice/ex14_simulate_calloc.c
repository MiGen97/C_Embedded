/**********************************************************************
 * \file        ex14_simulate_calloc.c
 *
 * \brief       Simulate calloc() using malloc and memset.
 * 
 * \description N.A.
 * 
 *
 * \author      Mihail P. (MP)
 * \date        01.VII.2025 05:55PM
 **********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ELEMENTS 100

void* myCalloc(size_t nbElements, size_t elementSize);

int main(void)
{
    int* array = myCalloc(ELEMENTS,sizeof(int));

    for(int i=0; i<ELEMENTS; i++)
        printf("%d ",array[i]);

    free(array);
    return 0;
}

void* myCalloc(size_t nbElements, size_t elementSize)
{
    char* array=(char*) malloc(nbElements*elementSize);
    if(array==NULL){
        printf("Memory allocation failed.\n");
        return NULL;
    }
    memset(array, 0, nbElements*elementSize);
    return array;
}
