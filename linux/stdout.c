//file name : stdout.c
//created at: 2012年04月30日 星期一 18时48分28秒
//author:  纪秀峰

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#include <unistd.h>
#include <fcntl.h>

/* 由open返回的文件描述符一定是该进程尚未使用的最小描述符。由于程序启动时自动打
   开文件描述符0、1、2，因此第一次调用open打开文件通常会返回描述符3，再调用
   open就会返回4。可以利用这一点在标准输入、标准输出或标准错误输出上打开一个新
   文件，实现重定向的功能。例如，首先调用close关闭文件描述符1，然后调用open打开
   一个常规文件，则一定会返回文件描述符1，这时候标准输出就不再是终端，而是一个
   常规文件了，再调用printf就不会打印到屏幕上，而是写到这个文件中了。后面要讲的
   dup2函数提供了另外一种办法在指定的文件描述符上打开文件。 */

int main(int argc, char *argv[]){
  close(STDOUT_FILENO);         /* close stdout  */
  open("/tmp/stdout.out",O_WRONLY|O_CREAT);
  printf ("hello\n");
  return 0;
}
