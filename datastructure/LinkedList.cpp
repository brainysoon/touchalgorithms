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

int DeleteElem_L(LinkList L,int i,int &e){
	
	LinkList q=L;		//指向头的指针 
	int j=0;
	
	//查找到 要删除的前一个  元素的指针，且  要删除的元素不为空 
	while (q->next&&j<i-1){
		
		++j;
		q=q->next;
	}
	
	if (!(q->next)||j>i-1) return ERROR;	//要删除的元素不为空  切  0<=i<=length 
	
	LinkList p=q->next;					//删除元素的指针 
	
	e=p->data;				//返回元素的值 通过  e 
	
	q->next=p->next;		//修改指针  使节点 i 在逻辑上删除 
	
	L->data-=1;			//长度-1 
	
	free(p);			//释放节点 
	
	return OK;
}

//查询第i个元素，并用e返回 
int GetElem_L(LinkList L,int i,int &e){
	
	LinkList q=L->next;		//第一个节点的指针 
	int j=1;				//计数器，计数第一个节点 
	
	//找到第i个元素 ，顺序向后查找，直到第i个元素，或者为空 
	while (q&&j<i){
		
		++j;
		q=q->next;
	}
	
	if (!q&&j>i) return ERROR;		//i的值是否合法   1<=i<=L.length 
	
	e=q->data;		//返回查找的值 
	
	return OK;
}//GetElem_L 

//逆位输入n个元素的值，建立带头节点的单链表 
int CreateList_L(LinkList &L,int n){
	
	L=(LinkList)malloc(sizeof(LNode));		//创建头节点 
	if (!L) return ERROR;
	
	L->next=NULL;		//给头节点初始化 
	L->data=0;
	
	LinkList p=NULL;	//新节点指针 
	
	while (n--){

		p=(LinkList)malloc(sizeof(LNode));		//生成新节点 
		if (!p) return ERROR;
		
		scanf("%d",&p->data);			//输入新节点数据 

		p->next=L->next;			//插入到表头 
		L->next=p;
		
		L->data+=1;			//长度+1 
	}
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
	
	//删除  5 个元素
	int e;
	DeleteElem_L(L,5,e);
	
	//打印删除的元素 
	printf("%d\n",e);
	
	//打印删除后的线性表 
	for (LinkList q=L->next;q;q=q->next) 
	printf("%d--%d\n",q->next,q->data); 
	
	//测试查找第i个元素 
	int elem;
	GetElem_L(L,3,elem);
	
	//查找结构 
	printf("%d \n",e);
	
	//尾插法 创建一个n个元素的单链表
	LinkList mL;
	CreateList_L(mL,4);
	
	//打印创建的单链表 
	for (LinkList q=mL->next; q; q=q->next)
	printf("%d---%d\n",q->next,q->data);
}
