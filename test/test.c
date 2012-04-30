#include<stdio.h>
struct tree{
 int left,
  int data,
int right;
}
typedef struct tree treenode;
treenode b_tree[15];

void create_btree(int *b_tree,int *nodelist,int len){
}
int main(){
	int i,index;
	int data;
	int b_tree[16];
	int nodelist[16]={6,3,8,2,5,7,9,0,0,4,0,0,0,0,10};
	index=0;
	for (i=0;i<16;i++){
		b_tree[i]=0;
	}
	index=15;
	create_btree(b_tree,nodelist,index);
}
