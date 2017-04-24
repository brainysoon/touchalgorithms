#include <stdio.h>		//��׼�������ͷ�ļ� 
#include <stdlib.h>		//��׼ͷ�ļ�
#include <string.h>		//�ַ�������ͷ�ļ� 
#include <ctype.h>

#define ERROR 0			//���� 
#define OK 1 			//�ɹ� 
#define MAX_IDENTY_LENGTH 16	//��󵥴ʳ���
#define COMPARE_OK 0	//��ԱȽϳɹ� 
#define LENGTH_MAX	40	//�洢������ʶ����Ŀ 

#define KEY_CODE 1 	//�����ֱ��� 
#define LABEL_CODE 2 	//��ʶ���ֱ��� 
#define UNSIGN_INT 3 	//���������ֱ��� 
#define COUNT_IDENTY 4 	//��������ֱ��� 
#define DIVIDED_CODE 5	//�ָ����ֱ��� 

char DEFAULTE_FILE_URI[]="example.cpp";

FILE *mFile;			//���ļ���ָ�� 
char cBuffer;			//��ȡһ���ַ� 
char *keys[]={"if","else","for","while","do","return",		//�ؼ��� 
		"break","continue"}; 
char *border[6]={",",";","{","}","(",")"};		//�ָ��� 
char *arithmetic[10]={"+","-","*","/","<","<=","=",">",">=","<>"};			//����� 
char *labels[LENGTH_MAX];		//���ڱ����ʶ�� 
int  labelLength=0;				//��ǰ�Ա����ʶ�������� 
char *unsignInts[LENGTH_MAX];
int unsignIntLength=0;
char otherStrs[LENGTH_MAX];		//���ڱ��������ַ��� 
int otherStrLength=0; 

int checkType(char identy[],int type){
	
	switch(type){		//����Ƿ�δָ�������� 
		
		case 1:
			for (int i=0; i<8; i++){
				if (strcmp(identy,keys[i])==COMPARE_OK){
					return i+1;				//���ƥ�䵽�ؼ��֣����ش˹ؼ��ֵ�λ�ã���1��ʼ 
				}
			}
			return ERROR;
			break;
			
		case 2:
			
			//����Ƿ��Ѿ�������ñ�ʶ��
			for (int i=0; i<labelLength; i++){
				if (strcmp(identy,labels[i])==COMPARE_OK){		//ƥ�䵽����ַ��� 
					
					return i+1;
				}
			}
			
			//��������� �򱣴���ַ���
			if (labelLength<LENGTH_MAX){
				
				labels[labelLength++]=identy;
				return labelLength;
			} else{
				return ERROR;
			}
			break;	
		
		case 3:
			//����Ƿ����
			for (int i=0; i<unsignIntLength; i++){
				
				if (strcmp(identy,unsignInts[i])){
					
					return i+1;
				}
			}
			
			//��ӵ�ĩβ
			if (unsignIntLength<LENGTH_MAX){
				
				unsignInts[unsignIntLength++]=identy;
				
				return unsignIntLength;
			} else{
				
				return ERROR;
			}
			 
			break;
		case 4:		//�����
			 
			 //����Ƿ����
			 for (int i=0; i<10; i++){
			 	if (strcmp(identy,arithmetic[i])==COMPARE_OK){
			 		
			 		return i+1;
				 }
			 } 
			 
			 return ERROR;
			break;
		case 5:
			
			//��� �Ƿ�Ϊ�ָ���
			for (int i=0; i<6; i++){
				
				if (strcmp(identy,border[i])==COMPARE_OK){
					
					return i+1;
				}
			} 
			
			return ERROR;
			break;
	}
	
	return ERROR;
}

