#include"mypctl.h"
int main(int argc, char *argv[]){
	int status1,status2;
	signal(SIGINT,(sighandler_t)sigcat);
	char* args1[] = {"/bin/ls","-a",NULL};
	char* args2[] = {"/bin/ps","-a",NULL};
	int pid1 = fork();
	int count = 0;
	if(pid1 < 0){
		printf("创建进程失败\n");
	}
	if(pid1 == 0){
		while(1)
		{
			pause();
			printf("我是子进程%d,我的父进程是%d\n",getpid(),getppid());
			printf("开始执行任务：ls\n");
			int pid = fork();
			if(pid < 0){
				printf("创建进程失败\n");
			}
			if(pid == 0){
				printf("ls %d号进程启动\n",getpid());
				status1 = execve(args1[0],args1,NULL);//装入执行程序
			}
		}
	}
	if(pid1 > 0){
		while(1)
		{
			printf("\n我是父进程%d, 现在是第%d次执行\n",getpid(),count);
			printf("开始执行任务： ps\n");
			int pid2 = fork();
			if(pid2 > 0){
				waitpid(pid2,&status2,0);//等待pid2结束
				kill(pid1,SIGINT);//运行pid1
				sleep(3);
				printf("第%d次执行结束，休眠3秒\n",count++);
				printf("\n");
				
			}
			if(pid2 < 0){
				printf("进城创建失败\n");
			}
			if(pid2 == 0){
				printf("ps %d号进程启动\n",getpid());
				status2 = execve(args2[0],args2,NULL);
			}
		}
	}
	return EXIT_SUCCESS;
}
			
			
			
