#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef void* Void;
struct ListStructNode{
	Void ele;
	struct ListStructNode *next;
};
typedef struct ListStructNode ListNodeClass;
typedef  ListNodeClass *ListNode;

struct ListStruct{
	int size;
	ListNode nodes;
};
typedef struct ListStruct ListClass;
typedef ListClass *List;
struct scoreStruct {
	char  stuname[20];
	char  term[20];
	char  class[20];
	int english;
	int chinese;
	int math;
};
typedef struct scoreStruct scoreClass;
typedef scoreClass *score;


/**get last node */
ListNode getLastListNode(ListNode head){
	ListNode n=head;
	if (head==NULL){
		return NULL;
	}
	if (head->next==NULL){
		return head;
	}

	while (n->next!=NULL){
		n=n->next;
	}
	return n;
}



ListNode getListNode(ListNode head,int index){
	ListNode n=head;
	int i=0;
	if(index<0||head==NULL){
		return NULL;
	}


	while (n!=NULL){
		if (i==index){
			return n;
		}
		n=n->next;
		i++;
	}
	return NULL;
}
int sizeOfListNode(ListNode listNode){
	ListNode n =listNode;
	int i =0;
	if (listNode==NULL){
		return 0;
	}


	while (n!=NULL){
		i++;
		n=n->next;
	}
	return i;
}
ListNode createNewNode(Void ele){
	ListNode newNode=(ListNode)malloc(sizeof(ListNodeClass));
	if (newNode==NULL) return NULL;
	newNode->next=NULL;
	newNode->ele=ele;
	return newNode;
}

ListNode mergeListNodeAt(ListNode head ,int index ,ListNode tail){
	ListNode nLast=getLastListNode(tail);
	ListNode indexListNode ,nextListNode;
	if (head==NULL) return tail ;

	if (index==-1){
		nLast->next=head;
		return  tail;
	}
	indexListNode= getListNode(head,index);
	if (indexListNode==NULL){ //index 越界,
		ListNode headLastNode=getLastListNode(head);
		headLastNode->next=tail;
		return  head;
	}
	nextListNode =indexListNode->next;
	indexListNode->next=tail;
	nLast->next=nextListNode;
	return head;
}

/* add the list n to head at heat.index position , when index=-1 means append head to n  */

List  list_create(){
	List list=(List)malloc(sizeof(ListClass));
	if (list!=NULL){
		list->size=0;
		list->nodes=NULL;
	}
	return list;
}
void list_merge_at(List headList ,int index ,List tailList){
	ListNode head,n ,nLast,indexListNode,nextListNode;
	if(tailList==NULL||headList==NULL) return;
	head=headList->nodes;
	n=tailList->nodes;
	nLast=getLastListNode(n);
	if (index==-1){
		nLast->next=head;
		headList->size+=tailList->size;
		headList->nodes=n;
		return ;
	}
	indexListNode  = getListNode(head,index);
	if (indexListNode==NULL){
		if (head==NULL){
			headList->size=tailList->size;
			headList->nodes=n;
			return ;
		}else{
			ListNode headLastNode=getLastListNode(head);
			headList->size+=tailList->size;
			headLastNode->next=n;
			return ;
		}

	}
	nextListNode=indexListNode->next;
	indexListNode->next=n;
	nLast->next=nextListNode;
	headList->size+=tailList->size;
	return;
}
void list_append(List headList, List tailList){
	if (headList==NULL) headList=tailList;
	list_merge_at(headList,headList->size-1,tailList);
}



void list_delete_at(List list ,int index){
	ListNode pro,n;
	ListNode head=list->nodes;
	if(index<0||list==NULL||list->size==0){
		return ;
	}
	if(index==0){
		ListNode next=head->next;
		head->next=NULL;
		free(head->ele);
		free(head);
		list->nodes=next;
		list->size--;
		return ;
	}
	pro= getListNode(head,index-1);
	if(pro==NULL){
		return ;
	}
	n= pro->next;
	if (n!=NULL){
		pro->next=n->next;
		n->next=NULL;
		free(n->ele);
		free(n);
		list->size--;
	}
}

