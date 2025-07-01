/**********************************************************************
 * \file        ex13_remove_from_array.c
 *
 * \brief       Write a function that removes duplicates from a dynamically allocated array.
 * 
 * \description N.A.
 * 
 *
 * \author      Mihail P. (MP)
 * \date        01.VII.2025 05:20PM
 **********************************************************************/
#include <stdio.h>
#include <stdlib.h>

#define ELEMENTS 100

int* allocateArray(int size);
void populateArray(int* array);
int isDuplicate(int* array, int begin);

int main(void)
{
    int* array = allocateArray(ELEMENTS*sizeof(int));
    if(array == NULL){
        return 1;
    }
    populateArray(array);

    int uniqueIndex=0;
    for(int i=0; i < ELEMENTS; i++){
        if( ! isDuplicate(array,i)){
            array[uniqueIndex] = array[i];
            uniqueIndex++;
        }
    }

    //shrink the memory allocated for array to the new size without duplicates.
    array=(int*)realloc(array,uniqueIndex*sizeof(int));
    if(array == NULL){
        printf("Failed to reallocate memory.\n");
        return 1;
    }

    for(int i=0; i < uniqueIndex; i++){
        printf("%d ",array[i]);
    }
    printf("\n");

    free(array);
    return 0;
}

int* allocateArray(int size)
{
    int* array = (int*)malloc(size);
    if(array == NULL)
    {
        printf("Failed to allocate the memory for array!\n");
    }
    return array;
}

void populateArray(int* array)
{
    for(int i=0; i< ELEMENTS; i++){
        array[i]=rand()%10;
    }
}

int isDuplicate(int* array, int begin)
{
    for(int i=begin+1; i<ELEMENTS; i++)
    {
        if(array[begin] == array[i])
            return 1;
    }
    return 0;
}
