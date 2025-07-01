/**********************************************************************
 * \file        ex11_duplicate_string.c
 *
 * \brief       Implement a function that duplicates a string using malloc.
 * 
 * \description N.A.
 * 
 *
 * \author      Mihail P. (MP)
 * \date        01.VII.2025 02:19PM
 **********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LIMIT 100

int main(void)
{
    int returnVal=0;
    char* inputString = (char*)malloc(sizeof(char)*MAX_LIMIT);
    char* destString = (char*)malloc(sizeof(char)*MAX_LIMIT);
    if((inputString == NULL) || (destString == NULL))
    {
        printf("Malloc failed!.\n");
        returnVal=1;
    }
    else
    {
        printf("Please enter the input string:\n");
        if(fgets(inputString, MAX_LIMIT, stdin) == NULL)
        {
            printf("Failed to read the input string.\n");
            returnVal=1;
        }
        else
        {
            for(int i=0; i < strlen(inputString); i++)
            {
                destString[i] = inputString[i];
            }

            printf("Duplicated. DestString is: %s\n",destString);
        }
    }

    free(inputString);
    free(destString);
    return returnVal;
}