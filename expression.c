#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stack.h>
#include<list.h>
#define MAX  100

int operatorsLength=6;
char operators[]={'+','-','*','/','(',')'};
//���ز����������ȼ� ,���û�õ�
int priority(char oper){
	if  (oper=='+'||oper=='-'){
		return 1;
	}else if (oper=='*'||oper=='/'){
		return 2;
	}else if (oper==')'){
		return 3;
	}else if (oper=='('){
	return 0;
  }
	return 0;
}


int isOperatorByChar(char unit){
	int i ;
		for(i=0;i<operatorsLength;i++){
		   char c1 =operators[i];
			if (c1==unit){
				return 1;
			}
		}
return 0;

}

int isOperator(char* unit){
	int i ;
	int len=strlen(unit);
	if (len==1){
		for(i=0;i<operatorsLength;i++){
		   char c1 =operators[i];
			if (c1==unit[0]){
				return 1;
			}
		}
	}
	return 0;

}

/*�����һ�����ʾ��Ԫ,���Ѳ������и�
 str  ���ʾ
 index ���ʾ������,��ʾ�Ӻδ��Ա��ʾ���д���
 return ��һ����Ԫ,ͬʱ����index ��ֵ,�� ����һ����Ԫ���и�
*/
char* getNextExpUnit(char* str,int* index){
	int i;
	int len= strlen(str);
	char *nextToken=(char*) malloc(len*sizeof(char));
	int nextIndex=0;
	for(i=*index;i<len;i++){
		char c =str[i];
		 *index=i+1;
		if (c==' '||c=='\t'){
			 continue;
		}
		if (isOperatorByChar(c)){
			if (nextIndex!=0){
                *index=i;
			nextToken[nextIndex]='\0';
				return nextToken;
			}else{
				nextToken[0]=c;
				nextToken[1]='\0';
				return nextToken;
			}
		}else{
			nextToken[nextIndex]=c;
			nextIndex++;
		}
	}
	return nextToken;
}

List getExpTokens(char* exp){
	List tokens= list_create();
	int index=0,*pi=&index;
	int len=strlen(exp);
	while(*pi<len){
		list_add(tokens,getNextExpUnit(exp,pi));
	}
	return tokens;
}

/*
���� num1 + num2

*/
void cal(double *num1,double *num2,char oper){
if (oper=='+')  *num1=*num1+*num2;
if (oper=='-')  *num1=*num1-*num2;
if (oper=='*')  *num1=*num1*(*num2);
if (oper=='/')  *num1=*num1 / *num2;
}

	//������ʾ��ֵ,
double* cal_mid_Fun(List mid){
	//���������ջ
	Stack opers= createStack();
	//���������ջ
	Stack nums= createStack();
 int i ;
	for(i=0;i<list_sizeOf(mid);i++){//��ʾ��û�б������ʾ��
		char *cp=list_get_at(mid,i);
		if (isOperator(cp)){//����ǲ�����
           char oper=cp[0];
         if (oper==')'){
          char *oper2;
		  do {
			  double *d2=(double*)pop(nums);
			  double *d1=(double*)pop(nums);
			  char *oper1=(char*)pop(opers);
			  oper2=(char*)peek(opers);//peek����ջ��Ķ��������,�Ա��ж��ǲ���( ,�ǵĻ��ͽ���,���������������
			  cal(d1,d2,oper1[0]);
			  push(nums,d1);
		  } while(oper2[0]!='(');//ֱ��ȡ������һ����������( ,��������
		           pop(opers);//pop ������
            }else if (oper=='('){//����� * ��/ ��(
                push(opers,cp);
			}else { //�����+-*/
                      int cur_priority=priority(oper);
					  if (!isEmpty(opers)){//���������ջ�ǿ�,
						  char *proOper= (char*)peek(opers);
						  int pro_priority=priority(proOper[0]);
						  if (pro_priority>=cur_priority){//������ȼ���Ȼ���ջ������ȼ��� ,����ջ�������,�ٽ���ǰ��������ջ,ע�⵽���,���ж�����ջ��,����˳���ջ�׿�ʼ,
								  double *d2=(double*)pop(nums);
								  double *d1=(double*)pop(nums);
								  cal(d1,d2,proOper[0]);
								  push(nums,d1);
								  char *oper3=(char*)pop(opers);
						  }
				}
				push(opers,cp);
			}                  
		} else{
			double *dp=(double*)malloc(sizeof(double));
			*dp=strtod(cp,NULL);
			push(nums,dp);
		}
	}
	while (!isEmpty(opers)){
			double *d2=(double*)pop(nums);
			double *d1=(double*)pop(nums);
		    char *oper3=(char*)pop(opers);
            cal(d1,d2,oper3[0]);
            push(nums,d1);
	}
  double *d= (double*)pop(nums);
         free(opers);
         free(nums);

     return d;
}

