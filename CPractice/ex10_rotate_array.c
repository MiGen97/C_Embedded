/**********************************************************************
 * \file        ex10_rotate_array.c
 *
 * \brief       Rotate an array to the left by k positions using pointers.
 * 
 * \description N.A.
 * 
 *
 * \author      Mihail P. (MP)
 * \date        01.VII.2025 02:09AM
 **********************************************************************/
#include <stdio.h>
#include <stdlib.h>

#define MAX_LIMIT 10 

void rotateArray(int* array, const int arrayLength, const int rotatePos);

int main(void)
{
    int returnValue = 0;
    int *array = (int *)calloc(MAX_LIMIT, sizeof(int));
    if (array == NULL)
    {
        printf("Calloc failed.\n");
        returnValue = 1;
    }
    else
    {
        int k=0;
        printf("Give the nb of array rotation positions: ");
        scanf("%d",&k);

        // populate array with random values
        for (int i = 0; i < MAX_LIMIT; i++)
        {
            array[i] = rand() % 500;
            printf("array[%d]=%d\n", i, array[i]);
        }

        rotateArray(array, MAX_LIMIT, k);
        
        printf("Rotated array:\n");
        for (int i = 0; i < MAX_LIMIT; i++)
        {
            printf("array[%d]=%d\n", i, array[i]);
        }

        free(array);
    }
    return returnValue;
}


void rotateArray(int* array, const int arrayLength, const int rotatePos)
{
    if (rotatePos <= 0 || rotatePos >= arrayLength) {
        return; // Nothing to rotate or invalid request
    }

    int* backup = malloc(rotatePos * sizeof(int));
    if (!backup) {
        printf("Memory allocation failed in rotateArray.\n");
        return;
    }

    // Step 1: Backup first rotatePos elements
    for(int i=0;i<rotatePos;i++)
    {
        backup[i] = array[i];
    }

    // Step 2: Shift the rest of the array to the left
    for(int j=rotatePos; j<arrayLength; j++)
    {   
        array[j-rotatePos] = array[j];
    }

    // Step 3: Copy the backup to the end
    for(int j=arrayLength-rotatePos; j<arrayLength; j++)
    {   
        array[j] = backup[j-arrayLength+rotatePos];
    }
}