#include <stdio.h>			//��׼���������
#include <stdlib.h>			//��׼��

#define MAXSIZE 1000		//�������󳤶�
#define ERROR -1			//���� 
#define OK 1				//�ɹ� 

//���徲̬����������ݽṹ 
typedef struct {
	int data;
	int cur;
}component,SLinkList[MAXSIZE]; 

//��ʼ������û���õĽڵ����ӳ�һ���������� 
int InitSpace_SL(SLinkList &space){
	
	//���ӱ������� 
	for (int i=0; i<MAXSIZE-1; i++) space[i].cur=i+1;
	space[MAXSIZE-1].cur=0;
	
	return OK; 
} 

int main(){
	
	//��ʼ��һ����̬���� 
	SLinkList SL;
	InitSpace_SL(SL);
	
	//��ӡ���ӳɱ�������������
	for (int i=0;SL[i].cur; i=SL[i].cur){
		printf("-->%d\n",SL[i].cur);
	} 
} 
