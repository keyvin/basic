#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "varlist.h"
#include "line.h"
/*tree structure.*/
typedef struct EVALTREE {
  int val;
  int result;
  char operator;
  char varname[20];
  struct EVALTREE *left;
  struct EVALTREE *right;
} evaltree;



/*creates an empty node*/
evaltree *genNewNode();
/*parses the input and builds the calculation tree*/
char * buildTree(char *, evaltree *, int);
/*calculates value of tree*/
int calcTree(evaltree *, var *);
void freeTree(evaltree *);
char * readVarName(char *, char *);

int main(int argv, char ** argc){
  char buffer[201];
  char tmpvarname[20];
  var *varlist = createVar();
  char *startpos = buffer;
  evaltree *root = NULL;
  line *list = NULL;
  line *tmp = NULL;
  int setvar=0;
  while (1){
    startpos = buffer;
    root = genNewNode(); 
    setvar=0;
    fgets(buffer, 100, stdin);
    buffer[strlen(buffer)-1]= '\0';
    tmp = newLine(buffer);
    list = insertLine(list, tmp);
    printList(list);
    /*if (strncmp(buffer, "SET", 3)==0){
      startpos = readVarName(buffer+4, tmpvarname);
      //skip equals when parsing
      startpos++;
      setvar=1;
    }
    buffer[strlen(buffer)-1]= '\0';
    buildTree(startpos, root, 0);
    calcTree(root, varlist);
    if (!setvar){
      printf("not setting variable, value of expression:%d\n", root->result);
    }
    else{
      setVar(varlist, tmpvarname, root->result);
    }
    freeTree(root);*/
  }
  
  freeVarList(varlist);
  return 0;
}

char * readVarName(char *input, char *output){
  memset(output, '\0', 0);
  while (isalpha(*input) ){
    *(output++)=*(input++);
  }
  *output = '\0';
  return input;
}
    

int calcTree(evaltree *currnode, var *varlist){
  var *getvar;
  /*descend left branch*/
  if (currnode->left){
    calcTree(currnode->left, varlist);
  }

  /*descend right branch*/
  if (currnode->right){
    calcTree(currnode->right, varlist);
  }

  /*perform appropriate calculation*/
  if (currnode->varname[0]!='\0'){
    getvar= getVar(varlist, currnode->varname);
    if (getvar)
      currnode->result = getvar->value;
    else
      currnode->result = 0;
    return;
  }
  switch (currnode->operator){
    /*leaf node, set result as value*/
    case'\0':
      currnode->result = currnode->val;
      break;
   /*non leafs. Perform appropriate calculation of children*/
    case '+':
      currnode->result = currnode->left->result + currnode->right->result;
      break;
    case '/':
      currnode->result = currnode->left->result / currnode->right->result;
      break;
    case '-':
      currnode->result = currnode->left->result - currnode->right->result;
      break;
    case '*':
      currnode->result = currnode->left->result * currnode->right->result;
      break;
    case '&':
      currnode->result = (currnode->left->result && currnode->right->result) ? 1 :0;
      break;
    case '|':
      currnode->result = (currnode->left->result || currnode->right->result) ?1 :0;
      break;
    case '<':
      currnode->result = (currnode->left->result < currnode->right->result) ? 1:0;
      break;
    case '>':
      currnode->result = (currnode->left->result > currnode->right->result) ?1:0;
      break;
    case '=':
      currnode->result = (currnode->left->result == currnode->right->result) ?1:0;
      break;
    case '^':
      currnode->result = pow(currnode->left->result, currnode->right->result);
      break;
  }
 
  printf ("result so far: %d\n", currnode->result);
  return 0;
}
  



