#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
int main(int argc, char *argv[]){
  int fd;
  if(argc<2){
    fprintf (stderr,"using:%s filename\n",argv[0]);
    exit(1);
  }
  fd = open(argv[1],O_RDONLY);
  if(fd<0){
    perror("open filename ");
    exit(1);
  }
  dup2(fd,STDIN_FILENO); /* 经此后，STDIN_FILENO指向fd所指的文件 ,所有从stdin读的数据 实从fd文件 来而*/

  /* 而upper.c中是从 stdin中读数据， */
  /* 用exec后，原来打开的文件描述符仍然是打开的[37]。利用这一点可以实现I/O重定向。
     先看一个简单的例子，把标准输入转成大写然后打印到标准输出 */
  execlp("./upper","upper",NULL );
  perror("exit");
  return 0;
}
