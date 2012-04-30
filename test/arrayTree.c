#include<stdio.h>
void create_btree(int *b_tree,int *nodelist,int len){
	int i=0;
	int level=1 ;
	b_tree[1]=nodelist[1];
 for(i=0;i<16;i++){
     printf("%d\n",nodelist[i]);
}
	for (i=2;i<15;i++){
		level=1;
		while( b_tree[level]!=0){
printf("nodelist_%d=%d,b_tree[%d]=%d\n",i,nodelist[i],level,b_tree[level]);
			if (nodelist[i]<b_tree[level])
				level=level*2;
			else
				level=level*2+1;
		}
		b_tree[level]=nodelist[i];
printf("b_tree[%d]=%d\n",level,b_tree[level]);
	}


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
