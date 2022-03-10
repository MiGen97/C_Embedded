/**********************************************************************
 * \file	exercise_1_10_replace_printed_char_with_special_char.c
 *
 * \brief 	Program that replaces the tabs, backspaces and 
 *		backslashes with their special characters /t,/b and //.
 * 
 * \description	N.A.
 * 
 *
 * \author	Mihail P. (MP)
 * \date	10.III.2022 09:25PM
 * \tag		"The C Programming Language 2nd Edition"
 * 		by Brian W. Kernighan and Dennis M. Ritchie
 * 		Chapter 1, Section 1.5
 * 		page 20, Exercise 1-10
 **********************************************************************/


#include <stdio.h>

int main(void)
{
	int c;
	int blankFlag=0;
	while((c=getchar()) != EOF)	
	{
		switch(c)
		{
			case '\t': printf("\\t");
			break;
			case '\b': printf("\\b");
			break;
			case '\\': printf("\\\\");
			break;
			default: printf("%c",c);
			break;
		}

	}
	return 0;
}

