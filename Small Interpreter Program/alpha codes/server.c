#include"server.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

var* createVar(char* name,char type,void* value){
    var* temp = (var*)malloc(sizeof(var));
    temp->type = type;
    strcpy(temp->name,name);
    if(type == 'i'){
        temp->value = malloc(sizeof(int));
        *((int*)temp->value) = *((int*)value);
    }
    else if(type == 'f'){
        temp->value = malloc(sizeof(float));
        *((float*)temp->value) = *((float*)value);
    }
    else if(type == 's'){
        temp->value = malloc(MAX_STRING_SIZE);
        strcpy(((char*)temp->value) , ((char*)value));
    }
    else
        return temp->value = NULL;
    
    temp->link = NULL;
    return temp;    
}

void displayVarList(){
    var* temp = head;
    while(temp!=NULL){
        if(temp->type == 'i')
            printf("%d",*((int*)temp->value));
    else if(temp->type == 'f')
            printf("%f",*((float*)temp->value));
    else if(temp->type == 's')
            printf("%s",((char*)temp->value));
    temp = temp->link;
    printf("\n");
    };
}

void insertVar(char* name,char type,void* value){
    var* new = createVar(name,type,value);
    if(head == NULL){
        head = new;
    }
    else{
        new->link = head;
        head = new;
    }


}