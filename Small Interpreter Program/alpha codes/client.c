#include"server.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){

    int a = 10;
    float bag = 3.14159;
    char c[] = "Hello!"; 
    insertVar("gg",'i',(void*)&a);
    insertVar("gi",'f',(void*)&bag);
    insertVar("ggi",'s',(void*)&c);
    displayVarList();
    return 0;
}