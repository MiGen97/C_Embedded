/**********************************************************************
 * \file        ex9_implement_strcpy.c
 *
 * \brief       Implement strcpy() without using standard library functions.
 * 
 * \description N.A.
 * 
 *
 * \author      Mihail P. (MP)
 * \date        01.VII.2025 01:55AM
 **********************************************************************/
#include <stdio.h>
#include <stdlib.h>

#define MAX_LIMIT 100 

void myStrcpy(char* destString, const int destSize, const char* inputString);

int main(void)
{
    int returnValue = 0;
    char inputString[]= "Hello world!";
    char *destString = (char *)calloc(MAX_LIMIT, sizeof(char));
    if (destString == NULL)
    {
        printf("Calloc failed.\n");
        returnValue = 1;
    }
    else
    {
        
        myStrcpy(destString, MAX_LIMIT, inputString);

        printf("%s\n", destString);

        free(destString);
    }
    return returnValue;
}


void myStrcpy(char* destString, const int destSize, const char* inputString)
{
    int copyLimit = destSize-1;
    while(*inputString != '\0' || copyLimit > 0)
    {
        *destString = *inputString;
        inputString++;
        destString++;

        copyLimit--;
        if(copyLimit == 0)
            destString='\0';
    }

}