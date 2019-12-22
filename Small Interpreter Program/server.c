#include"server.h"
#include"a.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int isDigit(char* a){
    for(int i=0;a[i]!='\0';i++){
        if(a[i]<48 || a[i]>57)
            return 0;
    }
    return 1;
}

void main_init(char* keyVals[])
{
   
        if(keyEnd == 1){
            print_err("INVALID SYNTAX");
            return;
        }
        if(strcmp(keyVals[keyBeg + 0],"if") == 0){
            if_eval(keyVals);
        }else if(strcmp(keyVals[keyBeg + 0],"times") == 0){
            times_eval(keyVals);
        }else if(strcmp(keyVals[keyBeg + 1],"=") == 0){
            expression_eval(keyVals);
        }else if(strcmp(keyVals[keyBeg + 0],"print") == 0){
            print_value(keyVals);
        }else {
            print_err("INVALID SYNTAX");
        } 
}
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
    }
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

int isPresent(char* name){
    if(head!=NULL){
        var* temp = head;
        while(temp!=NULL){
            if(!strcmp(temp->name,name)){
                return 1;
            }
            temp = temp->link;
        }
    }
    return 0;
}

var* getValue(char* variable){
    var* temp = head;
    while(temp!=NULL){
        if(strcmp(temp->name,variable) == 0){
            return temp;
        }
    temp = temp->link;
    }
    return NULL;
}

void expression_eval(char* keyVals[]){
    char type = 'e';
    char pofx[50];
    
    var* temp = getValue(keyVals[keyBeg + 2]);
    
    if(temp == NULL){
        if((atoi(keyVals[keyBeg + 2]) != 0) && keyVals[keyBeg + 2][0] != '0'){
            type = 'r';
        }
        if((atoi(keyVals[keyBeg + 2]) == 0) && keyVals[keyBeg + 2][0] == '0'){
            type = 'r';
        }
        for(int k = 0; keyVals[keyBeg + 2][k] != '\0';k++){
            if(keyVals[keyBeg + 2][k] == '.'){
                type = 'f';
                break;
            }
            if(keyVals[keyBeg + 2][k] == '+'){
                type = 'i';
            }
        }
        if(type == 'i'){
        infix_to_postfix(keyVals[keyBeg + 2], pofx);
        top_1();
        int value = eval_postfix(pofx);
        insertVar(keyVals[keyBeg + 0],'i',(void*)&value);
        }
        else if(type == 'f'){
        float z = atof(keyVals[keyBeg + 2]);
        insertVar(keyVals[keyBeg + 0],'f',(void*)&z);
        }else if(type == 'r'){
            int v = atoi(keyVals[keyBeg + 2]);
            insertVar(keyVals[keyBeg + 0],'i',(void*)&v);
        }else{
            print_err("UNKNOWN VARIABLE");
        }
    }else{
        if(temp->type == 'i')
            insertVar(keyVals[keyBeg + 0],'i',(temp->value));
    else if(temp->type == 'f')
            insertVar(keyVals[keyBeg + 0],'f',(temp->value));
    else if(temp->type == 's')
            insertVar(keyVals[keyBeg + 0],'s',(temp->value));
    }
}

void print_err(char* err){
    printf("***%s***\n",err);
}

int comparision_evaluation(char* a,char* b,char* c){
    if(strcmp(b,"<") == 0){
        return atoi(a) < atoi(c);
    }else if(strcmp(b,">") == 0){
        return atoi(a) > atoi(c);
    }else if(strcmp(b,"<=") == 0){
        return atoi(a) <= atoi(c);
    }else if(strcmp(b,">=") == 0){
        return atoi(a) >= atoi(c);
    }else if(strcmp(b,"==") == 0){
        return atoi(a) == atoi(c);
    }else if(strcmp(b,"!=") == 0){
        return atoi(a) != atoi(c);
    }else print_err("COMPARISION ERROR");
    return 0;
}

void if_eval(char* keyVals[]){
    int flag = comparision_evaluation(keyVals[keyBeg + 1],keyVals[keyBeg + 2],keyVals[keyBeg + 3]);
    if(strcmp(keyVals[keyBeg + 4],"then") == 0){
        if(flag){
        keyBeg = keyBeg + 5;
        main_init(keyVals);
        }
    }else {
        print_err("SYNTAX ERROR");
    }
}

void times_eval(char* keyVals[]){
    
    if(atoi(keyVals[keyBeg + 1]) != 0){

        int time = atoi(keyVals[keyBeg + 1]);
            keyBeg = 2;

        for(int i = 0;i < time;i++){
            main_init(keyVals);
        }
    }else{
        print_err("TIMES VALUE ERROR");
    }
}

void print_value1(char* keyVals[]){

    if(isDigit(keyVals[keyBeg + 1])){
        printf("%d\n",atoi(keyVals[keyBeg + 1]));
    }else{
        var* temp = getValue(keyVals[keyBeg + 1]);
        if(temp != NULL){
            if(temp->type == 'i')
                    printf("%d\n",*((int*)temp->value));
            else if(temp->type == 'f')
                    printf("%f\n",*((float*)temp->value));
            else if(temp->type == 's')
                    printf("%s\n",((char*)temp->value));
        }else{
            print_err("UNKNOWN VARIABLE");
        }
    }
}
void print_value(char* keyVals[]){
    char type = 'e';
    char pofx[50];
    var* temp = getValue(keyVals[keyBeg + 1]);
    
    if(temp == NULL){
        if((atoi(keyVals[keyBeg + 1]) != 0) && keyVals[keyBeg + 1][0] != '0'){
            type = 'r';
        }
        if((atoi(keyVals[keyBeg + 1]) == 0) && keyVals[keyBeg + 1][0] == '0'){
            type = 'r';
        }
        for(int k = 0; keyVals[keyBeg + 1][k] != '\0';k++){
            if(keyVals[keyBeg + 1][k] == '.'){
                type = 'f';
                break;
            }
            if(keyVals[keyBeg + 1][k] == '+'){
                type = 'i';
            }
        }
        if(type == 'i'){
        infix_to_postfix(keyVals[keyBeg + 1], pofx);
        top_1();
        int value = eval_postfix(pofx);
        printf("%d\n",value);
        }
        else if(type == 'f'){
        float z = atof(keyVals[keyBeg + 1]);
        printf("%f\n",z);
        }else if(type == 'r'){
            int v = atoi(keyVals[keyBeg + 1]);
            printf("%d\n",v);
        }else{
            print_err("UNKNOWN VARIABLE");
        }
    }else {
            if(temp->type == 'i')
                    printf("%d\n",*((int*)temp->value));
            else if(temp->type == 'f')
                    printf("%f\n",*((float*)temp->value));
            else if(temp->type == 's')
                    printf("%s\n",((char*)temp->value));
    }
}