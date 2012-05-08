#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
/*利用 管道，写一个类似 ls -l |grep fork|grep 2的程序 ， */
void exec(){
  int len=4;
  char* cmds[4][3]={{"ls","-l",NULL},{"grep","fork",NULL},{"grep","2",NULL},{"grep","c$",NULL}};

  int i,k;
  int fds[len][2];



  fds[0][0]=0;
  fds[len-1][1]=1;
  for (i = 1; i < len; ++i){
    int pipefd[2];
    pipe(pipefd);
    fds[i-1][1]=pipefd[1];
    fds[i][0]=pipefd[0];
  }
  for ( i = 0; i < len; ++i){
    /* spawnprocess(cmds[i][0],cmds[i][0],fds[i][0],fds[i][1],fds,len); */
    if(fork()==0)
      {

        if(fds[i][0]!=STDIN_FILENO) dup2(fds[i][0],STDIN_FILENO),close(fds[i][0]);
        if(fds[i][1]!=STDOUT_FILENO) dup2(fds[i][1],STDOUT_FILENO),close(fds[i][1]);
        for (k=0; k < len; ++k){
          if(fds[k][0]!=STDIN_FILENO) close(fds[k][0]);
          if(fds[k][1]!=STDOUT_FILENO) close(fds[k][1]);
        }
        execvp(cmds[i][0],cmds[i]);
        exit(1);
      }
  }
  for (k=0; k < len; ++k){
    if(fds[k][0]!=STDIN_FILENO) close(fds[k][0]);
    if(fds[k][1]!=STDOUT_FILENO) close(fds[k][1]);
  }
  for ( i = 0; i < len; ++i){
    wait(NULL);
  }
  exit(0);
}

int main(int argc, char *argv[]){
  exec();
  return 0;
}
