#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>

int pipe1[2],pipe2[2];              //record pip number
pthread_t thrd1,thrd2,thrd3;        //record three pthread number

void task1(int *x){                 //calculate f(x)
    printf("task1 is running!\n");
    int ansx=1;
    for(int i=1;i<=*x;i++){
        ansx*=i;
    }
    write(pipe1[1],&ansx,sizeof(int));
    printf("thread1 write f(x) = %d to thread3\n",ansx);
    close(pipe1[1]);
}

int f(int y){
    if(y==1||y==2){
        return 1;
    }else{
        return f(y-1)+f(y-2);
    }
}

void task2(int *y){                 //calculate f(y)
    printf("task2 is running!\n");
    int ansy=f(*y);
    write(pipe2[1],&ansy,sizeof(int));
    printf("thread2 write f(y) = %d to thread3\n",ansy);
    close(pipe2[1]);
}


void task3(int *num){               //calculate f(x,y)
    printf("task3 is running!\n");
    int ansx,ansy,ans;
    read(pipe1[0],&ansx,sizeof(int));
    printf("thread3 read f(x) = %d from thread1\n",ansx);
    read(pipe2[0],&ansy,sizeof(int));
    printf("thread3 read f(y) = %d from thread2\n",ansy);
    close(pipe1[0]);
    close(pipe2[0]);
    ans=ansx+ansy;
    printf("f(x,y) = %d\n", ans);
    
}



int main(int argc,char *arg[])
{
    int ret;
    int x,y;
    //create two pipe
    if(pipe(pipe1)<0){
        perror("pipe1 not create!");
        exit(EXIT_FAILURE);
    }
    if(pipe(pipe2)<0){
        perror("pipe2 not create!");
        exit(EXIT_FAILURE);
    }
    //input x and y
    printf("please input x,y");
    scanf("%d%d",&x,&y);

    //create three pthread by function pthread_create
    ret=pthread_create(&thrd1,NULL,(void*)task1,(void*)&x);
    if(ret){
        perror("pthread_create:f1 failire!");
        exit(EXIT_FAILURE);
    }

    ret=pthread_create(&thrd2,NULL,(void*)task2,(void*)&y);
    if(ret){
        perror("pthread_create:f1 failure!");
        exit(EXIT_FAILURE);
    }

    int num=1;
    ret=pthread_create(&thrd3,NULL,(void*)task3,(void*)&num);
    if(ret){
        perror("pthread_create:f1 failure!");
        exit(EXIT_FAILURE);
    }

    //to clear three pthread
    pthread_join(thrd1,NULL);
    pthread_join(thrd2,NULL);
    pthread_join(thrd3,NULL);
    //exit
    exit(EXIT_SUCCESS);
}
