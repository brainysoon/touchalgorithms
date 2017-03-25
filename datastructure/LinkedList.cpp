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
}
