/**********************************************************************
 * \file        ex22_array_fibonacci.c
 *
 * \brief       Write a function that returns a dynamically allocated array containing the first n Fibonacci numbers.
 * 
 * \description N.A.
 * 
 *
 * \author      Mihail P. (MP)
 * \date        01.VII.2025 11:52PM
 **********************************************************************/
#include <stdio.h>
#include <stdlib.h>

int* createArrayFibonacci(const int n);

 int main(void){
    int n;
    printf("Enter the number of elements from Fibonacci's numbers: ");
    scanf("%d",&n);

    int* array=createArrayFibonacci(n);
    if(array == NULL){
        printf("Failed to create the array.\n");
        return 1;
    }

    for(int i=0;i<n;i++){
        printf("%d ",array[i]);
    }

    free(array);
    return 0;
 }

 int* createArrayFibonacci(const int n){
    if(n<=0) return NULL;

    int* array=(int*)calloc(n,sizeof(int));
    if(array==NULL)
        return NULL;

    if(n>=1) array[0]=0;
    if(n>=2) array[1]=1;
    
    for(int i=2;i<n;i++){
        array[i]=array[i-1]+array[i-2];
    }
    return array;
 }