//file name : udp/server.c
//created at: 2012年05月20日 星期日 23时03分01秒
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
  char buf[1024];
  int n;
  int client_len;
  char addr[INET_ADDRSTRLEN];
  struct sockaddr_in serv_addr,client_addr;

  serverfd= socket(AF_INET,SOCK_DGRAM,0);
  if(serverfd==-1){
    perror("open server socket error!");
    exit(1);
  }

  bzero(&serv_addr,sizeof(serv_addr)); /* 清0 */
  serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
  serv_addr.sin_port=htons(SERVER_PORT);
  serv_addr.sin_family=AF_INET;
  strcpy(buf,"hello");
  n=sendto(serverfd,buf,strlen(buf),0,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
  if(n==-1){
    perror("sendto error");
    exit(1);
  }
  n= recvfrom(serverfd,buf,1024,0,NULL,NULL);
  write(STDOUT_FILENO,"server said:",strlen("server said:"));
  write(STDOUT_FILENO,buf,n);
  close(serverfd);
  return 0;
}
