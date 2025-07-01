/**********************************************************************
 * \file        ex17_sort_structs_array.c
 *
 * \brief       Write a function to sort an array of structs based on one field.
 * 
 * \description N.A.
 * 
 *
 * \author      Mihail P. (MP)
 * \date        01.VII.2025 07:50PM
 **********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ELEMENTS 5

//define struct element
typedef struct{
    int number;
    float value;
} element;

void sortArray(element* array);

int main(void)
{
    
    element* list=(element*)malloc(sizeof(element)*ELEMENTS);
    if(list==NULL){
        printf("Memory allocation failed.\n");
        return 1;
    }

    //populate list of elements
    for(int i=0; i<ELEMENTS; i++){
        list[i].number=rand()%10;
        list[i].value=(float) (rand()%100);
        printf("list[%d]\n\tnumber=%d\n\tvalue=%f\n",i,list[i].number,list[i].value);
    }

    //calculate distance
    sortArray(list);

    //print result
    printf("List of elements sorted by number:\n");
    for(int i=0; i<ELEMENTS; i++){
        printf("list[%d]\n\tnumber=%d\n\tvalue=%f\n",i,list[i].number,list[i].value);
    }

    free(list);
    return 0;
}


void sortArray(element* array)
{
    for(int i=0;i<ELEMENTS-1;i++)
        for(int j=i+1;j<ELEMENTS;j++)
            if(array[i].number > array[j].number)
            {
                element temp = array[i];
                array[i]=array[j];
                array[j]=temp;
            }
}