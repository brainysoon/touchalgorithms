#include <stdio.h>			//��׼���������
#include <stdlib.h>			//��׼��

#define ERROR 0			//���� 
#define OK 1			//�ɹ� 

//˫������洢�ṹ 
typedef struct DuLNode{
	int data;					//������ 
	struct DuLNode *prior;		//ֱ��ǰ��ָ�� 
	struct DuLNode *next;		//ֱ�Ӻ���ָ�� 
}DuLNode,*DuLinkList;

int main(){
	
	//��ʼ��һ��˫������
	DuLinkList DuL=(DuLinkList) malloc(sizeof(DuLNode));
	DuL->data=0;
	DuL->next=NULL;
	DuL->prior=NULL;
	
	//��ӡ���� 
	printf("Length:%d\n",DuL->data); 
} 
