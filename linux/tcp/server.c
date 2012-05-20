//file name : server.c
//created at: 2012年05月20日 星期日 17时05分04秒
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

start(){
  int serverfd,clientfd;
  int n,i;
  char buf[1024];
  char addr[INET_ADDRSTRLEN];
  struct sockaddr_in serv_addr,client_addr;
  socklen_t client_len;
  /* int socket(int domain, int type, int protocol); */
  serverfd=socket(AF_INET,SOCK_STREAM,0); /* AF_INET:ipv4, */
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

  if(listen(serverfd,20)==-1){
    perror("listen error!");
    exit(1);
  }
  while(1){
    /* client_len是一个传入传出参数，传入的是client_addr的长度，传出的是接收到的客户端的实际client_addr的长度 */
    client_len=sizeof(client_addr);
    clientfd= accept(serverfd,(struct sockaddr*)&client_addr,&client_len);

    n=read(clientfd,buf,1024);
    /* 转ip为string, af_inet 表示ipv4,client_addr.sin_addr类型的地址转成string 存到addr 中 */
    inet_ntop(AF_INET,&client_addr.sin_addr,&addr,sizeof(addr));

    printf ("client [addr:%s],[port:%d],content:%s\n",
            addr,
            ntohs(client_addr.sin_port), buf); /* ntohs -net to host short  */
    for (i = 0; i < n; i++){
      buf[i]=toupper(buf[i]);
    }
    write(clientfd,buf,n);
    close(clientfd);
  }

  /* int  bind(int sockfd,  struct  sockaddr *serv_addr,  socklen_t     addrlen); */

}
int main(int argc, char *argv[]){
  start();
  return 0;
}

/* jixiuf@jf /usr/include $ telnet localhost 8888    */
/* Trying 127.0.0.1...                            */
/* Connected to jf.org. */
/* Escape character is '^]'. */
/* hello */
/* HELLO */
/* Connection closed by foreign host. */
/* jixiuf@jf /usr/include $ */
