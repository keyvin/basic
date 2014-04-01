#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "varlist.h"
#include "line.h"
#include "parse.h"
#include "parsetree.h"
/*tree structure.*/



/*creates an empty node*/

/*parses the input and builds the calculation tree*/

/*calculates value of tree*/


int main(int argv, char ** argc){
  char buffer[201];
  char tmpvarname[20];
  var *varlist = createVar();
  char *startpos = buffer;
  line *currinstruction = NULL;
  line *list = NULL;
  line *tmp = NULL;
  int setvar=0;
  while (1){
    startpos = buffer;
    setvar=0;
    fgets(buffer, 100, stdin);
    buffer[strlen(buffer)-1]= '\0';
    if (!strncmp("EXEC", buffer, 4)){
      printf("exec encountered\n");
      currinstruction = executeLine(list, varlist);
      while (currinstruction){
	printf("in instruction %d \n", currinstruction->lineno);
	currinstruction = executeLine(currinstruction, varlist);
      }
    }
    else{
      tmp = newLine(buffer);
      list = insertLine(list, tmp);
      printList(list);
    }
  }    
  freeVarList(varlist);
  return 0;
}


    

  




