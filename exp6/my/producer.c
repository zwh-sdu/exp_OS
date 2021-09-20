#include "ipc.h"
int main(int argc,char *argv[])
{
    int rate;
//可在在命令行第一参数指定一个进程睡眠秒数，以调解进程执行速度
    if(argv[1] != NULL)
        rate = atoi(argv[1]);
    else
        rate = 3; //不指定为 1 秒
//共享内存使用的变量
    buff_key = 101;//缓冲区任给的键值
    buff_num = 3;//缓冲区任给的长度
    pput_key = 102;//生产者放产品指针的键值
    pput_num = 1; //指针数
    shm_flg = IPC_CREAT | 0644;//共享内存读写权限

//获取缓冲区使用的共享内存，buff_ptr 指向缓冲区首地址
    buff_ptr = (char *)set_shm(buff_key,buff_num,shm_flg);
//获取生产者放产品位置指针 pput_ptr
    pput_ptr = (int *)set_shm(pput_key,pput_num,shm_flg);
//信号量使用的变量
    prod1_key = 201;//生产者同步信号灯键值
    prod2_key = 202;//生产者同步信号灯键值
    prod3_key = 203;//生产者同步信号灯键值
    pmtx_key = 204;//生产者互斥信号灯键值
    ab_key = 301;//有C的消费者控制键值
    ac_key = 302;//有B的消费者控制键值
    bc_key = 303;//有A的消费者控制键值
    sem_flg = IPC_CREAT | 0644;
//生产者同步信号灯初值设为缓冲区最大可用量
    sem_val = 1;
//获取生产者同步信号灯，引用标识存 prod_sem
    prod1_sem = set_sem(prod1_key,sem_val,sem_flg);
    prod2_sem = set_sem(prod2_key,sem_val,sem_flg);
    prod3_sem = set_sem(prod3_key,sem_val,sem_flg);
//消费者初始无产品可取，同步信号灯初值设为 0
    sem_val = 0;
    ab_sem = set_sem(ab_key,sem_val,sem_flg);
    ac_sem = set_sem(ac_key,sem_val,sem_flg);
    bc_sem = set_sem(bc_key,sem_val,sem_flg);
//生产者互斥信号灯初值为 1
    sem_val = 1;
//获取生产者互斥信号灯，引用标识存 pmtx_sem
    pmtx_sem = set_sem(pmtx_key,sem_val,sem_flg);
    int i = 0;
    
    while(1){
        int d = (i++)%3;
        down(pmtx_sem);
        //buff_ptr[*pput_ptr] = 'A'+ d;

	if(d==0){
	    down(prod1_sem);
	    sleep(rate);
	    *pput_ptr = 0;
            printf("%d把烟草和纸放入[%d]缓存区\n",getpid(),*pput_ptr);
            up(bc_sem);
        }
        else if(d==1){
            down(prod2_sem);
            sleep(rate);
            *pput_ptr = 1;
            printf("%d把胶水和纸放入[%d]缓存区\n",getpid(),*pput_ptr);
            up(ac_sem);
        }
        else{
            down(prod3_sem);
            sleep(rate);
            *pput_ptr = 2;
            printf("%d把烟草和胶水放入[%d]缓存区\n",getpid(),*pput_ptr);
            up(ab_sem);
        }
	//*pput_ptr = (*pput_ptr+1) % buff_num;
        up(pmtx_sem);
    }
    return EXIT_SUCCESS;
}


