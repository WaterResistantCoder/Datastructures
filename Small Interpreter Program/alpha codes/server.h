#define MAX_STRING_SIZE 32 //Max size of string
#define debug printf("DEBUG\n")
typedef struct Var{
    char name[11];//Max size 10
    char type;
    void* value;
    struct Var* link;
}var;

var* head;

//Function prototypes

var* createVar(char* name,char type,void* value);
void displayVarList();
void insertVar(char* name,char type,void* value);