void list_delete_last(List list ){
	list_delete_at(list,list->size-1);
}
void  list_inverse (List list ){
	ListNode p =list->nodes;
	ListNode pro=NULL ,next;
	if (p!=NULL){
		next= p->next;
	}
	while (p!=NULL){
		p->next= pro;
		pro=p;
		p=next;
		if (next!=NULL){
			next= next->next;
		}
	}
	list->nodes=pro;

}
void list_add_at (List list ,Void ele,int index ){
	ListNode node=list->nodes;
	ListNode newNode= createNewNode(ele);
	list->nodes= mergeListNodeAt(list->nodes ,index,newNode);
	list->size++;

}
void list_add (List list ,Void ele ){
	list_add_at(list,ele,list->size-1);
}
void list_modify_at (List list ,Void ele ,int index ){
	ListNode indexNode;
	ListNode listNode=list->nodes;
	if (listNode==NULL||index<0){
		return ;
	}
	indexNode=getListNode(listNode,index);
	if (indexNode!=NULL){
		free(indexNode->ele);
		indexNode->ele=ele;
		return ;
	}
	return ;
}
Void list_get_at(List list,int index){
	ListNode head=list->nodes;
	ListNode node=getListNode(head,index);
	if (node==NULL) return NULL;
	return node->ele;
}
Void list_get_last(List list){
	ListNode lastNode= getLastListNode(list->nodes);
	if (lastNode==NULL){
		return NULL;
	}
	return lastNode->ele;
}
int list_sizeOf(List list){
	return list->size;
}
void list_free(List list){
	ListNode n,head=list->nodes;
	while (head!=NULL){
		n=head;
		head=head->next;
		n->next=NULL;
		free(n->ele);
		free(n);
	}
	free(list);
}
void list_swap(List list ,int x ,int y){
	ListNode  xNode,yNode;
	int  len;
	Void xele,yele;
	len=list_sizeOf(list);
	if(x<0||y<0||x>=len||y>=len||x==y){ return ;}
	xele=list_get_at(list,x);
	yele=list_get_at(list,y);
	xNode=getListNode(list->nodes,x);
	yNode=getListNode(list->nodes,y);
	xNode->ele=yele;
	yNode->ele=xele;
}
int equals(char* str, char* substr){
	int i ;
	int len =strlen(substr);
	int len2=strlen(str);
	if (len!=len2) return 0;

	for(i=0;i<len;i++){
		if (str[i]!=substr[i]) return 0;
	}
	return 1;

}
int isStartWith(char* str, char* substr){
	int len =strlen(substr);
	int i ;
	for(i=0;i<len;i++){
		if (str[i]!=substr[i]) return 0;
	}
	return 1;

}
List list;
void flush(){
	int c;
	while ((c=getchar()) != '\n' && c != EOF);

}
char getChar(){
	flush();
	return getchar();
}
void getCmd( char* cmd){
	gets(cmd);
	//flush();

}
void modify(){
	int i, index;
	List mods;
	score s ,r;
	s =(score)malloc(sizeof(scoreClass));
	printf("please input the [term] name (defalut:2010-0  [2010-1,2009-0,2009-1])" );
	gets(s->term);
	if (strlen(s->term)==0){
		strcpy(s->term,"2010-0");
	}
	printf("please input the [class] name (defalut:class1  [class2, class071,class072])" );
	gets(s->class);
	if (strlen(s->class)==0){
		strcpy(s->class,"class1");
	}
	mods	=list_create();
	for(i=0;i<list_sizeOf(list);i++){
		r =(score)list_get_at(list,i);
		if (equals(r->class,s->class)&&equals(r->term,s->term)){
			list_add(mods,r);
		}

	}
	printf("we found [%d] records :\n",list_sizeOf(mods));
	for(i=0;i<list_sizeOf(mods);i++){
		s =(score)list_get_at(mods,i);
		printf("[%d]: %s,%s ,name=%s, english=%d,chinese= %d,math=%d\n",i,s->term,s->class,s->stuname,s->english,s->chinese,s->math);
	}


	while (index<list_sizeOf(mods)||index>-1){
		printf("please input the index you want to modify  ,for example 0 :  intput -1 to exit ");
		scanf("%d",&index);
		flush();
		if (index<0) break;
		s=(score)list_get_at(mods,index);
		printf(" %s,%s ,name=%s, english=%d,chinese= %d,math=%d\n",s->term,s->class,s->stuname,s->english,s->chinese,s->math);
		printf("please input [english] score:" );
		scanf("%d",&s->english);
		printf("please input  [chinese] score:" );
		scanf("%d",&s->chinese);
		printf("please input [math] score:" );
		scanf("%d",&s->math);
		printf("\n the modified record looks like: %s,%s ,name=%s, english=%d,chinese= %d,math=%d\n",s->term,s->class,s->stuname,s->english,s->chinese,s->math);


	}

}
void add(){

	score  s =(score)malloc(sizeof(scoreClass));
	printf("please input the [term] name (defalut:2010-0  [2010-1,2009-0,2009-1])" );
	gets(s->term);
	if (strlen(s->term)==0){
		strcpy(s->term,"2010-0");
	}
	printf("please input the [class] name (defalut:class1  [class2, class071,class072])" );
	gets(s->class);
	if (strlen(s->class)==0){
		strcpy(s->class,"class1");
	}

	printf("please input [student'name]:" );
	gets(s->stuname);
	printf("please input [english] score:" );
	scanf("%d",&s->english);
	printf("please input  [chinese] score:" );
	scanf("%d",&s->chinese);
	printf("please input [math] score:" );
	scanf("%d",&s->math);
	printf(" you just add a record :%s,%s ,name=%s, english=%d,chinese= %d,math=%d\n\n",s->term,s->class,s->stuname,s->english,s->chinese,s->math);

	list_add(list,s);

}
//这里排序用到了冒泡排序,
List  sort(List list){

	score s,s2;
	int i,j,avg1,avg2,len;
	len=list_sizeOf(list);
	//冒泡排序, 根据avgs 排indexs 的序
	for(i=0;i<len-1;i++){
		for(j=0;j<len-1-i;j++){
			s=list_get_at(list,j);
			s2=list_get_at(list,j+1);
			avg1= (s->english+s->chinese+s->math)/3;
			avg2= (s2->english+s2->chinese+s2->math)/3;
			if (avg1<avg2){
				list_swap(list,j,j+1);
			}
		}
	}

	return list;
}
/*
List  sort(List list){
 
	int indexs[len];
	float  	tmpAvg,avgs [len];  
	score s;
	int i,j,tmp;
	List newScores=list_create();
	//此次循环,计算平均值,并存入avgs 数组中,同时初始化下标索引数组indexs
	for(i=0;i<len;i++){
		indexs[i]=i;
		s=(score)list_get_at(list,i);//得到第i个成绩记录
		avgs[i]= (s->english+s->chinese+s->math)/3;
	}
	//冒泡排序, 根据avgs 排indexs 的序
	for(i=0;i<len-1;i++){
		for(j=0;j<len-1-i;j++){
			if (avgs[j]<avgs[j+1]){
				tmp=indexs[j];
				tmpAvg=avgs[j];
				indexs[j]=indexs[j+1];
				avgs[j]=avgs[j+1];
				indexs[j+1]=tmp;
				avgs[j+1]=tmpAvg;
			}
		}
	}

	// 根据indexs 中的值,得到相应的成绩记录,并顺序的存入一个新链表
	for(i=0;i<len;i++){
		list_add(newScores,(score)list_get_at(list,indexs[i]));
	}
	return newScores;
}
*/
void sum_avg(){
	int i;
	float sum,avg;
	List ss;
	score r,s;
	s =(score)malloc(sizeof(scoreClass));
	printf(" now we will get the total score and average score of a student in special class and term\n" );
	printf("please input the [term] name (defalut:2010-0  [2010-1,2010-0])" );
	gets(s->term);
	if (strlen(s->term)==0){
		strcpy(s->term,"2010-0");
	}
	printf("please input the [class] name (defalut:class1  [class2, class1])" );
	gets(s->class);
	if (strlen(s->class)==0){
		strcpy(s->class,"class1");
	}

	ss	=list_create();
	for(i=0;i<list_sizeOf(list);i++){
		r =(score)list_get_at(list,i);
		if (equals(r->class,s->class)&&equals(r->term,s->term)){
			list_add(ss,r);
		}

	}
	free(s);
	puts("\nthe unsorted scores looks like:\n");
	for(i=0;i<list_sizeOf(ss);i++){
		s =(score)list_get_at(ss,i);
		sum=s->english+s->chinese+s->math;
		avg=sum/3;
		printf("[%d]: %s,%s ,name=%s,sum=%f, avg=%f \n",i,s->term,s->class,s->stuname,sum,avg);
	}

	puts("\nthe sorted scores[depend on average score] looks like:\n");
	ss=sort(ss);//对成绩进行排序,
	//将排好序的成绩打印输出
	for(i=0;i<list_sizeOf(ss);i++){
		s =(score)list_get_at(ss,i);
		sum=s->english+s->chinese+s->math;
		avg=sum/3;
		printf("[%d]: %s,%s ,name=%s,sum=%f, avg=%f \n",i,s->term,s->class,s->stuname,sum,avg);
	}


}
void list_all(){
	int i;
	for (i=0;i<list_sizeOf(list);i++){
		score s =(score)list_get_at(list,i);
		printf("[%d] %s,%s ,name=%s, english=%d,chinese= %d,math=%d\n\n",i,s->term,s->class,s->stuname,s->english,s->chinese,s->math);
	}
}

