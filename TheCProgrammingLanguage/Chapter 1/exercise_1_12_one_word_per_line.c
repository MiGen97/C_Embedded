/**********************************************************************
 * \file	exercise_1_12_one_word_per_line.c
 *
 * \brief 	Program writes its input one word per line.
 *
 * \description	N.A.
 *
 *
 * \author	Mihail P. (MP)
 * \date	13.III.2023 08:55PM
 * \tag		"The C Programming Language 2nd Edition"
 * 		by Brian W. Kernighan and Dennis M. Ritchie
 * 		Chapter 1, Section 1.5
 * 		page 21, Exercise 1-12
 **********************************************************************/


#include <stdio.h>

#define	IN	1	/* inside a word */
#define	OUT	0	/* outside a word */

int main(void)
{
	int c, state;

	state = OUT;
	while((c = getchar()) != EOF)
	{
		if(c == ' ' || c == '\n' || c == '\t')
				state = OUT;
		else if(state == OUT)
		{
			state = IN;
			printf("\n");
		}
		if(state == IN)
			putchar(c);
	}
	return 0;
}
