/**********************************************************************
 * \file        ex8_sort_array.c
 *
 * \brief       Sort an array using pointer notation (e.g., quick sort).
 * 
 * \description N.A.
 * 
 *
 * \author      Mihail P. (MP)
 * \date        01.VII.2025 01:20AM
 **********************************************************************/
#include <stdio.h>
#include <stdlib.h>

#define ARRAY_LENGTH 100

void quickSortArray(int* array, const int leftBound, const int rightBound);
int partition(int* array, const int leftBound, const int rightBound);
void swap(int* a, int* b);

int main(void)
{
    int returnValue = 0;
    int *array1 = (int *)calloc(ARRAY_LENGTH, sizeof(int));
    if (array1 == NULL)
    {
        printf("Calloc failed.\n");
        returnValue = 1;
    }
    else
    {
        // populate array1 with random values
        for (int i = 0; i < ARRAY_LENGTH; i++)
        {
            array1[i] = rand() % 500;
            printf("array1[%d]=%d\n", i, array1[i]);
        }

        quickSortArray(array1, 0, ARRAY_LENGTH-1);

        for (int i = 0; i < ARRAY_LENGTH; i++)
        {
            printf("array1[%d]=%d\n", i, array1[i]);
        }

        free(array1);
    }
    return returnValue;
}


void quickSortArray(int* array, const int leftBound, const int rightBound)
{
    if(leftBound < rightBound)
    {
        int pivotPos = partition(array, leftBound, rightBound);

        // Recursively call quickSortArray() for left and right
        // halfs based on pivot position
        quickSortArray(array, leftBound, pivotPos - 1);
        quickSortArray(array, pivotPos + 1, rightBound);
    }
}

int partition(int* array, const int leftBound, const int rightBound)
{
    // select pivot wherever you want (e.g.:first element)
    // move it to right (already there)
    int pivot = array[leftBound];

    // until the bounds overlap do
    int i = leftBound, j = rightBound;
    while(i < j)
    {
        // from left bound move until you find a value bigger than pivot
        while( (array[i] <= pivot) && (i <= (rightBound-1)) )
            i++;
        
        // from right bound move until you find a value smaller or equal than pivot
        while( (array[j] > pivot) && (j >= (leftBound+1)) )
            j--;
        
        // replace the 2 values from left and right bound
        if (i < j) {
            swap(&array[i], &array[j]);
        }
    }
    // place pivot in its correct position"
    swap(&array[leftBound], &array[j]);
    
    return j;
}

void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}