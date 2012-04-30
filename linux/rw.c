//file name : rw.c
//created at: 2012年04月30日 星期一 19时28分55秒
//author:  纪秀峰

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
int main(int argc, char *argv[]){
  /* 这个程序从终端上读10个字符，写读到字符到终端 */
  char str[10];
  int readed_count=  read(STDIN_FILENO,str,10);
  if(readed_count<0){
    perror("read error");
    exit(-1);
  }
  write(STDOUT_FILENO,str,readed_count);
  return 0;
}

/* $ ./a.out  */
/* hello（回车） */
/* hello */
/* $ ./a.out  */
/* hello world（回车） */
/* hello worl$ d */
/* bash: d: command not found */

/* 第一次执行a.out的结果很正常，而第二次执行的过程有点特殊，现在分析一下： */

/*     Shell进程创建a.out进程，a.out进程开始执行，而Shell进程睡眠等待a.out进程
       退出。 */

/*     a.out调用read时睡眠等待，直到终端设备输入了换行符才从read返回，read只读
       走10个字符，剩下的字符仍然保存在内核的终端设备输入缓冲区中。 */

/*     a.out进程打印并退出，这时Shell进程恢复运行，Shell继续从终端读取用户输入
       的命令，于是读走了终端设备输入缓冲区中剩下的字符d和换行符，把它当成一条
       命令解释执行，结果发现执行不了，没有d这个命令。 */
