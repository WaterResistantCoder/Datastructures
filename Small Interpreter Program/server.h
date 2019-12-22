#define MAX_STRING_SIZE 32 //Max size of string
#define debug printf("DEBUG\n")
typedef struct Var{
    char name[11];//Max size 10
    char type;
    void* value;
    struct Var* link;
}var;

var* head;
int keyEnd;
int keyBeg;

//Function prototypes

void main_init(char* keyVals[]);
var* createVar(char* name,char type,void* value);
void displayVarList();
var* getValue(char* variable);
void insertVar(char* name,char type,void* value);
int isPresent(char* name);
void print_err(char* err);
void if_eval(char* keyVals[]);
int comparision_evaluation(char* a,char* b,char* c);
void times_eval(char* keyVals[]);
void expression_eval(char* keyVals[]);
void print_value(char* keyVals[]);

