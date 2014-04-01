#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "parse.h"
#include "varlist.h"
#include "parsetree.h"

char * readVarName(char *input, char *output){
  memset(output, '\0', 0);
  while (isalpha(*input) ){
    *(output++)=*(input++);
  }
  *output = '\0';
  return input;
}

int isoperator(char a){
  if (a=='*' || a=='/' || a=='-' || a=='+' || a=='&' || a=='|'||a=='^'||a=='>'||a=='<'||a=='='){
    return 1;
  }
  return 0;
}


int noOperator(char *pos){
  char *currchar=pos;
  /*only check to first ) because that is the end to the recursion*/
  for (currchar; *currchar!='\0'&&*currchar!=')'; currchar++){
    if (isoperator(*currchar))
      return 0;
  }
  return 1;
}
	

char * buildTree(char *string, evaltree *currnode, int isleftset){
  char buffer[21];
  char *buffpos = buffer;
  char *pos = NULL;
  evaltree *tmptree;
  int leftset = isleftset;
  int val=0;
  int noop=0;
  //clear buffer
  memset(buffer, sizeof(char), '\0');
  //test for valid input
  if (string == NULL) return NULL;
  //maybe this would be better as a while
  for (pos = string; *pos!='\0'; pos++){
    //if we are entering a parenthisis
    if (!leftset){
     
      if (*pos == '('){
	//printf("encountered ( on left pair, recursing\n");
	//add new node to left side, set it as current node, and recurse
	currnode->left = genNewNode();
	//still possible to set the left side
	pos = buildTree(pos+1, currnode->left, 0);
      }
      else {
	//not a parenthisis. Read integer into buffer and sscanf it.
	noop = noOperator(pos);
	//printf("Value of noop is %d\n", noop);
	if (isdigit(*pos)){
	  while (isdigit(*pos)){
	    *buffpos++ = *pos++;
	  }
	  *buffpos='\0';
	  sscanf(buffer, "%i", &val);
	  //printf("read left val %d\n", val);
	  //create a new leaf on left side to store read value
	  if (noop){
	    currnode->val = val;
	    return pos;
	  }
	  currnode->left = genNewNode();
	  currnode->left->val = val;
	  buffpos=buffer;
	}
	else if (isalpha(*pos)){
	  pos = readVarName(pos, buffer);
	  //printf ("read varname %s on left side\n", buffer);
	  if (noop){
	    strcpy(currnode->varname, buffer);
	    return pos;
	  }
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
      //printf("operator %c read\n", *pos);
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
      //printf("( encountered, recursing on right tree\n");
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
	//printf("read right value, %d\n",val);
	currnode->right = genNewNode();
	currnode->right->val = val;
	buffpos=buffer;
      }
      else if (isalpha(*pos)){
	  pos = readVarName(pos, buffer);
	  //printf ("read varname %s on right side\n", buffer);
	  currnode->right = genNewNode();
	  strcpy(currnode->right->varname, buffer);
      }
    }
    //ending a level of recursion on the right side. Return
    if (*pos==')'){
      //printf(") encountered. Returning from recursion");
      pos++;
      return pos;
    }
    if (*pos=='+'||*pos=='-'||*pos=='/'||*pos=='*'||*pos=='&'||*pos=='|'||*pos=='^'||*pos=='>'||*pos=='<'||*pos=='='){
      //push left
      //printf("additional operator. pushing tree left and reparsing");
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
