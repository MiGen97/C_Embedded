/******************************************************************
 * \file	exercise_1_7_printEOFValue.c
 *
 * \brief 	Program that prints the value of EOF.
 * 
 * \description	This file is using the stdio library to print
 *		the value of EOF. 
 *
 * \author	Mihail P. (MP)
 * \date	09.XI.2021 03:44AM
 * \tag		"The C Programming Language 2nd Edition"
 * 		by Brian W. Kernighan and Dennis M. Ritchie
 * 		Chapter 1, Section 1.5
 * 		page 17, Exercise 1-7
 ******************************************************************/


#include <stdio.h>

int main(void)
{
	printf("char= %c\nvalue= %d\n",EOF, EOF);
	return 0;
}

