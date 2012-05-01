//file name : pipe.c
//created at: 2012年05月02日 星期三 01时25分10秒
//author:  纪秀峰

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]){
  int fd[2],c;
  pid_t pid;
  char* str[10];
  if(pipe(fd)<0){
    perror("pipe");
    exit(1);
  }
  if ((pid= fork())<0){
    perror("fork error");
    exit(1);
  }
  if (pid==0){                   /* child process */
    close(fd[1]);
    c=read(fd[0],str,10);
    write(STDOUT_FILENO,str,c);
  }else{                        /* pid>0, parent process */
    close(fd[0]);
    write(fd[1],"hello\n",6);
    wait(NULL);

  }

  return 0;
}

/* #include <unistd.h> */
/* int pipe(int filedes[2]); */
/* 通过read(filedes[0]);或者write(filedes[1]);向这个文件读写数据其实是在读写内核缓冲区 */
