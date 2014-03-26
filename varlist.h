#define MAX_VAR_LENGTH 20

typedef struct VAR{
  char varname[MAX_VAR_LENGTH];
  int value;
  struct VAR *next;
} var;


var * createVar();
var * getVar(var *, char *);
void setVar(var *, char*, int);
void freeVarlist(var *);

