/**********************************************************************
 * \file	exercise_1_22_fold_long_lines.c
 *
 * \brief 	Program that "folds" long input lines into multiple shorter lines
 *			after the last non-blank character that occurs before the n-th column of input.
 *
 * \description	N.A.
 *
 * \author	Mihail P. (MP)
 * \date	03.IV.2023 10:00PM
 * \tag		"The C Programming Language 2nd Edition"
 * 		by Brian W. Kernighan and Dennis M. Ritchie
 * 		Chapter 1, Section 1.10
 * 		page 34, Exercise 1-22
 **********************************************************************/


#include <stdio.h>


#define TRUE    1
#define FALSE   0
#define MAXLINE	1000	/* maximum input line size */
#define	MAX_LENGTH_SHORT_LINE	30 /* define the maximum length of the shorter line */


char shortLine[MAX_LENGTH_SHORT_LINE]="";
int positionOfLastBlankInShortLine = -1;
int positionOfLastBlankInLongLine = -1;
int shortLineCurrentPos=0;


int getline(char line[], int maxline);
void foldLine(char s[]);
void initVariableForANewShortLine();

int main(void)
{
	int len;	/* current line length */
	char line[MAXLINE];	/* current input line */

	while ((len = getline(line, MAXLINE)) > 0)
	{
		foldLine(line);
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

/* foldLine: folds line into multiple shorter lines */
void foldLine(char s[])
{
	
	for(int i=0; s[i]!='\0'; i++)
	{
		/* check if the current character is blank */
		if(s[i]==' ')
		{
			positionOfLastBlankInLongLine = i;
			positionOfLastBlankInShortLine = shortLineCurrentPos;
		}
		
		/* place the character in the shortLine string */
		shortLine[shortLineCurrentPos]=s[i];
		shortLineCurrentPos++;
		
		/* the maximum length for the short line was reached */
		if( (shortLineCurrentPos % MAX_LENGTH_SHORT_LINE) == (MAX_LENGTH_SHORT_LINE - 1) )
		{
			/*no blank found*/
			if(positionOfLastBlankInShortLine == -1)
			{
				shortLine[shortLineCurrentPos-2] = '-';
				shortLine[shortLineCurrentPos-1] = '\n';
				shortLine[shortLineCurrentPos] = '\0';
				i = i-2;
			}
			
			/* blanks were found in the short line */
			if(positionOfLastBlankInShortLine >= 0)
			{
				shortLine[positionOfLastBlankInShortLine] = '\n';
				shortLine[positionOfLastBlankInShortLine+1] = '\0';
				i = positionOfLastBlankInLongLine;
			}
			
			/* display the short line */
			printf("%s",shortLine);
			
			/* initialize again the algorithm for the next short line */
			initVariableForANewShortLine();
		}
	}
	
	/* treat also the case when the last part of the long line 
	is shorter than the max_length allowed for the short line */
	if(shortLineCurrentPos>=0)
	{
		shortLine[shortLineCurrentPos] = '\n';
		shortLine[shortLineCurrentPos+1] = '\0';
		printf("%s",shortLine);
	}
}

void initVariableForANewShortLine()
{
	shortLine[0]='\0';
	shortLineCurrentPos = 0;
	positionOfLastBlankInLongLine = -1;
	positionOfLastBlankInShortLine = -1;
}
