#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "parsetree.h"

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
 
 // printf ("result so far: %d\n", currnode->result);
  return 0;
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
