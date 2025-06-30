/**********************************************************************
 * \file        ex4_swap_no_temp.c
 *
 * \brief       Check if a given number is a palindrome using integer arithmetic.
 * 
 * \description N.A.
 * 
 *
 * \author      Mihail P. (MP)
 * \date        30.VI.2025 10:54PM
 **********************************************************************/
#include <stdio.h>
#include <math.h>

#define MAX_LIMIT 100
void checkIsPalindrome(const int number);

int main(void)
{
    int number;

    printf("Enter an integer to check if is palindrome: ");
    if (scanf("%d", &number) == 1) 
    {
        checkIsPalindrome(number);
    }
    else
    {
        printf("Error in geting the input number.\n");
    }
    return 0;
}

void checkIsPalindrome(int number)
{
    if(number > (pow(10,MAX_LIMIT)-1))
    {
        printf("Number to big to be processed by this function.\n");
    }
    else
    {
        //extract digits in an array
        int reversed=0, original=number;
        while (number > 0)
        {
            reversed= reversed*10 + number%10;
            number=number/10;
        }

        if(reversed == original)
            printf("Number is palindrome.\n");
        else
            printf("Number is not palindrome.\n");
    }
}