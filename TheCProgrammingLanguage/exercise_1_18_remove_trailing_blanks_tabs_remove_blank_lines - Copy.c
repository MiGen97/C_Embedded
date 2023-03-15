/**********************************************************************
 * \file	exercise_1_18_remove_trailing_blanks_tabs_remove_blank_lines.c
 *
 * \brief 	Program that remove trailing blanks and tabs from each input line
 *			and delete entirely blank lines.
 *
 * \description	N.A.
 *
 *
 * \author	Mihail P. (MP)
 * \date	15.III.2023 09:30PM
 * \tag		"The C Programming Language 2nd Edition"
 * 		by Brian W. Kernighan and Dennis M. Ritchie
 * 		Chapter 1, Section 1.9
 * 		page 31, Exercise 1-18
 **********************************************************************/


#include <stdio.h>
#define MAXLINE 1000	/* maximum input line size */
#define	IS_NOT_LINE	0	/* value returned in case the line is blank */
#define	IS_LINE		1	/* value returned when line is not blank */

int getline(char line[], int maxline);
int removeTralingBlanksTabs(char line[], int length);

int main(void)
{
	int len;	/* current line length */
	char line[MAXLINE];	/* current input line */

	while ((len = getline(line, MAXLINE)) > 0)
	{
		if(removeTralingBlanksTabs(line, len) == IS_LINE)
		{
			printf("%s",line);
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

/* removeTralingBlanksTabs: remove Traling Blanks Tabs from the input line */
int removeTralingBlanksTabs(char line[], int length)
{
	int retVal = IS_LINE;
	int i;
	for(i = length - 2; (line[i] == ' ' || line[i] == '\t') && i>=0; i--)
		;

	if(i >= 0)
	{
		line[i+1] = line[length - 1];
		line[i+2] = line[length];
	}
	else
	{
		retVal = IS_NOT_LINE;
	}

	return retVal;
}
