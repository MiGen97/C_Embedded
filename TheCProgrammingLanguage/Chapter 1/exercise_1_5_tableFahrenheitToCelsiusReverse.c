/******************************************************************
 * \file	exercise_1_5_tableFahrenheitToCelsiusReverse.c
 *
 * \brief 	Program that prints the table with temperatures
 *              conversion from Fahrenheit to Celsius from biggest
 * 		to lowest.
 * 
 * \description	This program makes conversion from Fahrenheit to 
 *              Celsius. Values from 300F to 0F with a step of -20.
 *
 * \author	Mihail P. (MP)
 * \date	09.XI.2021 03:11AM
 * \tag		"The C Programming Language 2nd Edition"
 * 		by Brian W. Kernighan and Dennis M. Ritchie
 * 		Chapter 1, Section 1.3
 * 		page 14, Exercise 1-5
 ******************************************************************/


#include <stdio.h>

#define LOWER	0	/* lower limit of the table */
#define UPPER	300	/* upper limit of the table */
#define STEP	0	/* step size */

/* print Fahrenheit-Celsius table
   for fahr = 300, 280, ..., 0; floating-point version */
int main(void)
{
	float fahr, celsius;

	fahr = UPPER;

	/* print table header */
	printf("Fahrenheit | Celsius\n");
	printf("-----------|--------\n");

	while (fahr >= LOWER)
	{
		celsius = (5.0/9.0) * (fahr-32.0);
		printf("%10.0f | %6.1f\n",fahr,celsius);
		fahr = fahr + STEP;
	}
	return 0;
}

