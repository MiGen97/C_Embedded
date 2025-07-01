/**********************************************************************
 * \file        ex21_modify_string_in_place.c
 *
 * \brief       Use a pointer to a pointer to modify a string in-place inside a function.
 * 
 * \description N.A.
 * 
 *
 * \author      Mihail P. (MP)
 * \date        01.VII.2025 11:39PM
 **********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LIMIT 100

void modifyStringInPlace(char** str);

 int main(void){
    const char demoString[]="Relearning the C language at fast pace.";
    char* str=(char*)malloc(sizeof(char)*(strlen(demoString)+1));
    memcpy(str,demoString,strlen(demoString)+1);

    modifyStringInPlace(&str);

    printf("%s\n",str);

    free(str);
    return 0;
}


void modifyStringInPlace(char** str){
    char* modifPointer=*str;
    int modifPos=5, modifNb=3;
    if((modifPos+modifNb) < strlen(*str))
        for(int i=modifPos; i< modifPos+modifNb; i++)
            modifPointer[i]='n';
}