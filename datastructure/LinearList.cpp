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

//����Ԫ�رȽϺ���
int compare(int p,int e){
	return p==e;
} //Compare 

//�����Ա��в�����e���� compare������Ԫ�ص�λ�� δ�ҵ��򷵻�0 
int LocateElem_Sq(SqList &L,int e,int (* compare)(int,int)){
	
	int i=1; 			//��һ��Ԫ�ص�λ��
	
	int *p=L.elem;		//��һ��Ԫ�ص�ָ��
	
	while (i<=L.length&&!(*compare)(*p++,e)) ++i;		//ɨ�����Ա�  ��һ��  �ܺã����� 
	
	if (i<=L.length) return i;			//���ڷ��� λ�� 
	else return FALSE;					//�����ڷ���ʧ�� 
} //LocateElem_Sq

//�������ǵݼ������Ա� a b �鲢��  ���Ա�c �����ع鲢��ĳ��� 
int MergeList_Sq(SqList La,SqList Lb,SqList &Lc){
	
	//��Ĺ鲢��ĳ��� 
	Lc.length=Lc.listsize=La.length+Lb.length;
	 
	Lc.elem=(int *)malloc(Lc.listsize*sizeof(int));  	//�������� 
	
	if (!Lc.elem) return OVERFLOW;			//ʧ�� ����  0 
	
	int *qa=La.elem;	// ���Ա�a����Ԫ�ص�ַ 
	int *qb=Lb.elem;	// ���Ա�b����Ԫ�ص�ַ 
	int *qc=Lc.elem;	// ���Ա�c�׵�ַ 
	
	int *pa=&(La.elem[La.length-1]);	//���Ա�a β��ַ 
	int *pb=&(Lb.elem[Lb.length-1]);	//���Ա�b β��ַ 
	
	//��ʼ�鲢 
	while (qa<=pa&&qb<=pb){
		
		if (*qa<=*qb) *qc++=*qa++;
		else *qc++=*qb++;
	}
	
	//�������Ҫ�鲢��  ֱ��  ���� 
	while (qa<=pa) *qc++=*qa++;
	while (qb<=pb) *qc++=*qb++;
	 
	return Lc.length;		//���س��� 
} //MergeList_Sq 

int main(){
	
	//����һ�� ����ʵ�ֵ����Ա� 
	SqList L;
	
	//��ʼ��������Ա� 
	InitList_Sq(L);
	
	//���Բ���20������ 
	for (int i=0; i<20; i++){
	
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
	
	//���������Ա��в��� eԪ��
	int i=LocateElem_Sq(L,12,compare);
	
	//���ҽ��
	printf("%d\n",i); 
	
	//�鲢 �������Ա�Ĳ���  
	SqList La;		//���Ա�a 
	SqList Lb;		//���Ա�b 
	SqList Lc;		//���Ա�c --���ڱ���鲢��� 
	
	//��ʼ��  ���Ա�a b 
	InitList_Sq(La);
	InitList_Sq(Lb);
	
	//��ʼ���ǵݼ����� 
	for (int i=0; i<20; i++){
		
		ListInsert_Sq(La,i+1,i*2);
		ListInsert_Sq(Lb,i+1,i*3);
	}
	
	// ��ӡ����  a b ������ 
	for (int i=0; i<20; i++) printf("%d ",La.elem[i]);
	printf("\n");
	for (int i=0; i<20; i++) printf("%d ",Lb.elem[i]);
	printf("\n");
	
	//��ʼ�ϲ� 
	MergeList_Sq(La,Lb,Lc);
	
	//�ϲ���Ľ�� 
	for (int i=0; i<Lc.length; i++){
		
		printf("%d--> %d\n",i+1,Lc.elem[i]);
	}
}
