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

//两个元素比较函数
int compare(int p,int e){
	return p==e;
} //Compare 

//在线性表中查找与e满足 compare条件的元素的位置 未找到则返回0 
int LocateElem_Sq(SqList &L,int e,int (* compare)(int,int)){
	
	int i=1; 			//第一个元素的位置
	
	int *p=L.elem;		//第一个元素的指针
	
	while (i<=L.length&&!(*compare)(*p++,e)) ++i;		//扫描线性表  这一句  很好，，， 
	
	if (i<=L.length) return i;			//存在返回 位置 
	else return FALSE;					//不存在返回失败 
} //LocateElem_Sq

//将两个非递减的线性表 a b 归并到  线性表c 并返回归并后的长度 
int MergeList_Sq(SqList La,SqList Lb,SqList &Lc){
	
	//算的归并后的长度 
	Lc.length=Lc.listsize=La.length+Lb.length;
	 
	Lc.elem=(int *)malloc(Lc.listsize*sizeof(int));  	//分配数组 
	
	if (!Lc.elem) return OVERFLOW;			//失败 返回  0 
	
	int *qa=La.elem;	// 线性表a的首元素地址 
	int *qb=Lb.elem;	// 线性表b的首元素地址 
	int *qc=Lc.elem;	// 线性表c首地址 
	
	int *pa=&(La.elem[La.length-1]);	//线性表a 尾地址 
	int *pb=&(Lb.elem[Lb.length-1]);	//线性表b 尾地址 
	
	//开始归并 
	while (qa<=pa&&qb<=pb){
		
		if (*qa<=*qb) *qc++=*qa++;
		else *qc++=*qb++;
	}
	
	//解决不需要归并的  直接  复制 
	while (qa<=pa) *qc++=*qa++;
	while (qb<=pb) *qc++=*qb++;
	 
	return Lc.length;		//返回长度 
} //MergeList_Sq 

int main(){
	
	//定义一个 数组实现的线性表 
	SqList L;
	
	//初始化这个线性表 
	InitList_Sq(L);
	
	//测试插入20个数据 
	for (int i=0; i<20; i++){
	
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
	
	//测试在线性表中查找 e元素
	int i=LocateElem_Sq(L,12,compare);
	
	//查找结果
	printf("%d\n",i); 
	
	//归并 两个线性表的测试  
	SqList La;		//线性表a 
	SqList Lb;		//线性表b 
	SqList Lc;		//线性表c --用于保存归并后的 
	
	//初始化  线性表a b 
	InitList_Sq(La);
	InitList_Sq(Lb);
	
	//初始化非递减数据 
	for (int i=0; i<20; i++){
		
		ListInsert_Sq(La,i+1,i*2);
		ListInsert_Sq(Lb,i+1,i*3);
	}
	
	// 打印出来  a b 的数据 
	for (int i=0; i<20; i++) printf("%d ",La.elem[i]);
	printf("\n");
	for (int i=0; i<20; i++) printf("%d ",Lb.elem[i]);
	printf("\n");
	
	//开始合并 
	MergeList_Sq(La,Lb,Lc);
	
	//合并后的结果 
	for (int i=0; i<Lc.length; i++){
		
		printf("%d--> %d\n",i+1,Lc.elem[i]);
	}
}
