//file name : lseek.c
//created at: 2012年04月30日 星期一 20时15分56秒
//author:  纪秀峰

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
int main(int argc, char *argv[]){
  int fd;
  char * str="hello";
  fd =open("/tmp/lseek.out",O_WRONLY|O_CREAT);
  if (fd<0){
    perror("open failed ");
  }
  off_t cur_pos=lseek(fd,10,SEEK_SET); /* 移动光标到10,从10处开始写，10之前的内容为0填充 */
   if(cur_pos<0){
     perror("set position failed");
   }
  write(fd,str,strlen(str));
  return 0;
}

/* 若lseek成功执行，则返回新的偏移量，因此可用以下方法确定一个打开文件的当前偏移量： */
/* off_t currpos; */
/* currpos = lseek(fd, 0, SEEK_CUR); */
/* 在当前处置，向后0个位置设置光标，实际还是原位置 */