void list_scores(){

	int i;
	List ss;
	float sum,avg;
	score s,r;
	s =(score)malloc(sizeof(scoreClass));
	printf(" now we will print all the scores in special class (default:list all   [class1 class2,all]):" );
	gets(s->class);
	ss	=list_create();
	//print all scores 
	if (strlen(s->class)==0||equals(s->class,"all")){
		list_all();
	}else {
		for (i=0;i<list_sizeOf(list);i++){
			r =(score)list_get_at(list,i);
			if (equals(s->class,r->class)){
				sum=s->english+s->chinese+s->math;
				avg=sum/3;
				printf("[%d] %s,%s ,name=%s, english=%d,chinese= %d,math=%d sum=%f,avg=%f\n\n",i,r->term,r->class,r->stuname,r->english,r->chinese,r->math,sum,avg);
			}

		}


	}



}
void query_stu(){
	int i;
	char name[20],cmd[10];
	score s;
	printf(" 1   :query all  depend on a  student'name\n" );
	printf(" 2   :query  students whose score is less than 60\n" );
	printf("input  number :");
	gets(cmd);
	if (isStartWith(cmd,"1")||strlen(cmd)==0){
		printf(" now we will query something depend a student's name , please input a \nstudent's name:" );
		gets(name);
		for(i=0;i<list_sizeOf(list);i++){
			s=list_get_at(list,i);
			if (equals(s->stuname,name)){
				printf("[%d] %s,%s ,name=%s, english=%d,chinese= %d,math=%d\n\n",i,s->term,s->class,s->stuname,s->english,s->chinese,s->math);
			}
		}
	}else {
		for(i=0;i<list_sizeOf(list);i++){
			s=list_get_at(list,i);
			if (s->chinese<60||s->english<60||s->math<60){
				printf("[%d] %s,%s   %s   chinese: %d, english:%d  ,math:%d \n",i,s->term,s->class,s->stuname,s->chinese ,s->english,s->math);

			}		}
	}
}
void list_names(){
	int i,j=0,exist=0;
	char class[20];
	score s ,r;
	List ss;
	printf("we will list all students'name in special class \n");
	printf("please input class name(default:class1   [class1 | class2 ] ) :");
	gets(class);
	if (strlen(class)==0){
		strcpy(class,"class1");
	}
	ss=list_create();
	for (i=0;i<list_sizeOf(list);i++){
		s=(score)list_get_at(list,i);
		if (equals(s->class,class)){
			for (j=0;j<list_sizeOf(ss);j++){
				r=(score)list_get_at(ss,j);
				if (equals(r->stuname,s->stuname)){
					exist=1;
					break;
				}
			}
			if (exist==0){
				list_add(ss,s);
			}
			exist=0;

		}
	}
	for (i=0;i<list_sizeOf(ss);i++){
		s=(score)list_get_at(ss,i);
		printf("%s\n",s->stuname);
	}
 
}
void handle_cmd(){

	char y_n, cmd[7];
	while (1){
		puts("\n\nplease input command :\nadd       :means add a new record of student's score \nmodify       :means change a record of a student \nsas       :means get the Sum  Average score and Sort the scores \nlist         :means list all scores  \nquery       :means query something depend on a student's name\nnames      menas list all the student's name in special class\n             (default class1  [class1|class2 or others you added])\nexit       : means  close the program  ");
		printf("input command(default:add):");
		getCmd(cmd);
		if(isStartWith(cmd ,"add")||strlen(cmd)==0){
			add();

			printf("add another one? (default y ,  [ y|n  ]):");
			y_n=getChar();
			while(y_n==10||y_n=='y'){
				flush();
				add();
				printf("add another one? (default y ,  [ y|n  ]):");
				y_n=getChar();
			} 
			if (y_n=='n'){
				flush();
			}
		}else if (isStartWith(cmd ,"modify")){
			modify();
		}else if (isStartWith(cmd ,"sas")){
			sum_avg();
		}else if  (isStartWith(cmd ,"list")){
			list_scores ();
		}else if  (isStartWith(cmd ,"query")){
			query_stu();
		}else if  (isStartWith(cmd ,"names")){
			list_names();
		}else if (isStartWith(cmd ,"exit")){
			break;
		}
	}


}
void initData(List list){
	int i =0; 
	int flag=1;
		char  buf[20];
	score s ;
	for (i=0;i<5;i++){
		//for (i=14;i>-1;i--){
		if (i%2==0){
			flag=-1;
		}else{
			flag=1;
		}
	s	=(score)malloc(sizeof(scoreClass));
	 
		sprintf(buf,"stuName_class1_%d",i);
		strcpy( s->stuname,buf);
		s->english=20+flag*1*i;
		s->math=60+flag*2*i;
		s->chinese=80+flag*3*i;
		sprintf(buf,"class1");
		strcpy( s->class,buf);
		sprintf(buf,"2010-0");
		strcpy( s->term,buf);
		list_add(list,s);
	}

	for (i=4;i>=0;i--){
		if (i%2==0){
			flag=-1;
		}else{
			flag=1;
		}
		 s =(score)malloc(sizeof(scoreClass));
	 
		sprintf(buf,"stuName_class2_%d",i);
		strcpy( s->stuname,buf);
		s->english=50+flag*1*i;
		s->math=50+flag*2*i;
		s->chinese=60+flag*3*i;
		sprintf(buf,"class2");
		strcpy( s->class,buf);
		sprintf(buf,"2010-0");
		strcpy( s->term,buf);
		list_add(list,s);
	}

	for (i=4;i>=0;i--){
		if (i%2==0){
			flag=-1;
		}else{
			flag=1;
		}
		  s =(score)malloc(sizeof(scoreClass));
	
		sprintf(buf,"stuName_class1_%d",i);
		strcpy( s->stuname,buf);
		s->english=50+flag*1*i;
		s->math=50+flag*2*i;
		s->chinese=50+flag*3*i;
		sprintf(buf,"class1");
		strcpy( s->class,buf);
		sprintf(buf,"2010-1");
		strcpy( s->term,buf);
		list_add(list,s);
	}

	for (i=4;i>=0;i--){
		if (i%2==0){
			flag=-1;
		}else{
			flag=1;
		}
	  s =(score)malloc(sizeof(scoreClass));
	
		sprintf(buf,"stuName_class2_%d",i);
		strcpy( s->stuname,buf);
		s->english=50+flag*1*i;
		s->math=50+flag*2*i;
		s->chinese=50+flag*3*i;
		sprintf(buf,"class2");
		strcpy( s->class,buf);
		sprintf(buf,"2010-1");
		strcpy( s->term,buf);
		list_add(list,s);
	}
	}
	int main(){
		list=list_create();//建一个空链表
		initData(list);//初始化数据, 
		list_all();//打印所有数据
		handle_cmd();//处理用户输入的命令,根据命令,管理学生的成绩
		return 0;
	}
