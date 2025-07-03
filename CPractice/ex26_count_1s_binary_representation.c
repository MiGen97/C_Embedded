/**********************************************************************
 * \file        ex26_count_1s_binary_representation.c
 *
 * \brief       Write a function that counts the number of 1s in the binary representation of an integer.
 * 
 * \description N.A.
 * 
 *
 * \author      Mihail P. (MP)
 * \date        03.VII.2025 08:05PM
 **********************************************************************/
#include <stdio.h>

#define MASK_BIT0 ((int)1)

int main(void){
    int number=1234567890;
    int nbOnes=0;
    while(number>0){
        nbOnes+=number&MASK_BIT0;
        number>>=1;
    }

    printf("Number of ones: %d.\n",nbOnes);
    return 0;
}