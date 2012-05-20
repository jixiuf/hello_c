//file name : client.c
//created at: 2012年05月20日 星期日 21时06分50秒
//author:  纪秀峰

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

#define SERVER_PORT 8888

int main(int argc, char *argv[]){
  int serverfd;
  struct sockaddr_in server_addr;
  int i ,n ;
  char buf[1024];
  char addr[]="127.0.0.1";

  if((serverfd=socket(AF_INET,SOCK_STREAM,0))<0){
    perror("socket error!");
    exit(1);
  }
  bzero(&server_addr,sizeof(server_addr));
  inet_pton(AF_INET,addr,&server_addr.sin_addr);
  server_addr.sin_port=htons(SERVER_PORT);
  server_addr.sin_family=AF_INET;

  /* int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen); */
  if(connect(serverfd,(struct sockaddr*)&server_addr,sizeof(server_addr))==-1){
    perror("connect error!");
    exit(1);
  }
  write(serverfd,"hello",sizeof("hello"));
  n=read(serverfd,buf,1024);
  printf ("server said:%s\n",buf);
  close(serverfd);
  return 0;
}
