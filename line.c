#include "line.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
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

