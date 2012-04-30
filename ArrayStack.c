#include<stdio.h>
#include<stdlib.h>
#define Max 20
struct ElementStruct{
	int num;
	char name;
};
typedef struct ElementStruct ElementClass ;
typedef ElementClass *Element ;

void  copyElement(Element src,Element dest){
         dest->num=src->num;
         dest->name=src->name;
}


struct StackStruct{
	  Element  eles ;
	  int top;
     int maxSize;
};
typedef  struct StackStruct StackClass;
typedef   StackClass *Stack;

Stack createStack(int size){
	Stack s ;
	s =(Stack)malloc(sizeof(StackClass));
    s->eles= (Element) malloc(size*sizeof(ElementClass));
    s->maxSize=size;
	s->top=-1;
return s;

}
int isEmpty(Stack s){
  return s->top ==-1;
}

int sizeS(Stack s){
  return (s->top)+1;
}

/*注意这里ele 传的是指针的地址*/
void push (Stack s ,Element* ele){
	if (s->top==s->maxSize-1){
		Element newE=(Element)malloc(s->maxSize*2*sizeof(ElementClass));
		Element oldElement=s->eles;
		Element newEp=newE;
        //copy src->dest
		int i=0;
		for(i=0;i< (s->maxSize);i++){
			copyElement(oldElement,newEp);
			oldElement++;
			newEp++;
		}
      //释放src 的内存
		free(s->eles);
		s->eles=newE;
		s->maxSize=s->maxSize*2;
	} 
	Element topE = (s->eles)+s->top+1;
	copyElement(*ele,topE);
	//只有是指针的地址,前面加* 表示指针所指向的Element指针类型，
	//有一点绕，是因为Element 本身就是个指针类型,而Element* 则表示这个指针类型的地十
	free(*ele);
	*ele=NULL;
	s->top++;

}
Element pop(Stack s ){
	Element topE = (s->eles)+(s->top);
     if (s->top==-1){
           return NULL;
      }
     (s->top)--;
    return topE;
}
int main(){
int i =0;
int size=10;
	Stack s =createStack(10);
//看到，这里是e 的地址，而不是e
	for(i=0;i<25;i++){
		Element e = (Element) malloc(sizeof(ElementClass));
		e->num=i;
		push(s,&e);
	}
Element it=s->eles;
for(i=0;i<sizeS(s);i++){
   printf("%d,%d\n",i,it->num);
    it++;
}

it=pop(s);
printf("%d\n",it->num);
	return 0;
}
