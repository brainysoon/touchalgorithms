#include <stdio.h> 				//��׼�������ͷ�ļ� 
#include <stdlib.h>				//��׼��ͷ�ļ� 

#define LIST_INIT_SIZE 100		//��̬����ʵ�ֵ����Ա�ĳ�ʼ��С 
#define LISTINCREMENT 10		//ÿ�ζ�̬���ӵĴ�С 

#define OVERFLOW -1		//Խ�� 
#define FALSE 0			//ʧ�� 
#define OK 1			//�ɹ� 

//��̬����ʵ�ֵ����Ա�����ݽṹ 
typedef struct{
	int *elem;		//ÿ�����Ա��Ӧ�Ķ�̬������׵�ַ������ַ 
	int length; 	//���Ա�ǰ�ĳ��� 
	int listsize;		//�������Ա�Ĵ�С 
}SqList;

//��ʼ��һ���յ����Ա� 
int InitList_Sq(SqList &L){
	
	//��̬�������� 
	L.elem=(int*)malloc(LIST_INIT_SIZE*sizeof(int));
	 
	if (!L.elem) return OVERFLOW; 				//����ʧ�� 
	
	L.length=0;									//�ձ�ĳ���Ϊ0 
	L.listsize=LIST_INIT_SIZE; 						//��ʼ�洢����
	
	return OK;									//���س�ʼ���ɹ� 
}//InitList_Sq �㷨 2.3

//��˳���L�е�i��λ��֮ǰ�����µ�Ԫ��e 
int ListInsert_Sq(SqList &L,int i, int e){
	
	//�ж�i��ֵ�Ƿ�Ϸ����� 1<=i<=L.length+1 
	if (i<1||i>L.length+1) return OVERFLOW;
	
	//��ǰ�洢�ռ��������ӷ��� 
	if (L.length>=L.listsize){
		
		int * newbase=(int *)realloc(L.elem,(L.listsize+LISTINCREMENT)*sizeof(int));
		
		if (!newbase) return OVERFLOW;		//����ʧ�� 
		
		L.elem=newbase;						//�����µĵ�ַ 
		L.listsize+=LISTINCREMENT; 			//�������Ա�Ĵ�С 
	}
	
	int *q=&(L.elem[i-1]);		//Ҫ�����λ��
	for (int *p=&(L.elem[L.length-1]); p>=q; p--){
		*(p+1)=*p;				//����λ�ü������Ԫ�غ���һ����λ 
	}
	
	*q=e;			//����e 
	++L.length;		//����+1 
	
	return OK;
}

//�����Ա�L��ɾ����i��Ԫ�أ�����e������ֵ 
int ListDelete_Sq(SqList &L,int i,int &e){
	
	if (i<1||i>L.length) return OVERFLOW;		// i��ȡֵ��ΧΪ 1<=i<=L.length
	
	int *p=&(L.elem[i-1]);			//pΪ��ɾ����Ԫ��
	
	e=*p;							//��e���ر�ɾ����Ԫ��
	
	int *q=&(L.elem[L.length-1]); 	//��βԪ��  //������  int *q=L.elem+L.length 
	
	for (++p; p<=q; ++p){
		
		*(p-1)=*p;					//��iԪ���Ժ������Ԫ��ͳͳ��ǰ�ƶ�һ�� �ܹ��ƶ� n-i�� 
	} 
	
	--L.length;						//����-1 
	
	return OK;
}

int main(){
	
	//����һ�� ����ʵ�ֵ����Ա� 
	SqList L;
	
	//��ʼ��������Ա� 
	InitList_Sq(L);
	
	//���Բ���200������ 
	for (int i=0; i<200; i++){
	
		ListInsert_Sq(L,i+1,i); 
		
		printf("%d %d \n",L.elem[i],L.length); 
	}
	
	//���� �����Ա���ɾ��һ��Ԫ�� λ��1 
	int e;
	ListDelete_Sq(L,1,e);
	
	//ɾ����Ԫ�� 
	printf("%d\n",e); 
	
	//��Ӧɾ�������Ա� 
	for (int i=0; i<L.length; i++){
		
		printf("%d %d\n",L.elem[i],i+1);
	}
}
