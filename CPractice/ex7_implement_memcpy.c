/**********************************************************************
 * \file        ex7_implement_memcpy.c
 *
 * \brief       Implement memcpy() using only pointers.
 * 
 * \description N.A.
 * 
 *
 * \author      Mihail P. (MP)
 * \date        01.VII.2025 00:59AM
 **********************************************************************/
#include <stdio.h>
#include <stdlib.h>

#define ARRAY_LENGTH 100

void myMemCpy(void* src, void* dest, int length);

int main(void)
{
    int returnValue = 0;
    int *array1 = (int *)calloc(ARRAY_LENGTH, sizeof(int));
    int *array2 = (int *)calloc(ARRAY_LENGTH, sizeof(int));
    if ((array1 == NULL) || (array2 == NULL))
    {
        printf("Calloc failed.\n");
        returnValue = 1;
    }
    else
    {
        // populate array1 with random values, leave array2 with 0 values from calloc
        for (int i = 0; i < ARRAY_LENGTH; i++)
        {
            array1[i] = rand() % 500;
            printf("array1[%d]=%d\n", i, array1[i]);
        }

        myMemCpy(array1, array2, ARRAY_LENGTH*sizeof(int));

        for (int i = 0; i < ARRAY_LENGTH; i++)
        {
            printf("array2[%d]=%d\n", i, array2[i]);
        }

        free(array1);
        free(array2);
    }
    return returnValue;
}


void myMemCpy(void* src, void* dest,int length)
{
    char* d=dest;
    const char* s=src;

    while (length > 0)
    {
        *d = *s;
        d++;
        s++;
        length--;
    }
}