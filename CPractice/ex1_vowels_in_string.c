/**********************************************************************
 * \file        ex1_vowels_in_string.c
 *
 * \brief       Write a function to count the number of vowels in a string.
 * 
 * \description N.A.
 * 
 *
 * \author      Mihail P. (MP)
 * \date        30.VI.2025 09:24PM
 **********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LIMIT 100
#define NB_OF_VOWELS 10

int getNumberOfVowels(const char* str);

int main(void)
{
	char* inputString = (char*) malloc(sizeof(char)*MAX_LIMIT);

	printf("Please enter the string:");
	if(fgets(inputString, MAX_LIMIT, stdin ))
	{
		printf("The number of vowels in this string is: %d.\n",getNumberOfVowels(inputString));
	}
	else
	{
		printf("Error reading the input.\n");
	}

	free(inputString);

	return 0;
}

int getNumberOfVowels(const char* str)
{
	char vowels[] = {'A','E','I','O','U','a','e','i','o','u'};
	int nbVowels=0;
	for(int i=0; i <  strlen(str); i++)	
	{
		for(int j=0; j<NB_OF_VOWELS;j++)
		{
			if (str[i] == vowels[j])
			{
				nbVowels++;	
			}
		}
	}

	return nbVowels;
}
