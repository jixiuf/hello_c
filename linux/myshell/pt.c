#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
/* 指针传参 */
mc(char*** str){
  char* s1=(char*)malloc(10);
  char* s2=(char*)malloc(10);
  char* s3=(char*)malloc(10);
  char **ss,**p;
  /* 注意 这里不能进行 s1="hello"进行赋值 */
  strcpy(s1,"hello");
  strcpy(s2,"world");
  strcpy(s3,"god");
  /* printf ("%p,%p,%p\n",&s1,&s2,&s3); */
  printf ("%s,%s,%s\n",s1,s2,s3);
  ss= (char**)calloc(3,sizeof(char*));
  p=ss;
  *p= s1;
  p++;
  *p= s2;
  p++;
  *p= s3;
  p++;
  /* printf ("%p\n",p); */
  *str=ss;
}

int main(int argc, char *argv[]){
  char** str;
  int i;
  mc(&str);
  printf ("%s\n",*str);
  str++;
  printf ("%s\n",*str);
  str++;
  printf ("%s\n",*str);

  return 0;
}