char * buildTree(char *string, evaltree *currnode, int isleftset){
  char buffer[21];
  char *buffpos = buffer;
  char *pos = NULL;
  evaltree *tmptree;
  int leftset = isleftset;
  int val;
  //clear buffer
  memset(buffer, sizeof(char), '\0');
  //test for valid input
  if (string == NULL) return NULL;
  //maybe this would be better as a while
  for (pos = string; *pos!='\0'; pos++){
    //if we are entering a parenthisis
    if (!leftset){
      if (*pos == '('){
	printf("encountered ( on left pair, recursing\n");
	//add new node to left side, set it as current node, and recurse
	currnode->left = genNewNode();
	//still possible to set the left side
	pos = buildTree(pos+1, currnode->left, 0);
      }
      else {
	//not a parenthisis. Read integer into buffer and sscanf it.
	if (isdigit(*pos)){
	  while (isdigit(*pos)){
	    *buffpos++ = *pos++;
	  }
	  *buffpos='\0';
	  sscanf(buffer, "%i", &val);
	  printf("read left val %d\n", val);
	  //create a new leaf on left side to store read value
	  currnode->left = genNewNode();
	  currnode->left->val = val;
	  buffpos=buffer;
	}
	else if (isalpha(*pos)){
	  pos = readVarName(pos, buffer);
	  printf ("read varname %s on left side\n", buffer);
	    currnode->left = genNewNode();
	  strcpy(currnode->left->varname, buffer);
	}
      }
    }
    //advance whitespace. Not needed here
    while (*pos==' '){
      pos++;
    }
    //check for operator
    if (*pos=='*' || *pos=='/' || *pos=='-' || *pos=='+' || *pos=='&' || *pos=='|'||*pos=='^'||*pos=='>'||*pos=='<'||*pos=='='){
      printf("operator %c read\n", *pos);
      //set the current node operator to the read operator
      currnode->operator = *pos;
      //advance position in string
      pos++;
    }
    //skip whitespace
    while (*pos==' '){
      pos++;
    }
    //read right hand side
    if (*pos == '('){
      printf("( encountered, recursing on right tree\n");
      currnode->right = genNewNode();
      //the left side is not set
      pos = buildTree(pos+1, currnode->right, 0);
    }
    else {
      if (isdigit(*pos)){

	while (isdigit(*pos)){
	  *buffpos++ = *pos++;
	}
	*buffpos='\0';
	sscanf(buffer, "%i", &val);
	printf("read right value, %d\n",val);
	currnode->right = genNewNode();
	currnode->right->val = val;
	buffpos=buffer;
      }
      else if (isalpha(*pos)){
	  pos = readVarName(pos, buffer);
	  printf ("read varname %s on right side\n", buffer);
	  currnode->right = genNewNode();
	  strcpy(currnode->right->varname, buffer);
      }
    }
    //ending a level of recursion on the right side. Return
    if (*pos==')'){
      printf(") encountered. Returning from recursion");
      pos++;
      return pos;
    }
    if (*pos=='+'||*pos=='-'||*pos=='/'||*pos=='*'||*pos=='&'||*pos=='|'||*pos=='^'||*pos=='>'||*pos=='<'||*pos=='='){
      //push left
      printf("additional operator. pushing tree left and reparsing");
      tmptree = genNewNode();
      tmptree->left = currnode->left;
      tmptree->operator = currnode->operator;
      tmptree->val = currnode->val;
      tmptree->result = currnode->result;
      tmptree->right = currnode->right;
      currnode->left = tmptree;
      currnode->operator='\0';
      currnode->right = NULL;
      leftset = 1;
      pos--;
    }
    else
      return pos;
    
  }
  //return position
  return pos;
}


evaltree * genNewNode() {
  evaltree *ptr = (evaltree *) malloc(sizeof(evaltree));
  ptr->val = 0;
  ptr->result = 0;
  ptr->operator = '\0';
  ptr->varname[0] = '\0';
  ptr->left = NULL;
  ptr->right = NULL;
  return ptr;
}

void freeTree(evaltree *currnode){
  if (currnode->left)
    freeTree(currnode->left);
  if (currnode->right)
    freeTree(currnode->right);
  if (currnode)
    free(currnode);
  return;
}
