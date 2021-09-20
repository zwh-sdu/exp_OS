#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main()
{
    int pid1,pid2;      //the name of process
    int pipe1[2],pipe2[2],pipe3[2],pipe4[2];    //create four pipe
    //start creating
    if(pipe(pipe1)<0){
        perror("creating pipe1 failed!\n");
        exit(EXIT_FAILURE);
    }
    if(pipe(pipe2)<0){
        perror("creating pipe2 failed!\n");
        exit(EXIT_FAILURE);
    }
    if(pipe(pipe3)<0){
        perror("creating pipe3 failed!\n");
        exit(EXIT_FAILURE);
    }
    if(pipe(pipe4)<0){
        perror("creating pipe4 failed!\n");
        exit(EXIT_FAILURE);
    }
    //create child process
    pid1=fork();
    if(pid1<0){
        perror("creating child process1 failed!\n");
        exit(EXIT_FAILURE);
    }
    if(pid1==0){    //child process running
        //close useless pipe
        close(pipe1[1]);
        close(pipe2[0]);
        int x,ansx=1;
        read(pipe1[0],&x,sizeof(int));
        printf("child process:%d read x = %d from father process:%d\n", getpid(),x,getppid());
        //calculate f(x)
        for(int i=1;i<=x;i++){
            ansx*=i;
        }
        printf("child process:%d write f(x) = %d to father process:%d\n",getpid(),ansx,getppid());        
        write(pipe2[1],&ansx,sizeof(int));
        //close used pipe
        close(pipe1[0]);
        close(pipe2[1]);
        exit(EXIT_SUCCESS);
    }
    if(pid1>0){
        pid2=fork();
        if(pid2<0){
            perror("creating child process2 failed!\n");
            exit(EXIT_FAILURE);
        }
        if(pid2==0){
            //close useless pipe
            close(pipe3[1]);
            close(pipe4[0]);
            int y,ansy;
            read(pipe3[0],&y,sizeof(int));
            printf("child process:%d read y = %d from father process:%d\n", getpid(),y,getppid());
            //calculate f(y)
            int temp1=1,temp2=1;
            if(y==1||y==2){
                ansy=1;
            }else{
                for(int i=3;i<=y;i++){
                    ansy=temp1+temp2;
                    temp1=temp2;
                    temp2=ansy;
                }
            }
            printf("child process:%d write f(y) = %d to father process:%d\n",getpid(),ansy,getppid());            
            write(pipe4[1],&ansy,sizeof(int));
            //close used pipe
            close(pipe3[0]);
            close(pipe4[1]);
            exit(EXIT_SUCCESS);
        }
        if(pid2>0){
            //close useless pipe
            close(pipe1[0]);
            close(pipe2[1]);
            close(pipe3[0]);
            close(pipe4[1]);
            int x,y;
            printf("please input x and y\n");
            scanf("%d %d",&x,&y);
            int ansx,ansy;
            write(pipe1[1],&x,sizeof(int));
            write(pipe3[1],&y,sizeof(int));
            read(pipe2[0],&ansx,sizeof(int));
            printf("father process read f(x) = %d\n",ansx);
            read(pipe4[0],&ansy,sizeof(int));
            printf("father process read f(y) = %d\n",ansy);
            int ans=ansx+ansy;
            printf("f(%d,%d) = %d\n", x,y,ans);
            //close used pipe
            close(pipe1[1]);
            close(pipe2[0]);
            close(pipe3[1]);
            close(pipe4[0]);
            exit(EXIT_SUCCESS);
        }
    }
}
