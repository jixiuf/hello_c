/*  -*- coding:utf-8 -*-  */
#include<stdio.h>
#include<stdlib.h>
#include<stack.h>
/*
   这一次的修改更具用通过性，
   因为这里定义了一个
   typedef void *Void 
   所以下面出现Void 的时个相当于void* 类型的，
   而void* 类型的指针可以转换为任意类型，
   所以 无论是结构体，还是普通的int float 类型的指针，都可以往里放
   */
Stack createStack(){
	Stack s ;
	s =(Stack)malloc(sizeof(StackClass));
	s->top=-1;
	return s;
}
int isEmpty(Stack s){
	return s->top ==-1;
}
int sizeS(Stack s){
	return (s->top)+1;
}

Node getNode(Node n,int index ){
	if (n==NULL||index==-1){
		return NULL;
	}
	int i;
	Node tmp=n;
	for(i=0;i<index;i++){
		tmp=tmp->next;
	} 
	return  tmp;
}
Node getLastNodeButOne(Stack s ){
	int top=s->top;
	if (top<1){//保证s  至少有两个节点,lastButOne 才会有值
		return NULL;
	}
	return getNode(s->n,top-1);
}

Node getLastNode(Stack s  ){
	return   getNode(s->n,s->top);
}
Stack push (Stack s ,Void ele){
	if (s->n==NULL){
		Node root =malloc(sizeof(NodeClass));
		s->n=root;
		root->ele=ele;
		root->next=NULL;
		s->top++;
		return s;
	}
	Node lastNode=getLastNode(s);
	Node newNode= (Node)malloc(sizeof(NodeClass));
	newNode->ele=ele;
	newNode->next=NULL;
	lastNode->next=newNode;
	s->top++;
	return s;
} 

Void peek(Stack s ){
	if (s->top==-1){
		return NULL;
	}
	Node lastNode=getLastNode(s);
	return lastNode->ele ;
}
Void pop(Stack s ){
	if (s->top==-1){
		s->n=NULL;
		return NULL;
	}else if (s->top==0){
		Void ele= s->n->ele;
       free(s->n);
		s->n=NULL;
		s->top--;
		return ele;
	}

	Node n = s->n;
	Node lastNodeButOne=getLastNodeButOne(s);
	Node last=lastNodeButOne->next;
	lastNodeButOne->next=NULL;
	s->top--;
	Void ele=last->ele;
	free(last);
	return ele ;
}
void freeStack(Stack s){
	while(!isEmpty(s)){
		Void ele= pop(s);
		free(ele);
	}
 free(s);
}
/*
   int main(){
   Stack s =createStack();
   int i =231;
   int *p;
   p=&i;
   push(s,p);
   int j=23;
   p=&j;
   push(s,p);
   p=peek(s);
   printf("%d\n",*p);
   p=pop(s);
   printf("%d,%d\n",*p,sizeS(s));
   p=pop(s);
   printf("%d,%d\n",*p,sizeS(s));

   }
   */
