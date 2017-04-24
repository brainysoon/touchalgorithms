#include <stdio.h>		//标准输入输出头文件 
#include <stdlib.h>		//标准头文件
#include <string.h>		//字符串处理头文件 
#include <ctype.h>

#define ERROR 0			//出错 
#define OK 1 			//成功 
#define MAX_IDENTY_LENGTH 16	//最大单词长度
#define COMPARE_OK 0	//相对比较成功 
#define LENGTH_MAX	40	//存储的最大标识符数目 

#define KEY_CODE 1 	//单词种别码 
#define LABEL_CODE 2 	//标识符种别码 
#define UNSIGN_INT 3 	//无整形数种别码 
#define COUNT_IDENTY 4 	//运算符号种别码 
#define DIVIDED_CODE 5	//分隔符种别码 

char DEFAULTE_FILE_URI[]="example.cpp";

FILE *mFile;			//打开文件的指针 
char cBuffer;			//读取一个字符 
char *keys[]={"if","else","for","while","do","return",		//关键字 
		"break","continue"}; 
char *border[6]={",",";","{","}","(",")"};		//分隔符 
char *arithmetic[10]={"+","-","*","/","<","<=","=",">",">=","<>"};			//运算符 
char *labels[LENGTH_MAX];		//用于保存标识符 
int  labelLength=0;				//当前以保存标识符的数据 
char *unsignInts[LENGTH_MAX];
int unsignIntLength=0;
char otherStrs[LENGTH_MAX];		//用于保存其他字符串 
int otherStrLength=0; 

int checkType(char identy[],int type){
	
	switch(type){		//检查是否未指定的类型 
		
		case 1:
			for (int i=0; i<8; i++){
				if (strcmp(identy,keys[i])==COMPARE_OK){
					return i+1;				//如果匹配到关键字，返回此关键字的位置，从1开始 
				}
			}
			return ERROR;
			break;
			
		case 2:
			
			//检查是否已经保存过该标识符
			for (int i=0; i<labelLength; i++){
				if (strcmp(identy,labels[i])==COMPARE_OK){		//匹配到相等字符串 
					
					return i+1;
				}
			}
			
			//如果不存在 则保存该字符串
			if (labelLength<LENGTH_MAX){
				
				labels[labelLength++]=identy;
				return labelLength;
			} else{
				return ERROR;
			}
			break;	
		
		case 3:
			//检查是否存在
			for (int i=0; i<unsignIntLength; i++){
				
				if (strcmp(identy,unsignInts[i])){
					
					return i+1;
				}
			}
			
			//添加到末尾
			if (unsignIntLength<LENGTH_MAX){
				
				unsignInts[unsignIntLength++]=identy;
				
				return unsignIntLength;
			} else{
				
				return ERROR;
			}
			 
			break;
		case 4:		//运算符
			 
			 //检查是否存在
			 for (int i=0; i<10; i++){
			 	if (strcmp(identy,arithmetic[i])==COMPARE_OK){
			 		
			 		return i+1;
				 }
			 } 
			 
			 return ERROR;
			break;
		case 5:
			
			//检查 是否为分隔符
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

//处理以字符开头的 
char alphaProcess(char buffer){
	
	//读取整个标识符 
	char identy[MAX_IDENTY_LENGTH];
	int i;
	for (i=0;isalpha(buffer)||isdigit(buffer);i++){
		
		identy[i]=buffer;
		buffer=fgetc(mFile);
	}
	identy[i]='\0';
	
	int position=0;		//单子的位置  默认没有位置 
	
	if (position=checkType(identy,KEY_CODE)){	//判断是否是Key种别码 
		printf("%d (%d,\"%s\")\n",position,KEY_CODE,identy);		
	}else{
		position=checkType(identy,LABEL_CODE);
		printf("%d (%d,\"%s\")\n",position,LABEL_CODE,identy);
	} 
	
	return buffer;
}

//对数字开头的进行处理 
char digitProcess(char buffer){
	
	char digitIdenty[MAX_IDENTY_LENGTH];
	int i;
	for (i=0; isdigit(buffer); i++){	//读取后面的数字 
		digitIdenty[i]=buffer;
		buffer=fgetc(mFile);
	}
	digitIdenty[i]='\0';		//添加字符串结束标志 
	
	int position=checkType(digitIdenty,UNSIGN_INT);		//位置
	
	printf("%d (%d,\"%s\")\n",position,UNSIGN_INT,digitIdenty);
	
	return buffer;
}

int otherProcess(char identy[],int &position){
	
	if (position=checkType(identy,COUNT_IDENTY)){		//检查是否为运算符 
		
		return COUNT_IDENTY;
	}else if (position=checkType(identy,DIVIDED_CODE)){	//检查是否为分隔符 
		
		return DIVIDED_CODE;
	}
	return ERROR; 		//都不是 
}

//对以其他开头的进行处理
char otherProcessBefore(char buffer){

	char identy[3];
	
	identy[0]=buffer;	//单子字符 
	//再读取一个
	identy[1]=fgetc(mFile);
	identy[2]='\0';		
	
	int position=0;
	int result=otherProcess(identy,position);
	
	if (!result){		//如果都不是 
		
		buffer=identy[1];
		identy[1]='\0'; 
		//再判断一遍
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

//词法分析函数 
int processWordAnalyze(char uri[]){
	 
	mFile=fopen(uri,"r");		//打开源程序文件 
	if (mFile==NULL) return ERROR;
	
	cBuffer=fgetc(mFile);		//从文件中读取一个字符
	
	while (cBuffer!=EOF){
		
		if (isalpha(cBuffer)){		//对这个字符进行分类处理 
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
