//file name : si.c
//created at: Fri Dec 20 00:23:20 2013
//author:  纪秀峰

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
  char  array[]="hello";
  char * str=array;
  void *p = malloc(100);
  printf("%lu\n",sizeof("hello")); /* =6  字符数组的大小， 包括后面附的字符结束符0 */
  printf("%lu\n",sizeof(array));   /* =6 */
  printf("%lu\n",sizeof(str)); /* =8 on x64, 4 on x86 指针的大小 ，跟char类型无关*/
  printf("%lu\n",sizeof(p));   /* =8 on x64, 4 on x86 指针的大小 */
  return 0;
}
