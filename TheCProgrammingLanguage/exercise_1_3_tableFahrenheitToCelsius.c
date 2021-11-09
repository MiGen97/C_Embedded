/******************************************************************
 * \file	exercise_1_3_tableFahrenheitToCelsius.c
 *
 * \brief 	Program that prints the table with temperatures
 *              conversion from Fahrenheit to Celsius.Values from
 *		0F to 300F with a step of 20.
 * 
 * \description	This program makes conversion from Fahrenheit to 
 *              Celsius. Values from 0F to 300F with a step of 20.
 *
 * \author	Mihail P. (MP)
 * \date	09.XI.2021 02:40AM
 * \tag		"The C Programming Language 2nd Edition"
 * 		by Brian W. Kernighan and Dennis M. Ritchie
 * 		Chapter 1, Section 1.2
 * 		page 13, Exercise 1-3
 ******************************************************************/


#include <stdio.h>

/* print Fahrenheit-Celsius table
   for fahr = 0, 20, ..., 300; floating-point version */
int main(void)
{
	float fahr, celsius;
	int lower, upper, step;

	lower = 0;	/* lower limit of temperature table */
	upper = 300;	/* upper limit */
	step = 20;	/* step size */

	fahr = lower;

	/* print table header */
	printf("Fahrenheit | Celsius\n");
	printf("-----------|--------\n");

	while (fahr <= upper)
	{
		celsius = (5.0/9.0) * (fahr-32.0);
		printf("%10.0f | %6.1f\n",fahr,celsius);
		fahr = fahr + step;
	}
	return 0;
}

