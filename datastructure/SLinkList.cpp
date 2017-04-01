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

//�ӱ�������������ȡһ���ڵ㣬���Ϊ�� �򷵻�0 ���򷵻ؽڵ��±� 
int Malloc_SL(SLinkList &space){
	
	int i=space[0].cur;		//��������ĵ�һ��Ԫ�� 
	
	if (space[0].cur)		//�����Ϊ���򽫱����������һλ 
	space[0].cur=space[i].cur;		

	return i;			//������ȡ�ڵ���±� 
}//Malloc_SL

int main(){
	
	//��ʼ��һ����̬���� 
	SLinkList SL;
	InitSpace_SL(SL);
	
	//��ӡ���ӳɱ�������������
	for (int i=0;SL[i].cur; i=SL[i].cur){
		printf("-->%d\n",SL[i].cur);
	}
	
	//�ӱ�������������ȡһ���ڵ�
	int i=Malloc_SL(SL);
	printf("BackUP:%d\n",i); 
} 
