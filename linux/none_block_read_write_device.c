#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
/* 对于常规文件是 不会block的 */

/* 对于那些会block的设备
  如果在open一个设备时指定了O_NONBLOCK标志，read/write就不会阻塞。以read为例，
   如果设备暂时没有数据可读就返回-1，同时置errno为EWOULDBLOCK（或者EAGAIN，这两
   个宏定义的值相同），表示本来应该阻塞在这里（would block，虚拟语气），事实上
   并没有阻塞而是直接返回错误，调用者应该试着再读一次（again）。这种行为方式称
   为轮询（Poll），调用者只是查询一下，而不是阻塞在这里死等，这样可以同时监视多
   个设备： */

/* 以下是一个非阻塞I/O的例子。目前我们学过的可能引起阻塞的设备只有终端，所以我
   们用终端来做这个实验。程序开始执行时在0、1、2文件描述符上自动打开的文件就是
   终端，但是没有O_NONBLOCK标志。所以就像例 28.2 “阻塞读终端”一样，读标准输入
   是阻塞的。我们可以重新打开一遍设备文件/dev/tty（表示当前终端），在打开时指定
   O_NONBLOCK标志。 */
#define TRY_MSG "try to read from stdin again\n"
#define HAVE_READED "have read:"
int main(int argc, char *argv[])
{
  int fd ,n;
  char str[10];
  /* /dev/tty代表当前终端 ,以非block的方式重新打开当前终端 */
  fd=  open("/dev/tty",O_RDONLY|O_NONBLOCK); /* read, none_block */
    if(fd<0){
      perror("open /dev/tty ");
    }
 try_again:
  n = read(fd,str,10);
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
