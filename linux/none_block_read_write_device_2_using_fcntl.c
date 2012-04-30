#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#define TRY_MSG "try to read from stdin again\n"
#define HAVE_READED "have read:"
/*先看 none_block_read_write_device.c */
/* 先行是用open 重新打开一遍 stdin ,来改变一些参数，
   此处用fcntl 里的函数，来改变 文件描述符的值
 */
int main(int argc, char *argv[])
{
  int n,flags;
  char str[10];
  flags=fcntl(STDIN_FILENO,F_GETFL); /* 注意 ，这里是 F_GETFL,而不是F_GETFD*/
  flags |=O_NONBLOCK;           /* 添加 none_block属性 */
  if(fcntl(STDIN_FILENO,F_SETFL,flags)<0){
    perror("fcntl set flag ");
    exit(1);
  }
 try_again:
  n = read(STDIN_FILENO,str,10);
  if(n<0){
    if (EAGAIN==errno ){
      write(STDOUT_FILENO,TRY_MSG,strlen(TRY_MSG));
      sleep(1);
      goto try_again;
    }else{
      perror("read /dev/tty error");
      exit(1);
    }
  }
  write(STDOUT_FILENO,HAVE_READED,strlen(HAVE_READED));
  write(STDOUT_FILENO,str,n);
  return 0;
}
