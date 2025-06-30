/**********************************************************************
 * \file        ex2_reverse_string.c
 *
 * \brief       Reverse a string in place using pointers.
 * 
 * \description N.A.
 * 
 *
 * \author      Mihail P. (MP)
 * \date        30.VI.2025 10:04PM
 **********************************************************************/

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>

 #define MAX_LIMIT 100

 void reverseString(char* str);

 int main(void)
 {
    char* inputString = (char*) malloc(sizeof(char)*MAX_LIMIT);

    printf("Please enter the input string:");
    if(fgets(inputString, MAX_LIMIT, stdin) != NULL)
    {
        inputString[strcspn(inputString, "\r\n")] = 0;
        printf("The reverse of the string %s, is ", inputString);
        reverseString(inputString);
        printf("%s.\n", inputString);
    }
    else
    {
		printf("Error reading the input.\n");
    }

    free(inputString);
    return 0;
 }

 void reverseString(char* str)
 {
    char temp='\0';
    int lastCharPosInString=strlen(str)-1;
    for(int i=0; i<lastCharPosInString/2; i++)
    {
        temp=str[i];
        str[i]=str[lastCharPosInString-i];
        str[lastCharPosInString-i]=temp;
    }
 }