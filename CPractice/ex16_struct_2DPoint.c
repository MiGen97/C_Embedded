/**********************************************************************
 * \file        ex16_struct_2DPoint.c
 *
 * \brief       Define a struct for a point in 2D and write a function to calculate the distance between two points.
 * 
 * \description N.A.
 * 
 *
 * \author      Mihail P. (MP)
 * \date        01.VII.2025 07:33PM
 **********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//define struct to point
typedef struct{
    float x;
    float y;
} point;

double calculateDistance(const point a, const point b);

int main(void)
{
    
    //create 2 points with values
    point a={.x=10.0,.y=12.0};
    point b={.x=5.0,.y=10.0};

    //calculate distance
    double d = calculateDistance(a,b);

    //print result
    printf("Distance is %f.\n",d);
    return 0;
}


double calculateDistance(const point a, const point b)
{
    return sqrt( pow(b.x-a.x,2) + pow(b.y-a.y,2) );
}