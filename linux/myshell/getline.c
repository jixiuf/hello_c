#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "parse_args.h"
#include <fcntl.h>
#include <string.h>

#define PROMPT ">"
#define LINE_MAX_LENGTH 1024


int my_getline(char* line){
  char c ,*p=line;
  int i=0;
  while(((c=fgetc(stdin))!='\n')&&i<LINE_MAX_LENGTH){
    *p=c;
    p++;
    i++;
  }
  *p=0;
  if (i==LINE_MAX_LENGTH){
    return -1;
  }
  return i;
}

int main(int argc, char *argv[]){
  char* line;
  pid_t pid;
  line=malloc(LINE_MAX_LENGTH*sizeof(char));
  fprintf (stderr,"%s",PROMPT);
printf ("%p\n",line);
  while (my_getline(line)!=-1){
    printf ("str=%s,len=%d\n",line,strlen(line));
  }
  fprintf(stderr,"error\n");
  exit(1);

  return 0;
}
