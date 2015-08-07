#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "parsetree.h"
#include <string.h>
/*I may need to define some error codes*/
/*They could be stored in the int value of an undefined node*/

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
  /*A variable containing element of the tree will always be a leaf*/
  /*look up value and set it. */
  if (currnode->varname[0]!='\0'){
    getvar= getVar(varlist, currnode->varname);
    if (getvar)
      currnode->result = getvar->val;
    else {
	currnode->result.value.i = 0;
	currnode->result.type = undefined;
    }
    return 0;
  }
  vartype ltype = currnode->left->result.type;
  vartype rtype = currnode->right->result.type;
  varval *lval = &(currnode->left->result.value);
  varval *rval = &(currnode->right->result.value);
  
  switch (currnode->operator){
    /*leaf node, set result as value*/
    case'\0':
      currnode->result = currnode->val;
      break;
   /*non leafs. Perform appropriate calculation of children based on type*/
    case '+':
      if (ltype == integer && rtype == integer){
	currnode->result.value.i = lval->i + rval->i;
	currnode->result.type = integer;
      }
      else if (ltype == integer && rtype == floating){
	currnode->result.type = integer;
	currnode->result.value.i = lval->i + (int) rval->f;
      }
      else if (ltype == floating && rtype == integer){
	currnode->result.type = integer;
	currnode->result.value.i = (int) lval->f + rval->i;
      }
      else if (ltype == floating && rtype == floating){
	currnode->result.type = floating;
	currnode->result.value.f = lval->f + rval->f;
      }
      else if (ltype == string && rtype == string){
	currnode->result.value.s = malloc(strlen(lval->s)+strlen(rval->s)+1);
	strcpy(currnode->result.value.s, lval->s);
	strcat(currnode->result.value.s, rval->s);
      }
      else {
	currnode->result.value.i = 0;
	currnode->result.type = undefined;
      }
      break;
    case '/':
      if (ltype == integer && rtype == integer){
	currnode->result.value.i = lval->i / rval->i;
	currnode->result.type = integer;
      }
      else if (ltype == integer && rtype == floating){
	currnode->result.type = integer;
	currnode->result.value.i = lval->i / (int) rval->f;
      }
      else if (ltype == floating && rtype == integer){
	currnode->result.type = integer;
	currnode->result.value.i = (int) lval->f / rval->i;
      }
      else if (ltype == floating && rtype == floating){
	currnode->result.type = floating;
	currnode->result.value.f = lval->f / rval->f;
      }
      else {
	currnode->result.value.i = 0;
	currnode->result.type = undefined;
      }

      break;
    case '-':
      if (ltype == integer && rtype == integer){
	currnode->result.value.i = lval->i - rval->i;
	currnode->result.type = integer;
      }
      else if (ltype == integer && rtype == floating){
	currnode->result.type = integer;
	currnode->result.value.i = lval->i - (int) rval->f;
      }
      else if (ltype == floating && rtype == integer){
	currnode->result.type = integer;
	currnode->result.value.i = (int) lval->f - rval->i;
      }
      else if (ltype == floating && rtype == floating){
	currnode->result.type = floating;
	currnode->result.value.f = lval->f - rval->f;
      }
      else {
	currnode->result.value.i = 0;
	currnode->result.type = undefined;
      }
      break;
    case '*':
      if (ltype == integer && rtype == integer){
	currnode->result.value.i = lval->i * rval->i;
	currnode->result.type = integer;
      }
      else if (ltype == integer && rtype == floating){
	currnode->result.type = integer;
	currnode->result.value.i = lval->i * (int) rval->f;
      }
      else if (ltype == floating && rtype == integer){
	currnode->result.type = integer;
	currnode->result.value.i = (int) lval->f * rval->i;
      }
      else if (ltype == floating && rtype == floating){
	currnode->result.type = floating;
	currnode->result.value.f = lval->f * rval->f;
      }
      else {
	currnode->result.value.i = 0;
	currnode->result.type = undefined;
      }

      break;
    case '&':
      currnode->result.value.i = (currnode->left->result.value.i && currnode->right->result.value.i) ? 1 :0;
      currnode->result.type = integer;
      break;
    case '|':
      currnode->result.value.i = (currnode->left->result.value.i || currnode->right->result.value.i) ?1 :0;
      currnode->result.type = integer;
      break;
    case '<':
      currnode->result.value.i = (lval->i < rval->i) ? 1:0;
      currnode->result.type = integer;
      break;
    case '>':
      currnode->result.value.i = (lval->i > rval->i) ?1:0;
      currnode->result.type = integer;
      break;
    case '=':
      currnode->result.value.i = (lval->i == rval->i) ?1:0;
      currnode->result.type = integer;
      break;
    case '^':
      currnode->result.value.i = pow(lval->i, rval->i);
      currnode->result.type = integer;
      break;
  }
 
 // printf ("result so far: %d\n", currnode->result);
  return 0;
}



evaltree * genNewNode() {
  evaltree *ptr = (evaltree *) malloc(sizeof(evaltree));
  ptr->val.type = integer;
  ptr->val.value.i = 0;
  ptr->result.value.i = 0;
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
  if (currnode) {
    if (currnode->val.type == string && currnode->val.value.s)
      free (currnode->val.value.s);
    if (currnode->result.type == string && currnode->result.value.s)
      free(currnode->result.value.s);
    free(currnode);
  }
  return;
}
