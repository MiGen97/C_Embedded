/**********************************************************************
 * \file        ex23_reverse_words_pointer_arithm.c
 *
 * \brief       Implement a function that reverses the words in a sentence using only pointer arithmetic.
 * 
 * \description N.A.
 * 
 *
 * \author      Mihail P. (MP)
 * \date        02.VII.2025 00:05AM
 **********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverseWords(char* str);
void reverseString(char* start, char* end);

int main(void){
    
    char str[]="This is my sencence and I will reverse it.";

    reverseWords(str);
    printf("%s",str);

    return 0;
}

void reverseWords(char* str){
    //reverse the entire sentence
    char* start=str;
    char* end=str+strlen(str)-1;
    reverseString(start,end);

    //reverse individual words  
    start=str;
    end=start;
    while(*end != '\0'){
        while(*end !=' ' && *end != '\0'){
            end++;
        }
        reverseString(start,end-1);
        end++;
        start=end;
    }
}

void reverseString(char* start, char* end){

    while(start<end){
        char temp = *start;
        *start=*end;
        *end=temp;
        start++;
        end--;
    }
}