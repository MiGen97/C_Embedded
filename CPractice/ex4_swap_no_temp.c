/**********************************************************************
 * \file        ex4_swap_no_temp.c
 *
 * \brief       Swap two integers using a function and pointers (no temporary variable).
 * 
 * \description N.A.
 * 
 *
 * \author      Mihail P. (MP)
 * \date        30.VI.2025 10:45PM
 **********************************************************************/
#include <stdio.h>

 void swap(int* a, int* b);

 int main(void)
 {
    int x,y;

    printf("Enter two integers: ");
    if (scanf("%d %d", &x, &y) == 2) {
        printf("Before swap: x = %d, y = %d\n", x, y);
        swap(&x, &y);
        printf("After  swap: x = %d, y = %d\n", x, y);
    } else {
        printf("Invalid input.\n");
    }

    return 0;
 }

 void swap(int* a, int* b)
 {
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
 }