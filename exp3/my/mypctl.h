#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
//进程自定义的键盘中断信号处理函数
typedef void (*sighandler_t)(int);
void sigcat() { printf("%d 进程继续\n", getpid()); }
//getpid 返回当前进程的进程号，getppid 返回当前进程父进程的进程号
