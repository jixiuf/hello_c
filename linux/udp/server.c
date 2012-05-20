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

  if(-1==bind(serverfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr))){
    perror("bind error!");
    exit(1);
  }

  while(1){
    client_len=sizeof(client_addr);
    n= recvfrom(serverfd,buf,1024,0,(struct sockaddr*)&client_addr,&client_len);
    if(n<0){
      perror("reevfrom error");
      exit(1);
    }
    if(n>0){
      inet_ntop(AF_INET,&client_addr.sin_addr,&addr,sizeof(addr));
      printf ("ip:%s,port:%d\n",addr,ntohs(client_addr.sin_port));
      /* 转ip为string, af_inet 表示ipv4,client_addr.sin_addr类型的地址转成string 存到addr 中 */
      printf ("%s\n",buf);
      n=sendto(serverfd,buf,n,0,(struct sockaddr*)&client_addr,sizeof(client_addr));
      if(n==-1){
        perror("sendto error");
        exit(1);
      }

    }

  }
  return 0;
}
