/**********************************************************************
 * \file	exercise_1_16_longest_line.c
 *
 * \brief 	Program that prints the longest line from the received input text,
 *			each lines length and each line.
 *
 * \description	N.A.
 *
 *
 * \author	Mihail P. (MP)
 * \date	15.III.2023 08:50PM
 * \tag		"The C Programming Language 2nd Edition"
 * 		by Brian W. Kernighan and Dennis M. Ritchie
 * 		Chapter 1, Section 1.9
 * 		page 30, Exercise 1-16
 **********************************************************************/


#include <stdio.h>
#define MAXLINE 1000	/* maximum input line size */

int getline(char line[], int maxline);
void copy(char to[], char from[]);

/* print longest input line */
int main(void)
{
	int len;	/* current line length */
	int max;	/* maximum length seen so far */
	char line[MAXLINE];	/* current input line */
	char longest[MAXLINE];	/* longest line saved here */
	
	max = 0;
	while ((len = getline(line, MAXLINE)) > 0)
	{
		printf("Line length=%d.\n", len);
		printf("%s\n\n", line);
		if (len > max)
		{
			max = len;
			copy(longest, line);
		}
	}
	if (max > 0)	/* there was a line */
		printf("%s", longest);
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

/* copy: copy 'from' into 'to'; assume to is big enough */
void copy(char to[], char from[])
{
	int i;
	
	i = 0;
	while ((to[i] = from [i]) != '\0')
		++i;
}