//file name : client.c
//created at: 2012年05月20日 星期日 21时06分50秒
//author:  纪秀峰

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <errno.h>
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
  while(1){
    n=my_read_line(STDIN_FILENO,buf,1024);
    if(strncmp("exit",buf,4)==0){
      break;
    }
    write(serverfd,buf,n);
    n=read(serverfd,buf,1024);
    printf ("server said:%s\n",buf);
  }
  close(serverfd);
  return 0;
}


static ssize_t my_read(int fd, char *ptr)
{
    static int read_cnt;
    static char *read_ptr;
    static char read_buf[100];

    if (read_cnt <= 0) {
    again:
        if ( (read_cnt = read(fd, read_buf, sizeof(read_buf))) < 0) {
            if (errno == EINTR)
                goto again;
            return -1;
        } else if (read_cnt == 0)
            return 0;
        read_ptr = read_buf;
    }
    read_cnt--;
    *ptr = *read_ptr++;
    return 1;
}

ssize_t my_read_line(int fd, void *vptr, size_t maxlen)
{
    ssize_t n, rc;
    char    c, *ptr;

    ptr = vptr;
    for (n = 1; n < maxlen; n++) {
        if ( (rc = my_read(fd, &c)) == 1) {
            *ptr++ = c;
            if (c  == '\n')
                break;
        } else if (rc == 0) {
            *ptr = 0;
            return n - 1;
        } else
            return -1;
    }
    *ptr  = 0;
    return n;
}
