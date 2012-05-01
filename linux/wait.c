#include <unistd.h>
#include <stdlib.h>

int main(void)
{
    pid_t pid=fork();
    if(pid<0) {
        perror("fork");
        exit(1);
    }
    if(pid>0) { /* parent */
        while(1);
    }
    /* child */
    return 0;
}
/* ps -ef |grep wait 可查看处于僵尸状态的子进程 */
/* 如果一个进程已经终止，但是它的父进程尚未调用wait或waitpid对它进行清理，这时
   的进程状态称为僵尸（Zombie）进程。任何进程在刚终止时都是僵尸进程，正常情况下，
   僵尸进程都立刻被父进程清理了， */
