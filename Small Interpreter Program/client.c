#include"server.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

/*
    no string datatype :(

    if comprassion then execute statement

    times value : execute statement

    variable = expression

    print variable
*/


int main(){
    char buffer[500];
    char* keyVals[10];
    

    while(1){

        int a=0;
        keyBeg = 0;
        printf(">>");
        while((buffer[a]=getchar())!='\n'){
            a++;
        }
        buffer[a]='\0';
        if(strcmp(buffer,"exit") == 0)
            break;
        keyVals[keyBeg + 0] = strtok(buffer," ");
        keyEnd=1;

        while((keyVals[keyEnd] = strtok(NULL," ")) != NULL){

            keyEnd++;
        }
        main_init(keyVals);
    }
    return 0;
}