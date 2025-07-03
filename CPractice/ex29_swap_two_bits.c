/**********************************************************************
 * \file        ex29_swap_two_bits.c
 *
 * \brief       Implement a function to swap two bits at given positions.
 * 
 * \description N.A.
 *
 * \author      Mihail P. (MP)
 * \date        03.VII.2025 08:39PM
 **********************************************************************/
#include <stdio.h>

void printBinary(const unsigned int number);
unsigned int swapBits(unsigned int number, const int pos1, const int pos2);

 int main(void){
    unsigned int number=2;
    unsigned int pos1=0,pos2=1;

    unsigned int numberSwapped = swapBits(number,pos1,pos2);

    printBinary(number);
    printBinary(numberSwapped);

    return 0;
}

unsigned int swapBits(unsigned int number, const int pos1, const int pos2){
    // Only swap if bits differ
    if (((number >> pos1) & 1u) != ((number >> pos2) & 1u)) {
        number ^= (1u << pos1) | (1u << pos2);
    }
    return number;
}

void printBinary(const unsigned int number){
    int numberBits = sizeof(unsigned int) * 8;
    for(int i= numberBits-1; i >= 0; i--){
        printf("%d",(number>>i)&1);
        if(( i % 8 == 0) && (i != 0)) printf(" ");
    }
    printf("\n");
}