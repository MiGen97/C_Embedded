/******************************************************************
 * \file	exercise_1_2_escapeSequencesExperiment.c
 *
 * \brief 	Program that experiments with Escape Sequences.
 * 
 * \description	This file is using the stdio library to print 
 * 		on screen the Escape Sequences
 *
 * \author	Mihail P. (MP)
 * \date	07.XI.2021 02:47AM
 * \tag		"The C Programming Language 2nd Edition"
 * 		by Brian W. Kernighan and Dennis M. Ritchie
 * 		Chapter 1, Section 1.1
 * 		page 8, Exercise 1-2
 ******************************************************************/


#include <stdio.h>

struct EscapeSequence
{
 char string[6];
 char value;
};

typedef struct EscapeSequence escapeSequence;

int main(void)
{
	escapeSequence array[15]=
	{
		{"\\n",'\n'},			
		{"\\t",'\t'},			
		{"\\a",'\a'},			
		{"\\r",'\r'},			
		{"\\\\",'\\'},			
		{"\\'",'\''},			
		{"\\\"",'\"'},			
		{"\\0",'\0'},			
		{"\\?",'\?'},			
		{"\\v",'\v'},			
		{"\\b",'\b'},			
		{"\\e",'\e'},			
		{"\\f",'\f'},
		{"\\101",'\101'},
		{"\\x41",'\x41'}
	};

	for(int i=0; i<15; i++)
	{
		printf("Character %s is printed as %c.\n",array[i].string, array[i].value);
	}
	return 0;
}
