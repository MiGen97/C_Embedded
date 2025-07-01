/**********************************************************************
 * \file        ex12_2D_array.c
 *
 * \brief       Allocate a 2D array dynamically and fill it with values.
 * 
 * \description N.A.
 * 
 *
 * \author      Mihail P. (MP)
 * \date        01.VII.2025 02:33PM
 **********************************************************************/
#include <stdio.h>
#include <stdlib.h>

#define ROWS 10
#define COLUMNS 10

int** allocate2DArray(const int size);
void fill2DArray(int** array);
void print2DArray(int** array);
void free2DArray(int** array);

int main(void)
{
    int** array2D = allocate2DArray(sizeof(int*)*ROWS);
    if(array2D == NULL)
    {
        return 1;
    }

    fill2DArray(array2D);
    print2DArray(array2D);
    free2DArray(array2D);

    return 0;
}

int** allocate2DArray(const int size)
{
    int** array = (int**)malloc(size);
    if(array != NULL)
    {
        for(int i=0; i<ROWS; i++)
        {
            array[i]=(int*)malloc(sizeof(int)*COLUMNS);
            if(array[i] == NULL)
            {
                printf("Malloc failed for column %d!.\n",i);

                //free already allocated memory in case of failure
                for(int j=0;j<i;j++)
                {
                    free(array[j]);
                }
                free(array);
                return NULL;
            }
        }
    }
    else
    {
        printf("Allocation of memory for 2D Array failed!\n");
    }
    return array;
}

void fill2DArray(int** array)
{
    //fill 2d array with rand values
    for(int i=0; i<ROWS; i++)
    {
        for(int j=0;j<COLUMNS;j++)
        {
            array[i][j]=rand()%10;
        }
    }
}

void print2DArray(int** array)
{
    //print 2d array values
    for(int i=0; i<ROWS; i++)
    {
        for(int j=0;j<COLUMNS;j++)
        {
            printf("%d ",array[i][j]);
        }
        printf("\n");
    }
}

void free2DArray(int** array)
{
    //free the allocated space
    for(int i=0; i<ROWS; i++)
    {
        free(array[i]);
    }
    free(array);
}