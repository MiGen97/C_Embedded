/**********************************************************************
 * \file        ex28_reverse_bits_of_uint.c
 *
 * \brief       Reverse the bits of an unsigned integer.
 * 
 * \description N.A.
 *
 * \author      Mihail P. (MP)
 * \date        03.VII.2025 08:20PM
 **********************************************************************/
#include <stdio.h>

unsigned int reverseBits(unsigned int number);
void printBitsOfNumber(unsigned int number);

int main(void){
    unsigned int number = 20;
    unsigned int numberReversed = reverseBits(number);

    printBitsOfNumber(number);
    printBitsOfNumber(numberReversed);
    return 0;
}

unsigned int reverseBits(unsigned int number){
    unsigned int reversed = 0;
    int numberBits = sizeof(unsigned int) * 8;
    for(int i=0; i< numberBits; i++){
        reversed<<=1;
        reversed|= (number & 1);
        number>>=1;
    }
    return reversed;
}

void printBitsOfNumber(unsigned int number){
    int numberBits = sizeof(unsigned int) * 8;
    printf("Number %d have the representation on bits:\n",number);
    for(int i=numberBits-1; i >= 0; i--){
        printf("%d",(number>>i)&1);
        if (i % 8 == 0 && i != 0) printf(" ");
    }
    printf("\n");
}