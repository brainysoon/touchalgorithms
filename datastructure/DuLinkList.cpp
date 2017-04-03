#include <stdio.h>			//标准输入输出库
#include <stdlib.h>			//标准库

#define ERROR 0			//错误 
#define OK 1			//成功 

//双向链表存储结构 
typedef struct DuLNode{
	int data;					//数据域 
	struct DuLNode *prior;		//直接前驱指针 
	struct DuLNode *next;		//直接后驱指针 
}DuLNode,*DuLinkList;

int main(){
	
	//初始化一个双向链表
	DuLinkList DuL=(DuLinkList) malloc(sizeof(DuLNode));
	DuL->data=0;
	DuL->next=NULL;
	DuL->prior=NULL;
	
	//打印长度 
	printf("Length:%d\n",DuL->data); 
} 
