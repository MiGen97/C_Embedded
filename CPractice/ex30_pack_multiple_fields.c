/**********************************************************************
 * \file        ex30_pack_multiple_fields.c
 *
 * \brief       Pack and unpack multiple fields (e.g., 3-bit and 5-bit fields) into a single unsigned char.
 * 
 * \description N.A.
 *
 * \author      Mihail P. (MP)
 * \date        03.VII.2025 09:09PM
 **********************************************************************/
#include <stdio.h>
#include <stdlib.h>

#define CLASS_BITSIZE 3
#define STUDENTS_BITSIZE 5
#define NB_DAYS 5

#define PACK(classNb, studentsNb) ((classNb) | ((studentsNb) << 3))
#define UNPACK_CLASS(packedData) ((packedData) & 0x07)
#define UNPACK_STUDENTS(packedData) (( (packedData) >> 3 ) & 0x1F)

int main(void){

    unsigned char studentsInClass [NB_DAYS] = {0};

    for(int i=0; i < NB_DAYS; i++){
        unsigned char classNb = rand()%8;
        unsigned char studentsNb = rand()%32;
        studentsInClass[i]=PACK(classNb, studentsNb);
        printf("In class %d, are currently %d students.\n",classNb, studentsNb);
        printf("Packed value is %d .\n",studentsInClass[i]);
    }

    for(int i=0; i < NB_DAYS; i++){
        printf("Unpacked values: In class %d, are currently %d students.\n",UNPACK_CLASS(studentsInClass[i]), UNPACK_STUDENTS(studentsInClass[i]));
    }

    return 0;
}