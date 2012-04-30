//file name : dup2_test.c
//created at: 2012年04月10日 星期二 23时52分52秒
//author:  纪秀峰

    /* int dup2(int oldfd, int newfd); */
    /*  makes newfd be the copy of oldfd,  */

#include <fcntl.h>
/* #include <stdio.h> */
/* #include <stdlib.h> */
#include <unistd.h>

int main(int argc, char *argv[]){
  /* O_CREAT 如果文件 不存在，创建一新的，  O_RDWR,可读可写*/
  /* S_IRWXU允许文件的属主读写执行 */
  /* S_IRGRP 允许用户所在组读*/
  int fd;
  if ((fd= open("/tmp/out" ,O_CREAT| O_RDWR,S_IRWXU|S_IRGRP))!=-1){
    /* 让STDOUT_FILENO文件描述符写指向fd  */
    /* int dup2(int oldfd, int newfd); */
    /*  makes newfd be the copy of oldfd,  */
    dup2(fd,STDOUT_FILENO);
    write(STDOUT_FILENO,"hello",5);
    /* 之后向STDOUT_FILENO,的写入操作，则写到了/tmp/out文件中了 */
    close(STDOUT_FILENO);
  }
  return 0;
}
