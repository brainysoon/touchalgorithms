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

//将下表为k的空闲节点回收到备用链表 
void Free_SL(SLinkList &space,int k){
	 
	space[k].cur=space[0].cur;		//回收 
	space[0].cur=k;
	
	return;
} //Free_SL 

//计算 (A-B)U(B-A) 两集合的四则运算
int Difference_SL(SLinkList &space,int &S){
	
	InitSpace_SL(space);		//初始化一个备用节点链表 
	
	S=Malloc_SL(space);			//从备用接连链表里面分配一个头节点 
	if (!S) return ERROR;
	
	space[S].cur=NULL;			//初始化头节点数据，包括长度和尾指针 
	space[S].data=0;
	
	int r=S;					//指向尾部 
	
	int m,n;					//输入的 集合 A B 的大小 
	scanf("%d %d",&m,&n);
	
	for (int i=0; i<m; i++){	//首先输入集合A 
		
		int k=Malloc_SL(space);		//从备用链表申请一个节点 
		if (!k) return ERROR;
		
		scanf("%d",&space[k].data);			//尾插法 插入到S链表 
		space[r].cur=k;
		r=k;							//尾部向后滑动 
		
		space[S].data+=1;				//长度+1 
	}
	space[r].cur=NULL;					//尾部指向空 
	
	int temp;
	for (int i=0; i<n; i++){			//依次输入 B集合节点 
		
		scanf("%d", &temp);
		
		int k=space[S].cur;			//分别指向S首节点 
		int p=S;
		
		while (k&&space[k].data!=temp){		//遍历A集合 查找是否有与 temp等值的节点 
			p=k;
			k=space[k].cur;
		}
		
		if (!k){						//如果没有等值的 则插入该节点 
			
			int j=Malloc_SL(space);		//首先从备用链表申请一个节点 
			if (!j) return ERROR;
			
			space[j].data=temp;			//插入到S链表尾部的前一个节点 
			space[j].cur=space[r].cur;
			space[r].cur=j;
			
			space[S].data+=1;			//长度+1 
		}else{							//否则，删除该节点 
			
			space[p].cur=space[k].cur;	//删除并回收该节点 
			Free_SL(space,k);
			
			if (r==k) r==p;				//如果删除的是尾部，尾部向前滑动一个
			
			space[S].data-=1;			//长度-1 
		}//if
	} //for
}//Difference_SL

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
	
	//定义计算 (A-B)U(B-A) 两集合的四则运算
	SLinkList mSL;
	int S;
	
	//输入集合并计算 
	Difference_SL(mSL,S);
	
	//打印集合计算结果
	printf("Length:%d\n",mSL[S].data);
	for (int i=mSL[S].cur; i; i=mSL[i].cur){
		printf("%d-->%d\n",mSL[i].cur,mSL[i].data);
	}  
} 
