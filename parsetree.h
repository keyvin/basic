#ifndef PARSETREE
#define PARSETREE 1
#include "varlist.h"

typedef struct EVALTREE {
  int val;
  int result;
  char operator;
  char varname[20];
  struct EVALTREE *left;
  struct EVALTREE *right;
} evaltree;


int calcTree(evaltree *, var *);
void freeTree(evaltree *);
evaltree *genNewNode();
#endif
