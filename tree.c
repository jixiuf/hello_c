#include <malloc.h>
#include <stdio.h>

typedef int Item;

static int item_cmp(Item *i1, Item *i2){
  int *i1_int = (int*) i1;
  int *i2_int = (int*) i2;
  return (*i1_int - *i2_int);
}

struct node {
  Item item;
  struct node * left;
  struct node * right;
};

typedef struct node node_t;

struct tree{
  node_t * root;
  int size;
};

typedef struct tree tree_t;

int tree_add_node(node_t *parent,node_t *n){
  int cmp=item_cmp(&(parent->item),&(n->item));
  if (cmp>0){
    if(parent->left==NULL){
      parent->left=n;
      return 0;
    }else{
      return tree_add_node(parent->left,n);
    }
  }else if (cmp<0){
    if (parent->right==NULL){
      parent->right=n;
      return 0;
    }else{
      return tree_add_node(parent->right,n);
    }
  }else{                        /* 说明parent与n所含item 同值， 不允许同值item的存在，添加失败 */
    return -1;
  }
}

void tree_init(tree_t *root){
  root->root=NULL;
  root->size=0;
}

/* 向tree添加节点,成功返回0,失败返回-1 */
int tree_add(tree_t *root,Item item){
  node_t *new_node;
  int ret=-1;
  if (make_node(&item,&new_node)!=-1){
    if(root->root==NULL){
      root->root=new_node;
      root->size++;
      ret=0;
    }else{
      ret=tree_add_node(root->root,new_node);
      if(ret ==0){
        root->size++;
      }
    }
  }else{
    ret= -1;                  /* 如创建节点不成功 */
  }
  return ret;
}

int make_node(Item *item,node_t **new_node){
  node_t* t=(node_t*)malloc(sizeof(node_t));
  if(t!=NULL){
    t->right=NULL;
    t->left=NULL;
    t->item=*item;
    *new_node = t;
    return 0;
  }
  return -1;
}


int main(int argc, char *argv[]){
  tree_t t ;
  tree_init(&t);
  Item i = 10;
  tree_add(&t,i);
  tree_add(&t,100);
  tree_add(&t,5);
  tree_add(&t,95);
  printf ("%d\n",t.size);
  printf ("%d\n",t.root->item);
  printf ("%d\n",t.root->right->item);
  printf ("%d\n",t.root->right->left->item);
  printf ("%d\n",t.root->left->item);
  return 0;
}
