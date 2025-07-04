/**********************************************************************
 * \file        ex25_implement_qsort.c
 *
 * \brief       Implement a basic version of qsort() using function pointers.
 * 
 * \description N.A.
 * 
 *
 * \author      Mihail P. (MP)
 * \date        04.VII.2025 01:10PM
 **********************************************************************/
#include <stdio.h>
#include <stdlib.h>

#define NB_ELEMENTS 10

void initArray(void* array, const int nbElem, const int sizeOfElem, void (*initElem)(void* ));
void initElemChar(void* elem);
void initElemInt(void* elem);
void initElemFloat(void* elem);

void myQsort(void *base, int leftBoundary, int rightBoundary, int sizeOfElem, 
    int (*compareFunc)(const void*, const void*),
    void (*swapFunc)(void*, void*));
int partition(void* base, int leftBoundary, int rightBoundary, int sizeOfElem, 
    int (*compareFunc)(const void*, const void*),
    void (*swapFunc)(void*, void*));
int compareChars(const void* a, const void* b);
int compareInt(const void* a, const void* b);
int compareFloat(const void* a, const void* b);
void swapChars(void* a, void* b);
void swapInt(void* a, void* b);
void swapFloat(void* a, void* b);

void printArray(const void* array, const int nbElem, const int sizeOfElem, void (*printElem)(const void*));
void printElemChar(const void* element);
void printElemInt(const void* element);
void printElemFloat(const void* element);

int main(void){
    char* arrayOfChars = (char*)calloc(NB_ELEMENTS, sizeof(char));
    int* arrayOfInts = (int*)calloc(NB_ELEMENTS, sizeof(int));
    float* arrayOfFloats = (float*)calloc(NB_ELEMENTS, sizeof(float));

    initArray(arrayOfChars,NB_ELEMENTS,sizeof(char),initElemChar);
    initArray(arrayOfInts,NB_ELEMENTS,sizeof(int),initElemInt);
    initArray(arrayOfFloats,NB_ELEMENTS,sizeof(float),initElemFloat);

    printf("Before the sorting:\n");
    printArray(arrayOfChars,NB_ELEMENTS,sizeof(char),printElemChar);
    printArray(arrayOfInts,NB_ELEMENTS,sizeof(int),printElemInt);
    printArray(arrayOfFloats,NB_ELEMENTS,sizeof(float),printElemFloat);

    myQsort(arrayOfChars,0,NB_ELEMENTS-1,sizeof(char),compareChars,swapChars);
    myQsort(arrayOfInts,0,NB_ELEMENTS-1,sizeof(int),compareInt,swapInt);
    myQsort(arrayOfFloats,0,NB_ELEMENTS-1,sizeof(float),compareFloat,swapFloat);

    printf("After sorting:\n");
    printArray(arrayOfChars,NB_ELEMENTS,sizeof(char),printElemChar);
    printArray(arrayOfInts,NB_ELEMENTS,sizeof(int),printElemInt);
    printArray(arrayOfFloats,NB_ELEMENTS,sizeof(float),printElemFloat);

    free(arrayOfChars);
    free(arrayOfInts);
    free(arrayOfFloats);
    return 0;
}

void initArray(void* array, const int nbElem, const int sizeOfElem, 
    void (*initElem)(void *)){
    for(int i=0; i < nbElem; i++){
        void* temp = (void*)(((char*)array)+(i*sizeOfElem));
        initElem(temp);
    }
}
void initElemChar(void* elem){
    *((char*)elem)=65+(rand()%26); //fill only with Uppercase letters
}
void initElemInt(void* elem){
    *((int*)elem)=rand()%100; //fill only with numbers up to 99
}
void initElemFloat(void* elem){
    *((float*)elem)=(rand()%10000)/100.00; //fill with numbers up 100 and with 2 decimal points
}

void myQsort(void *base, int leftBoundary, int rightBoundary, int sizeOfElem, 
    int (*compareFunc)(const void*, const void*),
    void (*swapFunc)(void*, void*)){
    if(leftBoundary < rightBoundary){
        //select pivot and partition the array
        int pivot = partition(base,leftBoundary,rightBoundary,sizeOfElem, compareFunc, swapFunc);

        //process each partition
        myQsort(base,leftBoundary,pivot-1,sizeOfElem,compareFunc,swapFunc);
        myQsort(base,pivot+1,rightBoundary,sizeOfElem,compareFunc,swapFunc);
    }
}

int partition(void* base, int leftBoundary, int rightBoundary, int sizeOfElem, 
    int (*compareFunc)(const void*, const void*),
    void (*swapFunc)(void*, void*)){
    //set the pivot to the right most elemet;
    int pivotIndex = rightBoundary;

    int i = leftBoundary, j = rightBoundary-1;
    while(i < j)
    {
        //from left bound move until you find a value bigger than pivot
        while( (compareFunc((void*)((char*)base)+(i*sizeOfElem), 
                            (void*)((char*)base)+(pivotIndex*sizeOfElem)) <= 0) 
                && (i <= rightBoundary-1) ) 
            i++;

        //from right bound move until you find a value smaller or equal than pivot
        while( (compareFunc((void*)((char*)base)+(j*sizeOfElem), 
                            (void*)((char*)base)+(pivotIndex*sizeOfElem)) > 0) 
                && (j >= leftBoundary+1) ) 
            j--;

        // replace the 2 values from left and right bound
        if(i<j){
            swapFunc((void*)((char*)base)+(i*sizeOfElem), (void*)((char*)base)+(j*sizeOfElem));
        }
    }
    //put pivot in the middle (swap with bigger value)
    swapFunc((void*)((char*)base)+(pivotIndex*sizeOfElem),(void*)((char*)base)+(i*sizeOfElem));

    return i;
}

int compareChars(const void* a, const void* b){
    return(*((char*)a)-*((char*)b));
}
void swapChars(void* a, void* b){
    char temp = *((char*)a);
    *((char*)a)=*((char*)b);
    *((char*)b)=temp;
}
int compareInt(const void* a, const void* b){
    return(*((int*)a)-*((int*)b));
}
void swapInt(void* a, void* b){
    int temp = *((int*)a);
    *((int*)a)=*((int*)b);
    *((int*)b)=temp;
}
int compareFloat(const void* a, const void* b){
    float fa =*((float*)a);
    float fb =*((float*)b);
    if( fa < fb ) return -1;
    if( fa > fb ) return 1;
    return 0;
}
void swapFloat(void* a, void* b){
    float temp = *((float*)a);
    *((float*)a)=*((float*)b);
    *((float*)b)=temp;
}

void printArray(const void* array, const int nbElem, const int sizeOfElem, 
    void (*printElem)(const void*)){
    for(int i=0; i < nbElem; i++){
        const void * temp =(void*)(((char*)array)+(i*sizeOfElem));
        printElem(temp);
    }
    printf("\n");
}
void printElemChar(const void* element){
    printf("%c ",*((char*)element));
}
void printElemInt(const void* element){
    printf("%i ",*((int*)element));
}
void printElemFloat(const void* element){
    printf("%.2f ",*((float*)element));
}