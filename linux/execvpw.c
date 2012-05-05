//file name : execvpw.c
//created at: 2012年05月06日 星期日 00时37分50秒
//author:  纪秀峰

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

int main(int argc, char *argv[]){
  char *cmd="find";
  char* const params[]={"find" ,"/tmp","-type" ,"f",NULL};
  execvp(cmd,params);
  return 0;
}
