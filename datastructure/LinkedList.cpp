#include <stdio.h>		//��׼�������ͷ�ļ�
#include <stdlib.h>		//��׼�� 

#define ERROR 0 		//��׼����
#define OK 1 			//�ɹ�

//��ʽ���Ա�--������Ľڵ����ݽṹ 
typedef struct LNode{
	int data;
	struct LNode *next;
}LNode, *LinkList; 

//������  ��i��Ԫ��ǰ����һ��Ԫ��e 
int ListInsert_L(LinkList &L,int i,int e){
	 
	LinkList q=L;			//ָ��ͷԪ�ص�ָ�� 
	int j=0;				//�������� j 
	
	while (q&&j<i-1) {		//�ҵ�  �� i ��Ԫ�ص�ǰһ��Ԫ�� ���� qָ���� 
		++j;
		q=q->next;
	}
	
	if (!q||j>i-1) return ERROR;		//i<1 ���ߴ��� ��+1 ������ 
	
	LinkList p=(LinkList)malloc(sizeof(LNode));			//Ϊ�½ڵ�  ����ռ� 
	
	if (!p) return ERROR;			//����ʧ�� 
	
	p->data=e;		//���·���Ľڵ㸳ֵ 
	
	//����Ԫ�صĺ��Ĵ��� 
	p->next=q->next;			 
	q->next=p;
	
	//�� +1 
	L->data+=1;
		
	return OK;
}

int DeleteElem_L(LinkList L,int i,int &e){
	
	LinkList q=L;		//ָ��ͷ��ָ�� 
	int j=0;
	
	//���ҵ� Ҫɾ����ǰһ��  Ԫ�ص�ָ�룬��  Ҫɾ����Ԫ�ز�Ϊ�� 
	while (q->next&&j<i-1){
		
		++j;
		q=q->next;
	}
	
	if (!(q->next)||j>i-1) return ERROR;	//Ҫɾ����Ԫ�ز�Ϊ��  ��  0<=i<=length 
	
	LinkList p=q->next;					//ɾ��Ԫ�ص�ָ�� 
	
	e=p->data;				//����Ԫ�ص�ֵ ͨ��  e 
	
	q->next=p->next;		//�޸�ָ��  ʹ�ڵ� i ���߼���ɾ�� 
	
	L->data-=1;			//����-1 
	
	free(p);			//�ͷŽڵ� 
	
	return OK;
}

//��ѯ��i��Ԫ�أ�����e���� 
int GetElem_L(LinkList L,int i,int &e){
	
	LinkList q=L->next;		//��һ���ڵ��ָ�� 
	int j=1;				//��������������һ���ڵ� 
	
	//�ҵ���i��Ԫ�� ��˳�������ң�ֱ����i��Ԫ�أ�����Ϊ�� 
	while (q&&j<i){
		
		++j;
		q=q->next;
	}
	
	if (!q&&j>i) return ERROR;		//i��ֵ�Ƿ�Ϸ�   1<=i<=L.length 
	
	e=q->data;		//���ز��ҵ�ֵ 
	
	return OK;
}//GetElem_L 

//��λ����n��Ԫ�ص�ֵ��������ͷ�ڵ�ĵ����� 
int CreateList_L(LinkList &L,int n){
	
	L=(LinkList)malloc(sizeof(LNode));		//����ͷ�ڵ� 
	if (!L) return ERROR;
	
	L->next=NULL;		//��ͷ�ڵ��ʼ�� 
	L->data=0;
	
	LinkList p=NULL;	//�½ڵ�ָ�� 
	
	while (n--){

		p=(LinkList)malloc(sizeof(LNode));		//�����½ڵ� 
		if (!p) return ERROR;
		
		scanf("%d",&p->data);			//�����½ڵ����� 

		p->next=L->next;			//���뵽��ͷ 
		L->next=p;
		
		L->data+=1;			//����+1 
	}
	return OK;
}

int main(){
	
	//����һ��ͷ�ڵ�
	LinkList L=(LinkList)malloc(sizeof(LNode));
	
	if (!L) return ERROR;		//����ʧ��
	
	L->data=0; 		//��ʼ��  ������ĳ���Ϊ0
	L->next=NULL;	//�յĵ�����ͷԪ��ָ��NULL 
	
	//ģ�����20 �����ݵ�  ������ 
	for (int i=0; i<20; i++){
		
		ListInsert_L(L,i+1,i);
	}
	
	//��ӡ���������   ���Խ�� 
	for (LinkList q=L->next;q;q=q->next) 
	printf("%d--%d\n",q->next,q->data); 
	
	//ɾ��  5 ��Ԫ��
	int e;
	DeleteElem_L(L,5,e);
	
	//��ӡɾ����Ԫ�� 
	printf("%d\n",e);
	
	//��ӡɾ��������Ա� 
	for (LinkList q=L->next;q;q=q->next) 
	printf("%d--%d\n",q->next,q->data); 
	
	//���Բ��ҵ�i��Ԫ�� 
	int elem;
	GetElem_L(L,3,elem);
	
	//���ҽṹ 
	printf("%d \n",e);
	
	//β�巨 ����һ��n��Ԫ�صĵ�����
	LinkList mL;
	CreateList_L(mL,4);
	
	//��ӡ�����ĵ����� 
	for (LinkList q=mL->next; q; q=q->next)
	printf("%d---%d\n",q->next,q->data);
}
