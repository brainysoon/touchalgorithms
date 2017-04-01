#include <stdio.h>			//标准输入输出库
#include <stdlib.h>			//标准库

#define MAXSIZE 1000		//链表的最大长度
#define ERROR -1			//错误 
#define OK 1				//成功 

//定义静态单链表的数据结构 
typedef struct {
	int data;
	int cur;
}component,SLinkList[MAXSIZE]; 

//初始化，将没有用的节点链接成一个备用链表 
int InitSpace_SL(SLinkList &space){
	
	//链接备用链表 
	for (int i=0; i<MAXSIZE-1; i++) space[i].cur=i+1;
	space[MAXSIZE-1].cur=0;
	
	return OK; 
} 

//从备用链表里面提取一个节点，如果为空 则返回0 否则返回节点下标 
int Malloc_SL(SLinkList &space){
	
	int i=space[0].cur;		//备用链表的第一个元素 
	
	if (space[0].cur)		//如果不为空则将备用链表后移一位 
	space[0].cur=space[i].cur;		

	return i;			//返回提取节点的下标 
}//Malloc_SL

int main(){
	
	//初始化一个静态链表 
	SLinkList SL;
	InitSpace_SL(SL);
	
	//打印链接成备用链表后的链表
	for (int i=0;SL[i].cur; i=SL[i].cur){
		printf("-->%d\n",SL[i].cur);
	}
	
	//从备用链表里面提取一个节点
	int i=Malloc_SL(SL);
	printf("BackUP:%d\n",i); 
} 
