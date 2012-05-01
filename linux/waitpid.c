#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    pid_t pid;
    pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }
    if (pid == 0) {
        int i;
        for (i = 3; i > 0; i--) {
            printf("This is the child\n");
            sleep(1);
        }
        exit(3);
    } else {
        int stat_val;
        waitpid(pid, &stat_val, 0);
        if (WIFEXITED(stat_val))
            printf("Child exited with code %d\n", WEXITSTATUS(stat_val));
        else if (WIFSIGNALED(stat_val))
            printf("Child terminated abnormally, signal %d\n", WTERMSIG(stat_val));
    }
    return 0;
}

/* 调用wait和waitpid不仅可以获得子进程的终止信息，还可以使父进程阻塞等待子进程
   终止，起到进程间同步的作用。如果参数status不是空指针，则子进程的终止信息通过
   这个参数传出，如果只是为了同步而不关心子进程的终止信息，可以将status参数指定
   为NULL。 */

/* 如果父进程的所有子进程都还在运行，调用wait将使父进程阻塞，而调用waitpid时如
   果在options参数中指定WNOHANG可以使父进程不阻塞而立即返回0。 /\* *\/ */

/* 子进程的终止信息在一个int中包含了多个字段，用宏定义可以取出其中的每个字段：
   如果子进程是正常终止的，WIFEXITED取出的字段值非零，WEXITSTATUS取出的字段值就
   是子进程的退出状态；如果子进程是收到信号而异常终止的，WIFSIGNALED取出的字段
   值非零，WTERMSIG取出的字段值就是信号的编号。作为练习，请读者从头文件里查一下
   这些宏做了什么运算，是如何取出字段值的。 */
