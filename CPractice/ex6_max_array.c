/**********************************************************************
 * \file        ex6_max_array.c
 *
 * \brief       Implement a function that returns the maximum element in an array using pointers.
 * 
 * \description N.A.
 * 
 *
 * \author      Mihail P. (MP)
 * \date        01.VII.2025 00:40AM
 **********************************************************************/
#include <stdio.h>
#include <stdlib.h>

#define ARRAY_LENGTH 10

 int getMaxElem(const int* array);

 int main(void)
 {
    int returnValue = 0;
    int* array = (int*) calloc(ARRAY_LENGTH, sizeof(int));
    if (array == NULL)
    {
        printf("Calloc failed.\n");
        returnValue = 1;
    }
    else
    {
        for(int i=0; i<ARRAY_LENGTH; i++)
        {
            array[i]=rand()%500;
            printf("array[%d]=%d\n",i,array[i]);
        }
        printf("The max value from array is: %d.\n",getMaxElem(array));

        free(array);
    }
    return returnValue;
 }

 int getMaxElem(const int* array)
 {
    const int* max = array;

    for(int i=0;i<ARRAY_LENGTH;i++)
    {
        if(*max < *array) max=array;
        array++;
    }

    return *max;
 }