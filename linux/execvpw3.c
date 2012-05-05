//file name : execvpw.c
//created at: 2012年05月06日 星期日 00时37分50秒
//author:  纪秀峰

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

int main(int argc, char *argv[]){
  char *cmd="find";
  char *p1,*p2,*p3,*p4;
  char**  params;

  p1=(char*)malloc(5);
  strcpy(p1,"find");

  p2=(char*)malloc(5);
  strcpy(p2,"/tmp");

  p3=(char*)malloc(6);
  strcpy(p3,"-type");

  p4=(char*)malloc(2);
  strcpy(p4,"f");

  params=(char**) malloc(5* sizeof(char*));

  params[0]=p1;
  params[1]=p2;
  params[2]=p3;
  params[3]=p4;
  params[4]=NULL;

  execvp(cmd,params);
  return 0;
}
