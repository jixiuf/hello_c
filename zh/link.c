#include<stdio.h>
#include<stdlib.h>
#include<list.h>

/**get last node */
ListNode getLastListNode(ListNode head){
	if (head==NULL){
		return NULL;
	}
	if (head->next==NULL){
		return head;
	}
	ListNode n=head;
	while (n->next!=NULL){
		n=n->next;
	}
	return n;
}



ListNode getListNode(ListNode head,int index){
	if(index<0||head==NULL){
		return NULL;
	}
	ListNode n=head;
	int i=0;
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
	if (listNode==NULL){
		return 0;
	}
	ListNode n =listNode;
	int i =0;
	while (n!=NULL){
		i++;
		n=n->next;
	}
	return i;
}
ListNode createNewNode(Void ele){
	ListNode newNode=(ListNode)malloc(sizeof(ListNodeClass));
	if (newNode==NULL) return ;
	newNode->next=NULL;
	newNode->ele=ele;
	return newNode;
}
ListNode mergeListNodeAt(ListNode head ,int index ,ListNode tail){
	if (head==NULL) return tail ;
	ListNode nLast=getLastListNode(tail);
	if (index==-1){
		nLast->next=head;
		return  tail;
	}
	ListNode indexListNode = getListNode(head,index);
	if (indexListNode==NULL){ //index 越界,
		ListNode headLastNode=getLastListNode(head);
		headLastNode->next=tail;
		return  head;
	}
	ListNode nextListNode=indexListNode->next;
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
    if(tailList==NULL||headList==NULL) return;
	ListNode head=headList->nodes;
	ListNode n=tailList->nodes;
	ListNode nLast=getLastListNode(n);
	if (index==-1){
		nLast->next=head;
		headList->size+=tailList->size;
        headList->nodes=n;
		return ;
	}
	ListNode indexListNode = getListNode(head,index);
	if (indexListNode==NULL){ //为NULL 有两种情况,一种是head==NULL, 另一种是index 越界,
		if (head==NULL){//如果head 是NULL, 则返回n ,相当于head 原本的长度为0,
				headList->size=tailList->size;
				headList->nodes=n;
			return ;
		}else{//另一种是index 越界, 则直接将n添加到head 末尾
			ListNode headLastNode=getLastListNode(head);
			headList->size+=tailList->size;
			headLastNode->next=n;
			return ;
		}

	}
	ListNode nextListNode=indexListNode->next;
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
	ListNode pro= getListNode(head,index-1);
	if(pro==NULL){//如果index 越界,则不删除任何元素
		return ;
	}
	ListNode n= pro->next;
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
	ListNode listNode=list->nodes;
	if (listNode==NULL||index<0){
		return ;
	}
	ListNode indexNode=getListNode(listNode,index);
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
/*
int main(){
	List list=list_create();
	printf("size=%d\n",list_sizeOf(list));
	int i ;
	for(i=0;i<10;i++){
		int *j =(int*)malloc(sizeof(int)) ;
		*j=i;
		list_add(list,j);
	}
	for(i=0;i<list_sizeOf(list);i++){
		int *j=list_get_at(list,i);
		printf("j=%d\n",*j);
	}
	printf("size=%d\n",list_sizeOf(list));

	list_delete_at(list,0);
	list_delete_at(list,3);
	list_delete_last(list);
	for(i=0;i<list_sizeOf(list);i++){
		int *j=list_get_at(list,i);
		printf("j=%d\n",*j);
	}
	printf("size=%d\n",list_sizeOf(list));
 list_free(list);
list=NULL;
 list=list_create();
List list2=list_create();
	for(i=0;i<10;i++){
		int *j =(int*)malloc(sizeof(int)) ;
		*j=i;
	list_add(list,j);
		list_add(list2,j);
	}
    //list_merge_at(list,9,list2);
list_append(list,list2);
	for(i=0;i<list_sizeOf(list);i++){
		int *j=list_get_at(list,i);
		printf("j=%d\n",*j);
	}
	printf("size=%d\n",list_sizeOf(list));

list_inverse(list);
	for(i=0;i<list_sizeOf(list);i++){
		int *j=list_get_at(list,i);
		printf("j=%d\n",*j);
	}
int *q=    list_get_last(list);
printf("%d\n",*q);
q=    list_get_at(list,2);
printf("%d\n",*q);
}
*/
