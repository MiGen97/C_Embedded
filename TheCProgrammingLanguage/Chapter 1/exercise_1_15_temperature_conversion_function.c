/**********************************************************************
 * \file	exercise_1_15_temperature_conversion_function.c
 *
 * \brief 	Program that prints the table with temperatures
 *          conversion from Fahrenheit to Celsius.Values from
 *			0F to 300F with a step of 20. Using a function.
 *
 * \description	N.A.
 *
 *
 * \author	Mihail P. (MP)
 * \date	15.III.2023 08:25PM
 * \tag		"The C Programming Language 2nd Edition"
 * 		by Brian W. Kernighan and Dennis M. Ritchie
 * 		Chapter 1, Section 1.8
 * 		page 27, Exercise 1-15
 **********************************************************************/


#include <stdio.h>

float convertFahrenheitToCelsius(float fahrenheitValue);

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
		celsius = convertFahrenheitToCelsius(fahr);
		printf("%10.0f | %6.1f\n",fahr,celsius);
		fahr = fahr + step;
	}
	return 0;
}

float convertFahrenheitToCelsius(float fahrenheitValue)
{
	return ((5.0/9.0) * (fahrenheitValue-32.0));
}
