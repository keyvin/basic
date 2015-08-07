#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "varlist.h"
#include "line.h"
#include "parse.h"
#include "parsetree.h"
#include "executor.h"
/*tree structure.*/



/*creates an empty node*/

/*parses the input and builds the calculation tree*/

/*calculates value of tree*/


int main(int argv, char ** argc){
  char buffer[201];
  char tmpvarname[20];
 
  char *startpos = buffer;
  line *currinstruction = NULL;
  line *list = NULL;
  line *tmp = NULL;
  int setvar=0;
  char *eof = NULL;
  while (1){
    startpos = buffer;
    setvar=0;
    eof = fgets(buffer, 100, stdin);
    if (!eof){
      printf("EOF Encountered. Exiting\n");
      return 0;
    }
    if (strlen(buffer)==1)
      continue;
    buffer[strlen(buffer)-1]= '\0';
    if (!strncmp("EXEC", buffer, 4)){
      //printf("exec encountered\n");
      executor(list, NULL);
    }
    else{
      tmp = newLine(buffer);
      list = insertLine(list, tmp);
      //printList(list);
    }
  }    
  return 0;
}


    

  




