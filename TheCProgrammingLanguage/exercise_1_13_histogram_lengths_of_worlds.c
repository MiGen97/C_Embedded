/**********************************************************************
 * \file	exercise_1_13_histogram_lengths_of_worlds.c
 *
 * \brief 	Program prints the histogram of the lengths of the input words.
 *
 * \description	N.A.
 *
 *
 * \author	Mihail P. (MP)
 * \date	14.III.2023 08:35PM
 * \tag		"The C Programming Language 2nd Edition"
 * 		by Brian W. Kernighan and Dennis M. Ritchie
 * 		Chapter 1, Section 1.5
 * 		page 24, Exercise 1-13
 **********************************************************************/


#include <stdio.h>

#define	IN	1	/* inside a word */
#define	OUT	0	/* outside a word */
#define NB_HIST_ELEMENTS 50

int main(void)
{
	int c, state;
	int nbChars = 0;
	int histgram[NB_HIST_ELEMENTS] = {0};
	int maxNbChars = 0;

	state = OUT;
	while(c = getchar())
	{
		if(c == ' ' || c == '\n' || c == '\t' || c == EOF)
        {
            if(state == IN)
            {
                if(nbChars < NB_HIST_ELEMENTS)
                {
                    if(nbChars > maxNbChars)
                        maxNbChars = nbChars;
                    ++histgram[nbChars];
                    nbChars = 0;
                }
                else
                {
                    printf("Histogram can take only words of max length of %d.",NB_HIST_ELEMENTS-1);
                }
            }
            state = OUT;
        }

		else
        {
            state = IN;
            ++nbChars;
        }
        if(c == EOF)
            break;
	}

	/* horizontal histogram */
	printf("\n\nThe horizontal histogram:\n");
	for(int i = 0; i < NB_HIST_ELEMENTS; i++)
	{
	    printf("%2d",i);
		for(int j=0; j<histgram[i]; j++)
		{
			printf("#");
		}
		printf("\n");
	}

	/* vertical histogram */
	printf("\n\nThe vertical histogram:\n");
	for(int i=maxNbChars; i>0; i--)
	{
		for(int j=0; j<NB_HIST_ELEMENTS; j++)
		{
			if(histgram[j]>=i)
			{
				printf("%3c",'#');
			}
			else
			{
				printf("%3c",' ');
			}
		}
		printf("\n");
	}
	for(int i = 0; i < NB_HIST_ELEMENTS; i++)
	{
		printf("%3d",i);
	}
	return 0;
}
