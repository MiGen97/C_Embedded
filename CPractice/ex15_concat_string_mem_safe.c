/**********************************************************************
 * \file        ex15_concat_string_mem_safe.c
 *
 * \brief       Write a memory-safe function to concatenate two strings.
 * 
 * \description N.A.
 * 
 *
 * \author      Mihail P. (MP)
 * \date        01.VII.2025 06:04PM
 **********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LIMIT 50

char* myStrCat(char* dest, const char* src);
void* allocateSafe(size_t nbElements, size_t elementSize);

int main(void)
{
    char* str1 = (char*) allocateSafe(sizeof(char),MAX_LIMIT);
    char* str2 = (char*) allocateSafe(sizeof(char),MAX_LIMIT);
    
    if((str1 != NULL) && (str2 != NULL)){
        strcpy(str1,"Works good ");
        strcpy(str2,"relearning of C.");

        str1 = myStrCat(str1,str2);

        printf("%s\n",str1);

        free(str1);
        free(str2);
    }

    return 0;
}


void* allocateSafe(size_t nbElements, size_t elementSize)
{
    void* array= (void*)malloc(elementSize*nbElements);
    if(array==NULL){
        printf("Failed to allocate memory.\n");
        return NULL;
    }
    return array;
}

char* myStrCat(char* dest, const char* src)
{
    int newSize=strlen(dest)+strlen(src)+1;

    char* temp =(char*) malloc(sizeof(char)*newSize);
    if(temp==NULL){
        printf("Failed to allocate memory for strcat.\n");
        return NULL;
    }
    
    memcpy(temp,dest,strlen(dest));
    memcpy(temp+strlen(dest),src,strlen(src)+1);

    free(dest);
    dest = temp;
    return dest;
}
