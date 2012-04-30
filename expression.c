#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stack.h>
#include<list.h>
#define MAX  100

int operatorsLength=6;
char operators[]={'+','-','*','/','(',')'};
//返回操作符的优先级 ,这个没用到
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

/*获得下一个表达示单元,根把操作符切割
 str  表达示
 index 表达示的索引,表示从何处对表达示进行处理
 return 下一个单元,同时调整index 的值,便 于下一个单元的切割
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
计算 num1 + num2

*/
void cal(double *num1,double *num2,char oper){
if (oper=='+')  *num1=*num1+*num2;
if (oper=='-')  *num1=*num1-*num2;
if (oper=='*')  *num1=*num1*(*num2);
if (oper=='/')  *num1=*num1 / *num2;
}

	//中序表达示求值,
double* cal_mid_Fun(List mid){
	//存操作符的栈
	Stack opers= createStack();
	//存操作数的栈
	Stack nums= createStack();
 int i ;
	for(i=0;i<list_sizeOf(mid);i++){//表示还没有遍历完表示达
		char *cp=list_get_at(mid,i);
		if (isOperator(cp)){//如果是操作符
           char oper=cp[0];
         if (oper==')'){
          char *oper2;
		  do {
			  double *d2=(double*)pop(nums);
			  double *d1=(double*)pop(nums);
			  char *oper1=(char*)pop(opers);
			  oper2=(char*)peek(opers);//peek出堆栈里的顶层操作符,以便判断是不是( ,是的话就结束,否则继续进行运算
			  cal(d1,d2,oper1[0]);
			  push(nums,d1);
		  } while(oper2[0]!='(');//直到取出的下一个操作符是( ,结束运算
		           pop(opers);//pop 左括号
            }else if (oper=='('){//如果是 * 或/ 或(
                push(opers,cp);
			}else { //如果是+-*/
                      int cur_priority=priority(oper);
					  if (!isEmpty(opers)){//如果操作符栈非空,
						  char *proOper= (char*)peek(opers);
						  int pro_priority=priority(proOper[0]);
						  if (pro_priority>=cur_priority){//如果优先级相等或者栈里的优先级高 ,先做栈里的运算,再将当前操作符入栈,注意到最后,所有东西入栈后,运算顺序从栈底开始,
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

//中
//前序表达式求值+/abc    读取方式 ,从右向左,遇数入栈,遇符取栈中两数计算
//  (a/b)+c
double* cal_pro_Fun(List pro_tokens){
	list_inverse(pro_tokens);//倒序pro_tokens ,便于从右向左读取
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
//中序表达式转后序表达式
List mid2post(List mid){
	Stack opers= createStack();
	List post=list_create();
	int i =0;
	for(i=0;i<list_sizeOf(mid);i++){//表示还没有遍历完表示达
		char *cp=list_get_at(mid,i);
		if (isOperator(cp)){//如果是操作符
			char oper=cp[0];
			if (oper==')'){
				char *oper2=(char*)pop(opers);
				do {
					list_add(post,oper2);
					oper2=(char*)pop(opers);
				} while(oper2[0]!='(');
			}else if (oper=='('){//如果是 * 或/ 或(
				push(opers,cp);
			}else { //如果是+-* /
				int cur_priority=priority(oper);
				if (!isEmpty(opers)){//如果操作符栈非空,
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
