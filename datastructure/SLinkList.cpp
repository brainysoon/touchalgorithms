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

//���±�Ϊk�Ŀ��нڵ���յ��������� 
void Free_SL(SLinkList &space,int k){
	 
	space[k].cur=space[0].cur;		//���� 
	space[0].cur=k;
	
	return;
} //Free_SL 

//���� (A-B)U(B-A) �����ϵ���������
int Difference_SL(SLinkList &space,int &S){
	
	InitSpace_SL(space);		//��ʼ��һ�����ýڵ����� 
	
	S=Malloc_SL(space);			//�ӱ��ý��������������һ��ͷ�ڵ� 
	if (!S) return ERROR;
	
	space[S].cur=NULL;			//��ʼ��ͷ�ڵ����ݣ��������Ⱥ�βָ�� 
	space[S].data=0;
	
	int r=S;					//ָ��β�� 
	
	int m,n;					//����� ���� A B �Ĵ�С 
	scanf("%d %d",&m,&n);
	
	for (int i=0; i<m; i++){	//�������뼯��A 
		
		int k=Malloc_SL(space);		//�ӱ�����������һ���ڵ� 
		if (!k) return ERROR;
		
		scanf("%d",&space[k].data);			//β�巨 ���뵽S���� 
		space[r].cur=k;
		r=k;							//β����󻬶� 
		
		space[S].data+=1;				//����+1 
	}
	space[r].cur=NULL;					//β��ָ��� 
	
	int temp;
	for (int i=0; i<n; i++){			//�������� B���Ͻڵ� 
		
		scanf("%d", &temp);
		
		int k=space[S].cur;			//�ֱ�ָ��S�׽ڵ� 
		int p=S;
		
		while (k&&space[k].data!=temp){		//����A���� �����Ƿ����� temp��ֵ�Ľڵ� 
			p=k;
			k=space[k].cur;
		}
		
		if (!k){						//���û�е�ֵ�� �����ýڵ� 
			
			int j=Malloc_SL(space);		//���ȴӱ�����������һ���ڵ� 
			if (!j) return ERROR;
			
			space[j].data=temp;			//���뵽S����β����ǰһ���ڵ� 
			space[j].cur=space[r].cur;
			space[r].cur=j;
			
			space[S].data+=1;			//����+1 
		}else{							//����ɾ���ýڵ� 
			
			space[p].cur=space[k].cur;	//ɾ�������ոýڵ� 
			Free_SL(space,k);
			
			if (r==k) r==p;				//���ɾ������β����β����ǰ����һ��
			
			space[S].data-=1;			//����-1 
		}//if
	} //for
}//Difference_SL

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
	
	//������� (A-B)U(B-A) �����ϵ���������
	SLinkList mSL;
	int S;
	
	//���뼯�ϲ����� 
	Difference_SL(mSL,S);
	
	//��ӡ���ϼ�����
	printf("Length:%d\n",mSL[S].data);
	for (int i=mSL[S].cur; i; i=mSL[i].cur){
		printf("%d-->%d\n",mSL[i].cur,mSL[i].data);
	}  
} 
