#include "line.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "parse.h"
#include "parsetree.h"
#include "varlist.h"


line * newLine(char *addline){
  char buffer[200];
  char *pos= addline;
  char *target = buffer;
  line * newline = (line *) malloc(sizeof(line));
  
  if (!isdigit(*pos)){
    printf("Invalid line - must start with line number: %s", addline);
    return NULL;
  }
  while (isdigit(*pos)){
    *(target++)= *(pos++);
  }
  *target = '\0';
  sscanf(buffer,"%d", &(newline->lineno));
  pos++;
  strcpy(newline->instruction, pos);
  newline->next = NULL;
  newline->prev = NULL;
  return newline;
}

line * insertLine(line *list, line *toinsert){
  line *position = list;
  if (!list)
    return toinsert;
  /*less than head of list*/
  if (toinsert->lineno < list->lineno){
    list->prev = toinsert;
    toinsert->next = list;
    return toinsert;
  }

  while (position->next){
     if (position->lineno == toinsert->lineno){
      position->prev->next = toinsert;
      toinsert->next = position->next;
      free(position);
      return list;
     }
     if (position->lineno > toinsert->lineno){
       toinsert->prev = position->prev;
       toinsert->next = position;
       position->prev->next = toinsert;
       position->prev = toinsert;
       return list;
     }
     position = position->next;
  }
  if (position->lineno > toinsert->lineno){
    toinsert->prev = position->prev;
    toinsert->next = position;
    position->prev->next = toinsert;
    position->prev = toinsert;
    return list;
  }
  position->next = toinsert;
  toinsert->prev = position;
  return list;
  
}

void printList(line *head)
{
  while (head){
    printf("%d %s\n", head->lineno, head->instruction);
    head = head->next;
  }
  return;
}

line *executeLine(line *toexec, var *varlist){
  char tmpbuffer[100];
  evaltree *root = NULL;
  char * startpos = NULL;
  root = genNewNode();
  if (!toexec){
    return NULL;
  }
  startpos = toexec->instruction;
  if (strncmp(toexec->instruction, "SET", 3)==0){
      startpos = readVarName(toexec->instruction+4, tmpbuffer);
      //skip equals when parsing
      startpos++;
      //tmpbuffer[strlen(tmpbuffer)-1]= '\0';
      buildTree(startpos, root, 0);
      calcTree(root, varlist);
      setVar(varlist, tmpbuffer, root->result);    
  }
  freeTree(root);
  return toexec->next;
}
