/******************************************************************
 * \file	exercise_1_8_count_blanks_tabs_newlines.c
 *
 * \brief 	Program that counts the number of blanks, tabs and 
 *		new lines.
 * 
 * \description	This file is using the stdio library to print
 *		the number of blanks, tabs and new lines from the input. 
 *
 * \author	Mihail P. (MP)
 * \date	10.III.2022 08:10PM
 * \tag		"The C Programming Language 2nd Edition"
 * 		by Brian W. Kernighan and Dennis M. Ritchie
 * 		Chapter 1, Section 1.5
 * 		page 20, Exercise 1-8
 ******************************************************************/


#include <stdio.h>

int main(void)
{
	int c,nbBlanks,nbTabs,nbNewLines;
	nbBlanks = 0;
	nbTabs = 0;
	nbNewLines = 0;
	while((c=getchar()) != EOF)
	{
		switch(c)
		{
			case '\n': nbNewLines++;
			break;
			case '\t': nbTabs++;
			break;
			case ' ': nbBlanks++;
			break;
			default:
			break;
		}
	}
	printf("nbBlanks= %d\nnbTabs= %d\nnbNewLines= %d\n",nbBlanks, nbTabs, nbNewLines);
	return 0;
}

