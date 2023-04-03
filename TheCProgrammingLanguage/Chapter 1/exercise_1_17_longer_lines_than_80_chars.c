/**********************************************************************
 * \file	exercise_1_17_longer_lines_than_80_chars.c
 *
 * \brief 	Program that prints all the lines longer than 80 characters.
 *
 * \description	N.A.
 *
 *
 * \author	Mihail P. (MP)
 * \date	15.III.2023 09:25PM
 * \tag		"The C Programming Language 2nd Edition"
 * 		by Brian W. Kernighan and Dennis M. Ritchie
 * 		Chapter 1, Section 1.9
 * 		page 31, Exercise 1-17
 **********************************************************************/


#include <stdio.h>
#define MAXLINE 1000	/* maximum input line size */

int getline(char line[], int maxline);
void copy(char to[], char from[]);

int main(void)
{
	int len;	/* current line length */
	char line[MAXLINE];	/* current input line */
	
	while ((len = getline(line, MAXLINE)) > 0)
	{
		if (len > 80u)
		{
			printf("%s\n\n", line);
		}
	}
	return 0;
}

/* getline: read a line into s, return length */
int getline(char s[], int lim)
{
	int c,i;
	
	for(i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
		s[i] = c;
	if (c == '\n')
	{
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}
