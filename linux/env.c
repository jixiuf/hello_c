//file name : env.c
//created at: 2012年12月23日 星期日 23时55分53秒
//author:  纪秀峰

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>


int main(int argc, char *argv[]){
  char* str;
  putenv("key=value");
  str=getenv("key");
  printf ("%s\n",str);
  return 0;
}
