/**********************************************************************
 * \file        ex27_power_of_2_bitwise.c
 *
 * \brief       Check if a number is a power of two using bitwise operators.
 * 
 * \description N.A.
 *
 * \author      Mihail P. (MP)
 * \date        03.VII.2025 08:14PM
 **********************************************************************/
#include <stdio.h>

int isPowerOf2(int number);

int main(void){
    int number=7;

    printf("Number %d is %spower of 2.\n",number,isPowerOf2(number)?"":"not ");
    return 0;
}


int isPowerOf2(int number){
    while(number>0){
        if(number&1 == 1) return 0;
        number>>=2;
    }
    return 1;
}