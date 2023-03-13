/**********************************************************************
 * \file	exercise_1_11_word_count_program.c
 *
 * \brief 	Program that counts the number of  lines, words and 
 *		characters in input.
 * 
 * \description	N.A.
 * 
 *
 * \author	Mihail P. (MP)
 * \date	13.III.2023 08:40PM
 * \tag		"The C Programming Language 2nd Edition"
 * 		by Brian W. Kernighan and Dennis M. Ritchie
 * 		Chapter 1, Section 1.5
 * 		page 21, Exercise 1-11
 **********************************************************************/


#include <stdio.h>

#define	IN	1	/* inside a word */
#define	OUT	0	/* outside a word */

/*count lines, words, and characters in input */
int main(void)
{
	int c, nl, nw, nc, state;
	
	state = OUT;
	nl = nw = nc = 0;
	while((c = getchar()) != EOF)	
	{
		nc++;
		if(c == '\n')
			++nl;
		if(c == ' ' || c == '\n' || c == '\t')
			state = OUT;
		else if(state == OUT)
		{
			state = IN;
			++nw;
		}
	}
	printf("%d %d %d\n", nl, nw, nc);
	return 0;
}

/* 
1. How would you test the word count program?
Answer: Input with multiple lines. Input with one line. Input with nothing. Input with multiple lines but one word per line. Input which tests all kinds of word separation. Check the state machine on IN or OUT of a word.
2. What kinds of input are most likely to uncover bugs if there are any?
Answer: A long enough input may break the while loop. 
*/