//��
//ǰ����ʽ��ֵ+/abc    ��ȡ��ʽ ,��������,������ջ,����ȡջ����������
//  (a/b)+c
double* cal_pro_Fun(List pro_tokens){
	list_inverse(pro_tokens);//����pro_tokens ,���ڴ��������ȡ
int i ;
	Stack nums= createStack();
	for(i=0;i<list_sizeOf(pro_tokens);i++){
		char *token=list_get_at(pro_tokens,i);
		if (isOperator(token)){
			double *num1=(double*)pop(nums);
			double *num2=(double*)pop(nums);
                  cal(num1,num2,token[0]);
			push(nums,num1);
		}else{
			double *num=(double*)malloc(sizeof(double));
			*num=strtod(token,NULL);
			push(nums,num);
		}
	}
	double* result=(double*)pop(nums);
	freeStack(nums);
     return result;
	//List tokens= getExpTokens(exp);
}

double* cal_post_Fun(List post_tokens){
int i ;
	Stack nums= createStack();
	for(i=0;i<list_sizeOf(post_tokens);i++){
		char *token=list_get_at(post_tokens,i);
		if (isOperator(token)){
			double *num2=(double*)pop(nums);
			double *num1=(double*)pop(nums);
                  cal(num1,num2,token[0]);
			push(nums,num1);
		}else{
			double *num=(double*)malloc(sizeof(double));
			*num=strtod(token,NULL);
			push(nums,num);
		}
			//free(token);
	}
	double* result=(double*)pop(nums);
	freeStack(nums);
     return result;
	//List tokens= getExpTokens(exp);
}
//1   +   2   *   (   2   +   2   -   6   )
//1   2   2   2   +   6   -   *   +  
//������ʽת������ʽ
List mid2post(List mid){
	Stack opers= createStack();
	List post=list_create();
	int i =0;
	for(i=0;i<list_sizeOf(mid);i++){//��ʾ��û�б������ʾ��
		char *cp=list_get_at(mid,i);
		if (isOperator(cp)){//����ǲ�����
			char oper=cp[0];
			if (oper==')'){
				char *oper2=(char*)pop(opers);
				do {
					list_add(post,oper2);
					oper2=(char*)pop(opers);
				} while(oper2[0]!='(');
			}else if (oper=='('){//����� * ��/ ��(
				push(opers,cp);
			}else { //�����+-* /
				int cur_priority=priority(oper);
				if (!isEmpty(opers)){//���������ջ�ǿ�,
					char *proOper= (char*)peek(opers);
					int pro_priority=priority(proOper[0]);
					if (pro_priority>=cur_priority){
						list_add(post,proOper);
						pop(opers);
					}
				}
				push(opers,cp);
			}                  
		} else{
			list_add(post,cp);
		}
	}

	while(!isEmpty(opers)){
		char* oper=pop(opers);
		list_add(post,oper);
	}
	freeStack(opers);
	return post;

}

int main(){
int i ;
 char* exp="1+2*(2+2-6)";
puts(exp);
 List mid=getExpTokens(exp);
 for(i=0;i<list_sizeOf(mid);i++){
	 printf("%s   ",(char*)list_get_at(mid,i));
 }
 double *d=cal_mid_Fun(mid);
	 printf("\nresult=%f\n ",*d);
 List post=mid2post(getExpTokens(exp));
 for(i=0;i<list_sizeOf(post);i++){
	 printf("%s   ",(char*)list_get_at(post,i));
 }
//d=cal_post_Fun(post);
	 printf("\nresult=%f\n ",*d);
 list_free(mid);
 list_free(post);
}
