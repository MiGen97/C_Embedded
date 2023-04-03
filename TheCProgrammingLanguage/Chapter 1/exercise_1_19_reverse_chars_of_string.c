/**********************************************************************
 * \file	exercise_1_19_reverse_chars_of_string.c
 *
 * \brief 	Program that reverses the characters string. And reverses its
 *			input a line at a time.
 *
 * \description	N.A.
 *
 *
 * \author	Mihail P. (MP)
 * \date	15.III.2023 09:55PM
 * \tag		"The C Programming Language 2nd Edition"
 * 		by Brian W. Kernighan and Dennis M. Ritchie
 * 		Chapter 1, Section 1.9
 * 		page 31, Exercise 1-19
 **********************************************************************/


#include <stdio.h>
#define MAXLINE 1000	/* maximum input line size */

int getline(char line[], int maxline);
void reverse(char s[], int length);

int main(void)
{
	int len;	/* current line length */
	char line[MAXLINE];	/* current input line */

	while ((len = getline(line, MAXLINE)) > 0)
	{
		reverse(line, len);
		printf("%s\n",line);
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

/* reverse: reverses the character string s */
void reverse(char s[], int length)
{
	int i = 0;
	int lastChar = length;
	
	if(s[lastChar - 1] == '\n') --lastChar;
		
	while( i < (((length)/2)) )
	{
		char temp = s[i];
		s[i] = s[lastChar - i];
		s[lastChar - i] = temp;
		++i;
	}
}
