/******************************************************************
 * \file	exercise_1_6_checkEOFValue.c
 *
 * \brief 	Program that checks the value of != operator is.
 * 
 * \description	This file is using the stdio library to print
 *		the value returned by operator !=. 
 *
 * \author	Mihail P. (MP)
 * \date	09.XI.2021 03:24AM
 * \tag		"The C Programming Language 2nd Edition"
 * 		by Brian W. Kernighan and Dennis M. Ritchie
 * 		Chapter 1, Section 1.5
 * 		page 17, Exercise 1-6
 ******************************************************************/


#include <stdio.h>

int main(void)
{
	int c;
	
	while( c = (getchar() != EOF))
		printf("%d\n",c);
	printf("%d\n",c); /* print when the value is 0 */
	return 0;
}

