//file name : create_un.c
//created at: 2012年05月20日 星期日 23时37分57秒
//author:  纪秀峰

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#include <stddef.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>

#define QUEUE_LEN 10
#define TMP "/tmp/"


int main(int argc, char *argv[]){
  int fd,n;
 char buf[1024];
 fd=conn("/tmp/my_unix_socket");
 write(fd,"hello",strlen("hello"));
 n =read(fd,buf,1024);
 write(STDOUT_FILENO,"server said:",strlen("server said:"));
 write(STDOUT_FILENO,buf,n);
  return 0;
}

int conn(char*  name){
  int fd ,size;
  struct sockaddr_un un;

  memset(&un,0,sizeof(un));
  un.sun_family=AF_UNIX;
  sprintf(un.sun_path,"%s%d",TMP,getpid());

  fd=socket(AF_UNIX,SOCK_STREAM,0);
  if(fd<0){
    perror("socket error");
    exit(1);
  }

  size=offsetof(struct sockaddr_un,sun_path)+strlen(un.sun_path);
  unlink(un.sun_path);

  /* offsetof宏，用来取成员在结构体中的偏移量
     offsetof(struct sockaddr_un, sun_path)就是取
     sockaddr_un结构体的sun_path成员在结构体中的偏移 */
  if (-1==bind(fd,(struct sockaddr*)&un,size)){
    perror("bind unix socket error");
    exit(1);
  }
  printf ("unix socket binded\n");

  memset(&un,0,sizeof(un));
  un.sun_family=AF_UNIX;
  strcpy(un.sun_path,name);
  size=offsetof(struct sockaddr_un,sun_path)+strlen(un.sun_path);
  if(connect(fd,(struct sockaddr*)&un,size)<0){
    perror("connect error");
    exit(1);
  }
  return fd;
  /* int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen); */


}
