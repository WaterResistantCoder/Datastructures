#define SIZE 50 /* Size of Stack */

void RemoveSpaces(char* source);
void push(char elem);
char pop(); 
int pr(char elem);
void infix_to_postfix(char *infix, char *postfix); 
int eval_postfix(char *postfix);
void top_1();