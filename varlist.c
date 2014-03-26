#include "varlist.h"
#include <stdlib.h>
#include <string.h>

var * createVar(){
  var *newvar = (var *) malloc(sizeof(var));
  memset(newvar->varname, '\0', MAX_VAR_LENGTH);
  newvar->value = 0;
  newvar->next = NULL;
}

var * getVar(var *head, char *varname){  
  var *list = NULL;
  if (!head)
    return NULL;
  for (list=head; list!=NULL; list=list->next){
    if (strcmp(list->varname, varname)==0)
      return list;
  }
  return NULL;
}

//if first element of list is empty, assign a value to first element
void setVar(var *head, char *varname, int value){
  var * existing = NULL;
  
  if (head->varname[0]=='\0'){
    strcpy( head->varname, varname );
    head->value = value;
    head->next = NULL;
    return;
  }

  if (existing = getVar(head, varname)){
    existing->value = value;
    return;
  }
  
  existing = createVar();
  strcpy( existing->varname, varname );
  existing->value = value;
  existing->next = NULL;
  while (head->next != NULL){
    head = head->next;
  }
  head->next = existing;
  return;
}

void freeVarList(var *head){
  var *tmp= NULL;
  while (head!=NULL)
  {
    tmp = head->next;
    free(head);
    head = tmp;
  }
  return;
}
      
  
  
