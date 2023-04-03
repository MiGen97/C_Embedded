/**********************************************************************
 * \file	exercise_1_14_histogram_of_chars_frequencies.c
 *
 * \brief 	Program prints the histogram of the frequencies of characters.
 *
 * \description	N.A.
 *
 *
 * \author	Mihail P. (MP)
 * \date	14.III.2023 09:40PM
 * \tag		"The C Programming Language 2nd Edition"
 * 		by Brian W. Kernighan and Dennis M. Ritchie
 * 		Chapter 1, Section 1.6
 * 		page 24, Exercise 1-14
 **********************************************************************/


#include <stdio.h>

#define NB_ASCII_CHARS	128
#define NB_HIST_ELEMENTS NB_ASCII_CHARS

int main(void)
{
	int c;
	int histgram[NB_HIST_ELEMENTS] = {0};

	while((c = getchar()) != EOF)
	{
        ++histgram[c];
	}

	/* horizontal histogram */
	for(int i = 0; i < NB_HIST_ELEMENTS; i++)
	{
	    printf("%2c ",i);
		for(int j=0; j<histgram[i]; j++)
		{
			printf("#");
		}
		printf("\n");
	}
	return 0;
}
