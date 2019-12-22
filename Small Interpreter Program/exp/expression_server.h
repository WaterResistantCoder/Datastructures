typedef struct char_node{
    char data;
    struct char_node * link;
}char_node;

typedef struct int_node{
    int data;
    struct int_node * link;
}int_node;



char char_top();
void char_push(char val);
void char_pop();
int char_empty();

int int_top();
void int_push(int val);
void int_pop();
int int_empty();

int precedence(char op);
int applyOp(int a, int b, char op);
int evaluate(char* tokens);

