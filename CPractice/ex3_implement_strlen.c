/**********************************************************************
 * \file        ex3_implement_strlen.c
 *
 * \brief       Implement your own strlen() using pointer arithmetic.
 * 
 * \description N.A.
 * 
 *
 * \author      Mihail P. (MP)
 * \date        30.VI.2025 10:26PM
 **********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LIMIT 100

int myStrlen(const char* str);

int main(void)
{
    char* inputString=(char*) malloc(sizeof(char)*MAX_LIMIT);

    printf("Please enter the input string:");
    if(fgets(inputString, MAX_LIMIT, stdin) != NULL)
    {
        inputString[strcspn(inputString, "\r\n")] = 0;
        printf("The string %s have length %ld and my function returns %d.\n",inputString,strlen(inputString),myStrlen(inputString)); 
    }
    else
    {
		printf("Error reading the input.\n");
    }

    free(inputString);
    return 0;
}

int myStrlen(const char* str)
{
    int len=0;

    while(*str != '\0')
    {
        str++;
        len++;
    }
    return len;
}