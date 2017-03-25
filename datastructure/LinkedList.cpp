#include <stdio.h>		//标准输入输出头文件
#include <stdlib.h>		//标准库 

#define ERROR 0 		//标准错误
#define OK 1 			//成功

//链式线性表--单链表的节点数据结构 
typedef struct LNode{
	int data;
	struct LNode *next;
}LNode, *LinkList; 

//向单链表  第i个元素前插入一个元素e 
int ListInsert_L(LinkList &L,int i,int e){
	 
	LinkList q=L;			//指向头元素的指针 
	int j=0;				//计数变量 j 
	
	while (q&&j<i-1) {		//找到  第 i 个元素的前一个元素 并且 q指向它 
		++j;
		q=q->next;
	}
	
	if (!q||j>i-1) return ERROR;		//i<1 或者大于 表长+1 都不行 
	
	LinkList p=(LinkList)malloc(sizeof(LNode));			//为新节点  分配空间 
	
	if (!p) return ERROR;			//分配失败 
	
	p->data=e;		//给新分配的节点赋值 
	
	//插入元素的核心代码 
	p->next=q->next;			 
	q->next=p;
	
	//表长 +1 
	L->data+=1;
		
	return OK;
}

int main(){
	
	//创建一个头节点
	LinkList L=(LinkList)malloc(sizeof(LNode));
	
	if (!L) return ERROR;		//创建失败
	
	L->data=0; 		//初始化  单链表的长度为0
	L->next=NULL;	//空的单链表，头元素指向NULL 
	
	//模拟插入20 个数据到  单链表 
	for (int i=0; i<20; i++){
		
		ListInsert_L(L,i+1,i);
	}
	
	//打印插入的数据   测试结果 
	for (LinkList q=L->next;q;q=q->next) 
	printf("%d--%d\n",q->next,q->data); 
}
