
typedef *void Void;
struct BTreeNodeStruct{
	int data;
	struct BTreeNodeStruct *left;
	struct BTreeNodeStruct *right;
}
typedef struct BTreeNodeStruct BTreeNodeClass;
typedef BTreeNodeClass *BTreeNode;
typedef BTreeNodeClass *BTree;

BTree btree_create(int *datas,int len){
   BTree node;
	int i ;
	for(i=0;i<len;i++){
	     node= (BTree)malloc(sizeof(BTreeNodeClass));
      

	}



}


