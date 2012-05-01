//file name : mmap_test.c
//created at: 2012年04月30日 星期一 23时09分55秒
//author:  纪秀峰

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
/* mmap可以把磁盘文件的一部分直接映射到内存，这样文件中的位置直接就有对应的内存
   地址，对文件的读写可以直接用指针来做而不需要read/write函数。 */

/* #include <sys/mman.h> */
/*  void *mmap(void *addr, size_t len, int prot, int flag, int filedes, off_t off); */
/*  int munmap(void *addr, size_t len); */


/* 如果addr参数为NULL，内核会自己在进程地址空间中选择合适的地址建立映射。如果
   addr不是NULL，则给内核一个提示，应该从什么地址开始映射，内核会选择addr之上的
   某个合适的地址开始映射。建立映射后，真正的映射首地址通过返回值可以得到。len
   参数是需要映射的那一部分文件的长度。off参数是从文件的什么位置开始映射，必须
   是页大小的整数倍（在32位体系统结构上通常是4K）。filedes是代表该文件的描述符。
    */

/* prot参数有四种取值： */
/*     PROT_EXEC表示映射的这一段可执行，例如映射共享库 */
/*     PROT_READ表示映射的这一段可读 */
/*     PROT_WRITE表示映射的这一段可写 */
/*     PROT_NONE表示映射的这一段不可访问 */

/* flag参数有很多种取值，这里只讲两种，其它取值可查看mmap(2) */
/*     MAP_SHARED多个进程对同一个文件的映射是共享的，一个进程对映射的内存做了修
       改，另一个进程也会看到这种变化。 */
/*     MAP_PRIVATE多个进程对同一个文件的映射不是共享的，一个进程对映射的内存做
       了修改，另一个进程并不会看到这种变化，也不会真的写到文件中去。 */

/* 如果mmap成功则返回映射首地址，如果出错则返回常数MAP_FAILED。当进程终止时，该
   进程的映射内存会自动解除，也可以调用munmap解除映射。munmap成功返回0，出错返
   回-1。 */
#define LENGTH 6
int main(int argc, char *argv[]){
  int fd;
  int *p;
  fd=open("/tmp/a.dat",O_RDWR); /* 事先要存在此文件，文件中最好有内容 ，以便查看 mmap的效果 */
  if(fd<0){
    perror("open /tmp/a.dat");
    exit(1);
  }
  p=  mmap(NULL,LENGTH,PROT_WRITE,MAP_SHARED,fd,0);
  if(p==MAP_FAILED){
    perror("mmap /tmp/a.dat");
    exit(1);
  }

  close(fd);                    /* 此时虽然close 了fd,但是对p的更改依然可以同步到/tmp/a.dat文件中 */
  p[0]=0x30313233;
  p[1]=0x12345678;
  munmap(p,LENGTH);                    /* 解除映射关系 */
  return 0;
}

/* jixiuf@jf /tmp $ cat a.dat  */
/* helloworld */
/* jixiuf@jf /tmp $ hexdump a.dat  */
/* 0000000 6568 6c6c 776f 726f 646c 000a           */
/* 000000b */
/* jixiuf@jf /tmp $ /home/jixiuf/c/linux/mmap_test  */
/* jixiuf@jf /tmp $ hexdump a.dat                  */
/* 0000000 3233 3031 5678 1234 646c 000a           */
/* 000000b */
/* jixiuf@jf /tmp $  */