//�������ַ���ͷ�� 
char alphaProcess(char buffer){
	
	//��ȡ������ʶ�� 
	char identy[MAX_IDENTY_LENGTH];
	int i;
	for (i=0;isalpha(buffer)||isdigit(buffer);i++){
		
		identy[i]=buffer;
		buffer=fgetc(mFile);
	}
	identy[i]='\0';
	
	int position=0;		//���ӵ�λ��  Ĭ��û��λ�� 
	
	if (position=checkType(identy,KEY_CODE)){	//�ж��Ƿ���Key�ֱ��� 
		printf("%d (%d,\"%s\")\n",position,KEY_CODE,identy);		
	}else{
		position=checkType(identy,LABEL_CODE);
		printf("%d (%d,\"%s\")\n",position,LABEL_CODE,identy);
	} 
	
	return buffer;
}

//�����ֿ�ͷ�Ľ��д��� 
char digitProcess(char buffer){
	
	char digitIdenty[MAX_IDENTY_LENGTH];
	int i;
	for (i=0; isdigit(buffer); i++){	//��ȡ��������� 
		digitIdenty[i]=buffer;
		buffer=fgetc(mFile);
	}
	digitIdenty[i]='\0';		//����ַ���������־ 
	
	int position=checkType(digitIdenty,UNSIGN_INT);		//λ��
	
	printf("%d (%d,\"%s\")\n",position,UNSIGN_INT,digitIdenty);
	
	return buffer;
}

int otherProcess(char identy[],int &position){
	
	if (position=checkType(identy,COUNT_IDENTY)){		//����Ƿ�Ϊ����� 
		
		return COUNT_IDENTY;
	}else if (position=checkType(identy,DIVIDED_CODE)){	//����Ƿ�Ϊ�ָ��� 
		
		return DIVIDED_CODE;
	}
	return ERROR; 		//������ 
}

//����������ͷ�Ľ��д���
char otherProcessBefore(char buffer){

	char identy[3];
	
	identy[0]=buffer;	//�����ַ� 
	//�ٶ�ȡһ��
	identy[1]=fgetc(mFile);
	identy[2]='\0';		
	
	int position=0;
	int result=otherProcess(identy,position);
	
	if (!result){		//��������� 
		
		buffer=identy[1];
		identy[1]='\0'; 
		//���ж�һ��
		result=otherProcess(identy,position);	
		
		if (result==COUNT_IDENTY){
		
			printf("%d (%d,\"%s\")\n",position,COUNT_IDENTY,identy);
		} else if (result==DIVIDED_CODE){
		
			printf("%d (%d,\"%s\")\n",position,DIVIDED_CODE,identy);
		}else {
			if (identy[0]=='\n'){
				printf("\'\\n\' character\n");
			}else if (identy[0]=='\t'){
				printf("\'\\t\' character\n");
			}else if (identy[0]==32){
				printf("\'\\b\' character\n");	
			}else{
				printf("\'code:%d\' character\n",identy[0]);
			}
		}
	}else{
		if (result==COUNT_IDENTY){
		
			printf("%d (%d,\"%s\")\n",position,COUNT_IDENTY,identy);
		} else if (result==DIVIDED_CODE){
		
			printf("%d (%d,\"%s\")\n",position,DIVIDED_CODE,identy);
		}
		buffer=fgetc(mFile);
	}
	
	return buffer;
} 

//�ʷ��������� 
int processWordAnalyze(char uri[]){
	 
	mFile=fopen(uri,"r");		//��Դ�����ļ� 
	if (mFile==NULL) return ERROR;
	
	cBuffer=fgetc(mFile);		//���ļ��ж�ȡһ���ַ�
	
	while (cBuffer!=EOF){
		
		if (isalpha(cBuffer)){		//������ַ����з��ദ�� 
			cBuffer=alphaProcess(cBuffer); 
		}else if (isdigit(cBuffer)){
			cBuffer=digitProcess(cBuffer);
		}else{
			cBuffer=otherProcessBefore(cBuffer);
		}
	}
	printf("over\n");
}

int main(){
	
	processWordAnalyze(DEFAULTE_FILE_URI);
}
