/******************************************************************
 * \file	exercise_1_9_one_blank.c
 *
 * \brief 	Program that replaces multiple blanks with a single one
 * 
 * \description	N.A.
 * 
 *
 * \author	Mihail P. (MP)
 * \date	10.III.2022 08:20PM
 * \tag		"The C Programming Language 2nd Edition"
 * 		by Brian W. Kernighan and Dennis M. Ritchie
 * 		Chapter 1, Section 1.5
 * 		page 20, Exercise 1-9
 ******************************************************************/


#include <stdio.h>

int main(void)
{
	int c;
	int blankFlag=0;
	while((c=getchar()) != EOF)	
	{
		if(' '==c)
		{
			if(0==blankFlag)
			{
				printf(" ");
			}
			blankFlag=1;
		}
		else
		{
			blankFlag=0;
			printf("%c",c);
		}
	}
	return 0;
}

