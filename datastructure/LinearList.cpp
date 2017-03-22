#include <stdio.h> 				//标准输入输出头文件 
#include <stdlib.h>				//标准库头文件 

#define LIST_INIT_SIZE 100		//动态数组实现的线性表的初始大小 
#define LISTINCREMENT 10		//每次动态增加的大小 

#define OVERFLOW -1		//越界 
#define FALSE 0			//失败 
#define OK 1			//成功 

//动态数组实现的线性表的数据结构 
typedef struct{
	int *elem;		//每个线性表对应的动态数组的首地址，基地址 
	int length; 	//线性表当前的长度 
	int listsize;		//分配线性表的大小 
}SqList;

//初始化一个空的线性表 
int InitList_Sq(SqList &L){
	
	//动态分配数组 
	L.elem=(int*)malloc(LIST_INIT_SIZE*sizeof(int));
	 
	if (!L.elem) return OVERFLOW; 				//分配失败 
	
	L.length=0;									//空表的长度为0 
	L.listsize=LIST_INIT_SIZE; 						//初始存储容量
	
	return OK;									//返回初始化成功 
}//InitList_Sq 算法 2.3

//在顺序表L中第i个位置之前插入新的元素e 
int ListInsert_Sq(SqList &L,int i, int e){
	
	//判断i的值是否合法，及 1<=i<=L.length+1 
	if (i<1||i>L.length+1) return OVERFLOW;
	
	//当前存储空间已满增加分配 
	if (L.length>=L.listsize){
		
		int * newbase=(int *)realloc(L.elem,(L.listsize+LISTINCREMENT)*sizeof(int));
		
		if (!newbase) return OVERFLOW;		//分配失败 
		
		L.elem=newbase;						//赋予新的地址 
		L.listsize+=LISTINCREMENT; 			//增加线性表的大小 
	}
	
	int *q=&(L.elem[i-1]);		//要插入的位置
	for (int *p=&(L.elem[L.length-1]); p>=q; p--){
		*(p+1)=*p;				//插入位置及后面的元素后移一个单位 
	}
	
	*q=e;			//插入e 
	++L.length;		//长度+1 
	
	return OK;
}

//在线性表L中删除第i个元素，并用e返回其值 
int ListDelete_Sq(SqList &L,int i,int &e){
	
	if (i<1||i>L.length) return OVERFLOW;		// i的取值范围为 1<=i<=L.length
	
	int *p=&(L.elem[i-1]);			//p为被删除的元素
	
	e=*p;							//用e返回被删除的元素
	
	int *q=&(L.elem[L.length-1]); 	//表尾元素  //或则是  int *q=L.elem+L.length 
	
	for (++p; p<=q; ++p){
		
		*(p-1)=*p;					//将i元素以后的所有元素统统向前移动一个 总共移动 n-i个 
	} 
	
	--L.length;						//长度-1 
	
	return OK;
}

int main(){
	
	//定义一个 数组实现的线性表 
	SqList L;
	
	//初始化这个线性表 
	InitList_Sq(L);
	
	//测试插入200个数据 
	for (int i=0; i<200; i++){
	
		ListInsert_Sq(L,i+1,i); 
		
		printf("%d %d \n",L.elem[i],L.length); 
	}
	
	//测试 在线性表中删除一个元素 位置1 
	int e;
	ListDelete_Sq(L,1,e);
	
	//删除的元素 
	printf("%d\n",e); 
	
	//答应删除后线性表 
	for (int i=0; i<L.length; i++){
		
		printf("%d %d\n",L.elem[i],i+1);
	}
}
