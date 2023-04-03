/**********************************************************************
 * \file	exercise_1_20_detab.c
 *
 * \brief 	Program that replaces the tabs in the input with the proper
 *			number of blanks spaces.
 *
 * \description	N.A.
 *
 * \author	Mihail P. (MP)
 * \date	02.IV.2023 05:15PM
 * \tag		"The C Programming Language 2nd Edition"
 * 		by Brian W. Kernighan and Dennis M. Ritchie
 * 		Chapter 1, Section 1.10
 * 		page 34, Exercise 1-20
 **********************************************************************/


#include <stdio.h>
#define MAXLINE	1000	/* maximum input line size */
#define	TAB_SIZE	4	/* the size of the tab in */

int getline(char line[], int maxline);
void replaceTabs(char s[]);

int main(void)
{
	int len;	/* current line length */
	char line[MAXLINE];	/* current input line */

	while ((len = getline(line, MAXLINE)) > 0)
	{
		replaceTabs(line);
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

/* replaceTabs: replaces tabs with the apropriate number of spaces */
void replaceTabs(char s[])
{
	for(int i = 0; s[i]!='\0';i++)
	{
		if('\t' == s[i])
		{
			for(int j = 0; j < TAB_SIZE; j++)
				printf("%c",' ');

		}
		else
		{
			printf("%c",s[i]);
		}
	}
}
