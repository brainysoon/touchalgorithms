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

int main(){
	
	//初始化一个静态链表 
	SLinkList SL;
	InitSpace_SL(SL);
	
	//打印链接成备用链表后的链表
	for (int i=0;SL[i].cur; i=SL[i].cur){
		printf("-->%d\n",SL[i].cur);
	} 
} 
