#include"expression_server.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<ctype.h>

char_node * ctop = NULL;
int ccount = 0;

int_node * itop = NULL;
int icount = 0;

//char stack
char char_top(){
    return ctop->data;
}

void char_push(char val){
    if (ctop == NULL)
    {
        ctop =(struct char_node *)malloc(sizeof(struct char_node));
        ctop->link = NULL;
        ctop->data = val;
    }
    else
    {
        char_node* temp =(struct char_node *)malloc(sizeof(struct char_node));
        temp->link = ctop;
        temp->data = val;
        ctop = temp;
    }
    ccount++;
}

void char_pop(){
    char_node* top1 = ctop;
    char a;
    if (top1 == NULL)
    {
        printf("\nempty char_stack");
        return;
    }
    else
    top1 = top1->link;
    //a = itop->data;
    free(ctop);
    ctop = top1;
    ccount--;
    //return a;
}

int char_empty(){
    return ccount;
}

//int stack

int int_top(){
    return itop->data;
}

void int_push(int val){
    if (itop == NULL)
    {
        itop =(struct int_node *)malloc(sizeof(struct int_node));
        itop->link = NULL;
        itop->data = val;
    }
    else
    {
        int_node* temp =(struct int_node *)malloc(sizeof(struct int_node));
        temp->link = itop;
        temp->data = val;
        itop = temp;
    }
    icount++;
}

void int_pop(){
    int_node* top1 = itop;
    int a;
    if (top1 == NULL)
    {
        printf("\empty int_stack");
        return;
    }
    else
    top1 = top1->link;
    //a = itop->data;
    free(itop);
    itop = top1;
    icount--;
    //return a;
}

int int_empty(){    
    return icount;
}

int precedence(char op){ 
    if(op == '+'||op == '-') 
    return 1; 
    if(op == '*'||op == '/') 
    return 2; 
    return 0; 
} 
  
// Function to perform arithmetic operations. 
int applyOp(int a, int b, char op){ 
    switch(op){ 
        case '+': return a + b; 
        case '-': return a - b; 
        case '*': return a * b; 
        case '/': return a / b; 
    } 
} 
  
// Function that returns value of 
// expression after evaluation. 
int evaluate(char* tokens){ 
    int i; 
      
    /*// stack to store integer values. 
    stack <int> values; 
      
    // stack to store operators. 
    stack <char> ops;*/ 
      
    for(i = 0; i < strlen(tokens); i++){ 
          
        // Current token is a whitespace, 
        // skip it. 
        if(tokens[i] == ' ') 
            continue; 
          
        // Current token is an opening  
        // brace, push it to 'ops' 
        else if(tokens[i] == '('){ 
            char_push(tokens[i]); 
        } 
          
        // Current token is a number, push  
        // it to stack for numbers. 
        else if(isdigit(tokens[i])){ 
            int val = 0; 
              
            // There may be more than one 
            // digits in number. 
            while(i < strlen(tokens) &&  
                        isdigit(tokens[i])) 
            { 
                val = (val*10) + (tokens[i]-'0'); 
                i++; 
            } 
              
            int_push(val); 
        } 
          
        // Closing brace encountered, solve  
        // entire brace. 
        else if(tokens[i] == ')') 
        { 
            while(!char_empty() && char_top() != '(') 
            { 
                int val2 = int_top(); 
                int_pop(); 
                  
                int val1 = int_top(); 
                int_pop(); 
                  
                char op = char_top(); 
                char_pop(); 
                  
                int_push(applyOp(val1, val2, op)); 
            } 
              
            // pop opening brace. 
            if(!char_empty()) 
               char_pop(); 
        } 
          
        // Current token is an operator. 
        else
        { 
             
            while(!char_empty() && precedence(char_top()) 
                                >= precedence(tokens[i])){ 
                int val2 = int_top(); 
                int_pop(); 
                  
                int val1 = int_top(); 
                int_pop(); 
                  
                char op = char_top(); 
                char_pop(); 
                  
                int_push(applyOp(val1, val2, op)); 
            } 
              
            // Push current token to 'ops'. 
            char_push(tokens[i]); 
        } 
    } 
      
    // Entire expression has been parsed at this 
    // point, apply remaining ops to remaining 
    // values. 
    while(!char_empty()){ 
        int val2 = int_top(); 
        int_pop(); 
                  
        int val1 = int_top(); 
        int_pop(); 
                  
        char op = char_top(); 
        char_pop(); 
                  
        int_push(applyOp(val1, val2, op)); 
    } 
      
    // Top of 'values' contains result, return it. 
    return int_top(); 
} 