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
#include <unistd.h>
#include <sys/stat.h>
#define QUEUE_LEN 10

int main(int argc, char *argv[]){
  int fd,clientfd ,size,n;
  char buf[1024];
  struct sockaddr_un un;
  memset(&un,0,sizeof(un));
  un.sun_family=AF_UNIX;
  strcpy(un.sun_path,"/tmp/my_unix_socket");
  unlink(un.sun_path);          /* delete already exits  "/tmp/my_unix_socket" */
  fd=socket(AF_UNIX,SOCK_STREAM,0);
  if(fd<0){
    perror("socket error");
    exit(1);
  }
  size=offsetof(struct sockaddr_un,sun_path)+strlen(un.sun_path);
  /* offsetof宏，用来取成员在结构体中的偏移量
     offsetof(struct sockaddr_un, sun_path)就是取
     sockaddr_un结构体的sun_path成员在结构体中的偏移 */
  if (-1==bind(fd,(struct sockaddr*)&un,size)){
    perror("bind unix socket error");
    exit(1);
  }
  printf ("unix socket binded\n");
  if(-1==listen(fd, QUEUE_LEN)){
    perror("listen error");
    exit(1);
  }

  clientfd = server_accept(fd,NULL);
  if(clientfd<0)exit(1);
  n=read(clientfd,buf,1024);
  if(n>0){
    write(STDOUT_FILENO,buf,n);
    write(clientfd,buf,n);
  }
  else
    exit(-1);

  return 0;
}

int server_accept(int fd,uid_t *uidptr){
  int clientfd;
  int len;
  struct sockaddr_un addr;
  struct stat stat_buf;
     /* int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen); */

  clientfd=accept(fd,(struct sockaddr*)&addr,&len);
  if(clientfd<0){
    perror("accept error");
    exit(1);
  }

  len=sizeof(addr);
  len -= offsetof(struct sockaddr_un, sun_path); /* len of sun_path */
  addr.sun_path[len]=0;                          /* null terminal */

  if (stat(addr.sun_path,&stat_buf)<0){          /* socket file state error */
    return -2;
  }

  if(uidptr!=NULL){
    *uidptr = stat_buf.st_uid;  /* return uid of owner */
  }
  unlink(addr.sun_path);      /* socket file 用完可删了 */

  return clientfd;
}
