/*
 * Filename : dask.cc
 * copyright : (C) 2006 by zhonghonglie
 * Function : 磁盘移臂调度算法 
*/
#include "dask.h"
DiskArm::DiskArm(){
int i;
 //输入当前道号
 cout << "Please input Current cylinder :" ;
 cin >> CurrentCylinder; 
 //磁头方向，输入 0 表示向小道号移动，1 表示向大道号移动
 cout << "Please input Current Direction (0/1) :" ;
 cin >> SeekDirection;
 //输入磁盘请求数，请求道号
 cout << "Please input Request Numbers :" ;
 cin >> RequestNumber;
 cout << "Please input Request cylinder string :";
 Request = new int[sizeof(int) * RequestNumber];
 Cylinder = new int[sizeof(int) * RequestNumber];
 for (i = 0; i < RequestNumber; i++)
 cin >> Request[i]; 
}
DiskArm::~DiskArm(){
}
//初始化道号，寻道记录
void DiskArm::InitSpace(char * MethodName)
{
 int i; 
 cout << endl << MethodName << endl;
 SeekNumber = 0;
 SeekChang = 0;
 for (i = 0; i < RequestNumber; i++)
 Cylinder[i] = Request[i];
 }
 // 统计报告算法执行情况
void DiskArm::Report(void){ 
 cout << endl;
 cout << "Seek Number: " << SeekNumber << endl;
 cout << "Chang Direction: " << SeekChang << endl << endl;
}
//先来先服务算法
void DiskArm::Fcfs(void)
{
 int Current = CurrentCylinder; 
 int Direction = SeekDirection;
 InitSpace("FCFS"); 
 cout << Current;
 for(int i=0; i<RequestNumber; i++){
 if(((Cylinder[i] >= Current) && !Direction)
 ||((Cylinder[i] < Current) && Direction)){
 //需要调头
SeekChang++; //调头数加 1
 Direction = !Direction ; //改变方向标志
 //报告当前响应的道号
 cout << endl << Current << " -> " << Cylinder[i]; 
 }
 else //不需调头，报告当前响应的道号
 cout << " -> " << Cylinder[i] ; 
 //累计寻道数，响应过的道号变为当前道号
 SeekNumber += abs(Current -Cylinder[i]);
 Current = Cylinder[i];
 }
 //报告磁盘移臂调度的情况
 Report();
}
//最短寻道时间优先算法
void DiskArm::Sstf(void)
{
 int Shortest;
 int Distance = 999999 ;
 int Direction = SeekDirection;
 int Current = CurrentCylinder; 
 InitSpace("SSTF"); 
 cout << Current;
 for(int i=0; i<RequestNumber; i++){
//查找当前最近道号
 for(int j=0; j<RequestNumber; j++){
  if(Cylinder[j] == -1) continue; //-1 表示已经响应过了
 if(Distance > abs(Current-Cylinder[j])){
 //到下一道号比当前距离近，下一道号为当前距离 
 Distance = abs(Current-Cylinder[j]);
 Shortest = j;
 }
 }
 if((( Cylinder[Shortest] >= Current) && !Direction)
 ||(( Cylinder[Shortest] < CurrentCylinder) && Direction)){
 //需要调头
 SeekChang++; //调头数加 1
 Direction = !Direction ; //改变方向标志
 //报告当前响应的道号
 cout << endl << Current << " -> " << Cylinder[Shortest]; 
 }
 else //不需调头，报告当前响应的道号
 cout << " -> " << Cylinder[Shortest] ; 
 //累计寻道数，响应过的道号变为当前道号
 SeekNumber += abs(Current -Cylinder[Shortest]);
 Current = Cylinder[Shortest];
 //恢复最近距离，销去响应过的道号
 Distance = 999999;
 Cylinder[Shortest] = -1;
 }
 Report();
 
}
//电梯调度算法
void DiskArm::Scan(void){
}
//均匀电梯调度算法
void DiskArm::CScan(void){
}
//LOOK 调度算法
void DiskArm::Look(void) 
{
}
//程序启动入口
int main(int argc,char *argv[]){
//建立磁盘移臂调度类
 DiskArm *dask = new DiskArm();
 //比较和分析 FCFS 和 SSTF 两种调度算法的性能
 dask->Fcfs();
 dask->Sstf();
}

