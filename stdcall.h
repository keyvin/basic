#ifndef STDCALL
#define STDCALL 1

#ifdef  freestanding 
#define isdigit my_isdigit 
#define isalpha my_isalpha
int my_isdigit(char);
int strcmp(char *, char *);
int strncmp(char *, char *, int);
int strcpy(char *, char *);
int memset(char *, char, int);
int strlen(char *);
int strcat(char*, char*);
int my_free(void *);
int my_malloc(size_t);

void *memory_block;
unsigned int read_int(char *);
int inttoa(int, char *);
int my_isalpha(char);
#else
#include <string.h>
#endif


#endif
