#include<stdio.h>
#include<stdlib.h>
#include<sched.h>
#include<sys/time.h>
#include<sys/resource.h>
#include<unistd.h>
#include<signal.h>
#include<wait.h>
int pid;
typedef void (*sighandler)(int);
void plusc(){
    if(pid>0) return;
    setpriority(PRIO_PROCESS,getpid(),getpriority(PRIO_PROCESS,0)+1);
    printf("process %d priority+1 = %d\n",getpid(),getpriority(PRIO_PROCESS,0));
}

void minusc(){
    if(pid>0) return;
    setpriority(PRIO_PROCESS,getpid(),getpriority(PRIO_PROCESS,0)-1);
    printf("process %d priority-1 = %d\n",getpid(),getpriority(PRIO_PROCESS,0));
}

void minusp(){
    if(pid==0) return;
    setpriority(PRIO_PROCESS,getpid(),getpriority(PRIO_PROCESS,0)-1);
    printf("process %d priority-1 = %d\n",getpid(),getpriority(PRIO_PROCESS,0));
} 

int main(int argc,char* argv[])
{
    signal(SIGINT,(sighandler)plusc);
    signal(SIGTSTP,(sighandler)minusc);
    signal(SIGQUIT,(sighandler)minusp);
    struct sched_param p[2];
    for(int i=0;i<2;i++){
        p[i].sched_priority=10;
    }
    pid=fork();
    if(pid>0){
        sched_setscheduler(getpid(),SCHED_OTHER,&p[0]);
        setpriority(PRIO_PROCESS,getpid(),10);
        sleep(1);
        for(int i=0;;i++){
            printf("parent pid = %d, priority = %d, scheduler = %d\n",getpid(),getpriority(PRIO_PROCESS,0),sched_getscheduler(getpid()));
            sleep(3);
        }
    }else{
        sched_setscheduler(getpid(),SCHED_OTHER,&p[1]);
        setpriority(PRIO_PROCESS,getpid(),10);
        sleep(1);
        for(int i=0;;i++){
            printf("child pid = %d, priority = %d, scheduler = %d\n",getpid(),getpriority(PRIO_PROCESS,0),sched_getscheduler(getpid()));
            sleep(3);
        }
        exit(EXIT_SUCCESS);
    }
    return EXIT_SUCCESS;
}
