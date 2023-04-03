/**********************************************************************
 * \file	exercise_1_21_entab.c
 *
 * \brief 	Program that replaces the string of blanks in the input with the
 *			minimum number of blanks and tabs.
 *
 * \description	N.A.
 *
 * \author	Mihail P. (MP)
 * \date	02.IV.2023 05:35PM
 * \tag		"The C Programming Language 2nd Edition"
 * 		by Brian W. Kernighan and Dennis M. Ritchie
 * 		Chapter 1, Section 1.10
 * 		page 34, Exercise 1-21
 **********************************************************************/


#include <stdio.h>
#define MAXLINE	1000	/* maximum input line size */
#define	TAB_SIZE	4	/* the size of the tab in */

int getline(char line[], int maxline);
void replaceBlanks(char s[]);

int main(void)
{
	int len;	/* current line length */
	char line[MAXLINE];	/* current input line */

	while ((len = getline(line, MAXLINE)) > 0)
	{
		replaceBlanks(line);
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

/* replaceBlanks: replaces blanks with the apropriate number of tabs and blanks */
void replaceBlanks(char s[])
{
	int i = 0;
	while( s[i]!='\0')
	{
		int j = 0;
		/* convert the apropriate number of blanks into tabs */
		while(' ' == s[i])
		{
			j++;
			if( j % TAB_SIZE == 0)
			{
				printf("\t");
				j = 0;
			}
			i++;
		}
		/* print the remaining blanks that were note replaced with tabs */
		while( j > 0 )
		{
			printf(" ");
			j--;
		}

		printf("%c",s[i]);

		i++;
	}
}
