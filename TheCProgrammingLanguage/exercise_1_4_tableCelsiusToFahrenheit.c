/******************************************************************
 * \file	exercise_1_4_tableCelsiusToFahrenheit.c
 *
 * \brief 	Program that prints the table with temperatures
 *              conversion from Celsius to Fahrenheit.
 * 
 * \description	This program makes conversion from Celsius to Fahrenheit.
 *              Values from 0C to 300C with a step of 20.
 *
 * \author	Mihail P. (MP)
 * \date	09.XI.2021 03:00AM
 * \tag		"The C Programming Language 2nd Edition"
 * 		by Brian W. Kernighan and Dennis M. Ritchie
 * 		Chapter 1, Section 1.2
 * 		page 13, Exercise 1-4
 ******************************************************************/


#include <stdio.h>

/* print Celsius-Fahrenheit table
   for celsius = 0, 20, ..., 300; floating-point version */
int main(void)
{
	float fahr, celsius;
	int lower, upper, step;

	lower = 0;	/* lower limit of temperature table */
	upper = 300;	/* upper limit */
	step = 20;	/* step size */

	celsius = lower;

	/* print table header */
	printf("Celsius | Fahrenheit\n");
	printf("--------|-----------\n");

	while (celsius <= upper)
	{
		fahr = (9.0/5.0)*celsius + 32.0;
		printf("%7.0f | %9.1f\n", celsius, fahr);
		celsius = celsius + step;
	}
	return 0;
}

