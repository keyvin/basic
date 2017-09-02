//This file has all stdlib, stdio, string, and conversion macros

int my_isdigit(char c){
  if (c >= '0' && c<= '9'){
    return 1;
  }
  return 0;
}

int strlen(char *target){
  int length = 0;
  while (*target != '\0'){
    length++;
    target++;

  }
  return length;
}

int strcmp(char *s1, char *s2){
  int difference = 0;
  difference = *s1 - *s2;
  while (!difference  && (*s1 != '\0') && (s2 != '\0')){
 
      s1++;
      s2++;
      difference = *s1 - *s2;
  }
    
  return difference;
}

int strncmp(char *s1, char *s2, int num)
{
  int difference = 0;
  int cnt = 0;
  difference = *s1 - *s2;
  while ((!difference) && (cnt < num))
  {
    s1++;
    s2++;
    cnt++;
    difference = *s1 - *s2;
    if (*s1 != '\0' || *s2 !='\0')
      break;
  }
  return difference;
}

int strcpy(char *target, char *source){
  while (*source != '\0'){
    *target = *source;
    target++;
    source++;
  }
  return 0;
}

int memset(char *buffer, char fill, int num){
  int a = 0;
  for (a=0; a < num; a++)
    {
      buffer[a] = fill;
    }
  return 0;

}

int strcat(char *target, char *src){
  int len = 0;
  len = strlen(target);
  while(*src != '\0'){
    target[len] = *src;
      src++;
      target++;

  }
  target[len+1] = '\0';
}

void * malloc(int bytes){
  return NULL;
}

void * free(void *){
  return NULL;
}
