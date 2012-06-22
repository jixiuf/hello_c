//file name : avl_tree.c
//created at: 2012年06月03日 星期日 22时40分51秒
//author:  纪秀峰

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>
#include "avl_tree.h"


int avl_max_height(int height1,int height2){
  return height1>height2?height1:height2;
}
int avl_node_height(avl_node_t* node){
  if(node){
    return node->height;
  }
  return -1;
}
/* 对于
     ##a                 ###
     #b#    ------>      #b#
     c##                 c#a
 类型的转换,转换后返回b 的指针
 b如果有右子树，则旋转后成为 a的左子树(为什么要考虑b有没有子树呢， 因为以 b为轴旋转)
 在旋转的过程中除c外，a、b节点的高度发生变化
 */
avl_node_t *avl_single_right_rotate(avl_node_t* a){
  avl_node_t* b=a->left;
  a->left=b->right;
  b->right=a;
  a->height=1+avl_max_height(avl_node_height(a->right),avl_node_height(a->left));
  b->height=1+avl_max_height(avl_node_height(b->left),avl_node_height(b->right));
  return b;
}

/* 对于
     a##                 ###
     #b#    ------>      #b#
     ##c                 a#c
     如果b有左子树，则旋转后成为a的右子树(为什么要考虑b有没有子树呢， 因为以 b为轴旋转)
 */
avl_node_t *avl_single_left_rotate(avl_node_t* a){
  avl_node_t* b=a->right;
  a->right=b->left;
  b->left=a;
  a->height =1+avl_max_height(avl_node_height(a->left),avl_node_height(a->right));
  b->height =1+avl_max_height(avl_node_height(b->left),avl_node_height(b->right));
  return b;
}


/* 先右旋，后左旋
     a##        a##         ###
     #b#------> #c#-------> #c#
     c##        ##b         a#b
     第一轮旋转(右旋)，如果c有右子树，则旋转后，成为b的左子树(首轮旋转与a无关,以b为轴，使c转到轴心处)
     第二转旋转(左旋),c有左子树(比c小，比a大)，则旋转后，成为a的右子树(以c为轴)
   5            5                 8
      10->         8           5    10
    8            6  10          6  9
   6 9             9
 */
avl_node_t *avl_right_left_rotate(avl_node_t* a){
  a->right=avl_single_right_rotate(a->right);
  return avl_single_left_rotate(a);
}

/* avl_node_t *avl_right_left_rotate(avl_node_t* a){ */
/*   avl_node_t* b=a->right; */
/*   avl_node_t* c=b->left; */

/*   b->left=c->right; */
/*   c->right= b; */
/*   b->height=1+avl_max_height(avl_node_height(b->left),avl_node_height(b->right)); */
/*   c->height=1+avl_max_height(avl_node_height(c->left),avl_node_height(c->right)); */
/*   /\* 第二轮 *\/ */
/*   a->right=c->left; */
/*   c->left=a; */
/*   a->height =1+avl_max_height(avl_node_height(a->left),avl_node_height(a->right)); */
/*   c->height =1+avl_max_height(avl_node_height(c->left),avl_node_height(c->right)); */
/*   return c; */
/* } */
/* 先左旋，后右旋
     ##a        ##a         ###
     #b#------> #c#-------> #c#
     ##c        b##         b#a
     第一轮旋转(左旋)，如果c有左子树(比c小，比b大)，则旋转后，成为b的右子树(首轮旋转与a无关,以b为轴，使c转到轴心处)
     第二转旋转(右旋),c有右子树(比c大，比a小)，则旋转后，成为a的左子树(以c为轴)
 */

avl_node_t *avl_left_right_rotate(avl_node_t* a){
  a->left=avl_single_left_rotate(a->left);
  return avl_single_right_rotate(a);
}
/* 注释的这段代码可用，但罗嗦 */
/* avl_node_t *avl_left_right_rotate(avl_node_t* a){ */
/*   avl_node_t* b=a->left; */
/*   avl_node_t* c=b->right; */

/*   b->right=c->left; */
/*   c->left= b; */
/*   b->height=1+avl_max_height(avl_node_height(b->left),avl_node_height(b->right)); */
/*   c->height=1+avl_max_height(avl_node_height(c->left),avl_node_height(c->right)); */

/*   /\* 第二轮 *\/ */
/*   a->left=c->right; */
/*   c->right=a; */
/*   a->height =1+avl_max_height(avl_node_height(a->left),avl_node_height(a->right)); */
/*   c->height =1+avl_max_height(avl_node_height(c->left),avl_node_height(c->right)); */
/*   return c; */
/* } */


int avl_make_node(Item item,avl_node_t **node){
  avl_node_t* n;
  n=(avl_node_t*)malloc(sizeof(avl_node_t));
  if(n){
    n->left=NULL;
    n->right=NULL;
    n->height=0;
    n->item=item;
    *node=n;
    return 0;
  }
  return -1;
}


void avl_free_node(avl_node_t *node){
  free(node);
}

int avl_node_add(avl_node_t** parent,Item item,int (*item_cmp)(Item* item1,Item* item2)){
  avl_node_t *new_node;
  int cmp,ret;
  if(avl_make_node(item,&new_node)!=-1){
    if(*parent){
      cmp=item_cmp(&((*parent)->item),&item);
      if(cmp>0){              /* 插入到左子树中 */
        ret=avl_node_add(&((*parent)->left),item,item_cmp);
        if(ret>-1){
          if(2==avl_node_height((*parent)->left)-avl_node_height((*parent)->right)){ /* 如果左右不平衡 */
            if(item_cmp(&item,&((*parent)->left->item))>0){ /* >0  ,插入到左子树的右子树中 */
              *parent=avl_left_right_rotate(*parent);
            }else{ /* <0的情况 (不会出现==0的情况，==0时不会出现不平衡),插入到左子树的左子树中 */
              *parent=avl_single_right_rotate(*parent);
            }
            /* *parent->height= 1+ avl_max_height() */
          }
        }else{
          return ret;
        }
      }else if(cmp<0){              /* 插入到右子树中 */
        ret=avl_node_add(&(*parent)->right,item,item_cmp);
        if(ret>-1){
          if(2==avl_node_height((*parent)->right)-avl_node_height((*parent)->left)){ /* 如果左右不平衡 */
            if(item_cmp(&item,&((*parent)->right->item))>0){ /* >0  ,插入到右子树的右子树中 */
              *parent=avl_single_right_rotate(*parent);
            }else{ /* <0的情况 (不会出现==0的情况，==0时不会出现不平衡),插入到右子树的左子树中 */
              *parent=avl_right_left_rotate(*parent);
            }
          }
        }else{
          return ret;
        }

      }else{                  /* 暂不支持重复元素 */
        avl_free_node(new_node);
        return -1;
      }
    }else{
      *parent=new_node;
    }
    (*parent)->height= 1+ avl_max_height(avl_node_height((*parent)->left),avl_node_height((*parent)->right));
    return 0;
  }else{
    return -1;
  }
}
int avl_add(avl_tree_t* avl,Item item){
  int ret=avl_node_add(&(avl->root),item,avl->item_cmp);
  if(ret!= -1){
    avl->size++;
  }
  return ret;
}

void avl_init(avl_tree_t* tree,int (*item_cmp)(Item* item1,Item* item2)){
  tree->size=0;
  tree->root=NULL;
  tree->item_cmp=item_cmp;
}

int avl_size(avl_tree_t * avl){
  return avl->size;
}

int avl_seek(int (*item_cmp)(Item* item1,Item* item2) ,avl_node_t *parent ,Item item,avl_node_t **no,avl_node_t **par){
  avl_node_t *p,*n;
  int cmp;
  if(parent==NULL) return -1;
  p=NULL;
  n=parent;
  while(n!=NULL){
    cmp=item_cmp(&(n->item),&item);
    if(cmp==0){                    /* found */
      *no=n;
      *par=p;
      return 0;
    }else if (cmp<0){
      p=n;
      n=n->right;
    }else{
      p=n;
      n=n->left;
    }
  }
  return -1;
}

int avl_find(avl_tree_t *root,Item item,Item *out){
  avl_node_t *n;
  int cmp;
  if(root->root==NULL) return -1;
  n=root->root;
  while(n!=NULL){
    cmp=root->item_cmp(&(n->item),&item);
    if(cmp==0){                    /* found */
      *out=n->item;
      return 0;
    }else if (cmp<0){
      n=n->right;
    }else{
      n=n->left;
    }
  }
  return -1;
}
int avl_del(avl_tree_t* tree,Item item){
  int found,lh,rh;
  avl_node_t *n,*p,*n1,*p1,*tmp;
  found=avl_seek(tree->item_cmp,tree->root , item,&n,&p);
  if(-1==found){
    return -1;                  /* 未找到，无从删起 */
  }
  /* if(p==NULL){ */
  /*   avl_free_node(tree->root); */
  /*   tree->root=NULL; */
  /*   tree->size--; */
  /*   return 0; */
  /* } */
  if(n->left==NULL &&n->right==NULL){ /* 无子女 */
    if(p==NULL){
      tree->root=NULL;
    }else if (p->left==n){
      p->left=NULL;
      /* lr=avl_node_height(p->right); */
      /* if(lr==-1){               /\* 若无右节点，则删除左节点，会使树高-1 *\/ */

      /* } */
    }else if (p->right==n){
      p->right=NULL;
    }
  }else if(n->left==NULL &&n->right!=NULL){ /* 无左子树 */
    if(p==NULL){
      tree->root=n->right;
    }else if (p->left==n){
      p->left=n->right;
    }else if (p->right==n){
      p->right=n->right;
    }
  }else if(n->left!=NULL &&n->right==NULL){ /* 无右子树 */
    if(p==NULL){
      tree->root=n->left;
    }else if (p->left==n){
      p->left=n->left;
    }else if (p->right==n){
      p->right=n->left;
    }
  }else if(n->left!=NULL &&n->right!=NULL){ /* 有左右子树 */
    tree_largest(n->left,&n1,&p1);
    if(p1==NULL){               /* n->left节点 就是左子树中最大的元素,即n->left无右子树 */
      p1=n;
    }
    /* 把n1,从原处移除 */
    if(p1->left==n1){
      p1->left=n1->left;
    }else if(p1->right==n1){
      p1->right=n1->left;
    }
    /* n1->left=NULL; */
    /* n1->right=NULL; */
    /* 把n1 移动新位置 */
    if(p==NULL){
      tree->root=n1;
    }else if(p->left==n) {
      p->left=n1;
    }else if(p->right==n) {
      p->left=n1;
    }
    n1->left=n->left;
    n1->right=n->right;
  }
  avl_free_node(n);
  tree->size--;
  return 0;
}

/* private 从parent树中寻找最大的node,存到no中，其父节点存到par中，若无父，则par=NULL ,
   只需一路寻找右节点，直到null即寻到最大值
 */
int tree_largest(avl_node_t *parent ,avl_node_t **no,avl_node_t **par){
  avl_node_t *p,*n;
  p=NULL;
  n=parent;
  if(parent==NULL){
    *no=NULL;
    *par=NULL;
    return -1;
  }
  while(n->right!=NULL){
    p=n;
    n=n->right;
  }
  *no=n;
  *par=p;
  return 0;
}

/* int avl_del_node(avl_node_t *node,Item item,int (*item_cmp)(Item* item1,Item* item2)){ */
/* } */


int int_cmp(Item *i1, Item *i2){
  int *i1_int = (int*) i1;
  int *i2_int = (int*) i2;
  return (*i1_int - *i2_int);
}
/*del 6
           10               10
       6       20 ->     3      20
     3       15               15
 */
void test_avl_del5(){           /* test no right sub tree */
  avl_tree_t tree;
  avl_init(&tree,int_cmp);
  avl_add(&tree,10);
  avl_add(&tree,6);
  avl_add(&tree,20);
  avl_add(&tree,3);
  avl_add(&tree,15);
  assert(0==avl_del(&tree,6));
  assert(4==avl_size(&tree));
  assert(10==tree.root->item);
  assert(20==tree.root->right->item);
  assert(3==tree.root->left->item);
}

/*del 6
           10               10
       6       20 ->     4      20
     3   8    15       3   8   15
   2 4               2
 */
void test_avl_del4(){
  avl_tree_t tree;
  avl_init(&tree,int_cmp);
  avl_add(&tree,10);
  avl_add(&tree,6);
  avl_add(&tree,20);
  avl_add(&tree,8);
  avl_add(&tree,3);
  avl_add(&tree,15);
  avl_add(&tree,2);
  avl_add(&tree,4);
  assert(0==avl_del(&tree,6));
  assert(7==avl_size(&tree));
  assert(10==tree.root->item);
  assert(20==tree.root->right->item);
  assert(4==tree.root->left->item);
  assert(3==tree.root->left->left->item);
  assert(8==tree.root->left->right->item);
  assert(2==tree.root->left->left->left->item);
}

void test_avl_del3(){           /* test del root element */
  avl_tree_t tree;
  avl_init(&tree,int_cmp);
  avl_add(&tree,10);
  avl_add(&tree,9);
  avl_add(&tree,11);
  assert(0==avl_del(&tree,10));
  assert(2==avl_size(&tree));
  assert(9==tree.root->item);
  assert(11==tree.root->right->item);
}

void test_avl_del2(){           /* test del root element */
  avl_tree_t tree;
  avl_init(&tree,int_cmp);
  avl_add(&tree,10);
  assert(0==avl_del(&tree,10));
  assert(0==avl_size(&tree));
}

void test_avl_del(){
  avl_tree_t tree;
  avl_init(&tree,int_cmp);
  avl_add(&tree,10);
  assert(-1==avl_del(&tree,100));
  assert(1==avl_size(&tree));
}


/*
     ##5                 #4#
     #4#    ------>      3#5
     3##                 ###
 */
int test_avl_single_right_rotate(){
  avl_node_t a,b,c,*result;
  a.item=5;
  b.item =4;
  c.item=3;

  a.height=2;
  a.left=&b;
  a.right=NULL;

  b.height=1;
  b.left=&c;
  b.right=NULL;

  c.height=0;
  c.right=NULL;
  c.left=NULL;
  result= avl_single_right_rotate(&a);

  assert(4==result->item);
  assert(3==result->left->item);
  assert(5==result->right->item);
  assert(0==a.height);
  assert(1==b.height);
  assert(0==c.height);
  printf ("test_avl_single_right_rotate:");
  printf ("%d,%d,%d\n",result->item,result->left->item,result->right->item);
}

/*
     1##                 #2#
     #2#    ------>      1#3
     ##3                 ###
 */
int test_avl_single_left_rotate(){
  avl_node_t a,b,c,*result;
  a.item=1;
  b.item =2;
  c.item=3;

  a.height=2;
  a.right=&b;
  a.left=NULL;

  b.height=1;
  b.right=&c;
  b.left=NULL;

  c.height=0;
  c.right=NULL;
  c.left=NULL;
  result= avl_single_left_rotate(&a);
  printf ("test_avl_single_left_rotate:");
  assert(2==result->item);
  assert(1==result->left->item);
  assert(3==result->right->item);
  assert(1==result->height);
  assert(0==result->left->height);
  assert(0==result->right->height);
  printf ("%d,%d,%d\n",result->item,result->left->item,result->right->item);

  return 0;
}


/* 先右旋，后左旋
     a##        a##         #c#
     #b#------> #c#-------> a#b
     c##        ##b         ###
     第一轮旋转(右旋)，如果c有右子树，则旋转后，成为b的左子树(首轮旋转与a无关)
     第二转旋转(左旋),c有左子树(比c小，比a大)，则旋转后，成为a的右子树

   5              8
      10->     5    10
    8           6  9
   6 9
*/
int test_right_left_rotate(){
  avl_node_t a,b,c,*result,cr,cl;
  a.item=5;
  b.item =10;
  c.item=8;

  a.height=3;
  a.right=&b;
  a.left=NULL;

  b.height=2;
  b.left=&c;
  b.right=NULL;


  cr.item=9;
  cr.height=0;
  cr.left=NULL;
  cr.right=NULL;

  cl.item=6;
  cl.height=0;
  cl.left=NULL;
  cl.right=NULL;

  c.height=1;
  c.right=&cr;
  c.left=&cl;

  result= avl_right_left_rotate(&a);
  printf ("test_right_left_rotate:");

  assert(8==result->item);
  assert(5==result->left->item);
  assert(10==result->right->item);
  assert(9==result->right->left->item);
  assert(6==result->left->right->item);

  assert(0==cr.height);
  assert(0==cl.height);
  assert(1==a.height);
  assert(1==b.height);
  assert(2==c.height);


  printf ("%d,%d,%d,%d,%d\n",
          result->item,
          result->left->item,
          result->right->item,
          result->right->left->item,
          result->left->right->item);

  return 0;

}
/* 先左旋，后右旋
     ##a        ##a         ###
     #b#------> #c#-------> #c#
     ##c        b##         b#a
     第一轮旋转(左旋)，如果c有左子树(比c小，比b大)，则旋转后，成为b的右子树(首轮旋转与a无关,以b为轴，使c转到轴心处)
     第二转旋转(右旋),c有右子树(比c大，比a小)，则旋转后，成为a的左子树(以c为轴)
     10              10             8
  5                 8             5    10
    8           5        9          6 8
   6 9            6
 */
int test_left_right_rotate(){
  avl_node_t a,b,c,*result,cr,cl;
  a.item=10;
  b.item =5;
  c.item=8;

  a.left=&b;
  a.right=NULL;
  a.height=3;


  b.right=&c;
  b.left=NULL;
  b.height=2;

  cr.item=9;
  cr.left=NULL;
  cr.right=NULL;
  cr.height=0;

  cl.item=6;
  cl.left=NULL;
  cl.right=NULL;
  cl.height=0;

  c.height=1;
  c.right=&cr;
  c.left=&cl;

  result= avl_left_right_rotate(&a);
  assert(0==cr.height);
  assert(0==cl.height);
  assert(1==a.height);
  assert(1==b.height);
  assert(2==c.height);

  printf ("test_left_right_rotate:%d,%d,%d,%d,%d\n",
          result->item,
          result->left->item,
          result->right->item,
          result->right->left->item,
          result->left->right->item);

  return 0;

}

/*
     10           5
   5    --->    2  10
 2                    18

 */
void test_avl_add(){
  avl_tree_t tree;
  avl_init(&tree,int_cmp);
  avl_add(&tree,10);
  avl_add(&tree,5);
  avl_add(&tree,2);
  avl_add(&tree,18);
  assert(5==tree.root->item);
  assert(2==tree.root->left->item);
  assert(10==tree.root->right->item);
  assert(18==tree.root->right->right->item);

  assert(2==tree.root->height);
  assert(0==tree.root->left->height);
  assert(1==tree.root->right->height);
  assert(0==tree.root->right->right->height);
}
/*
     10           5                    5
   5    --->    2  10   ---->      2      16
 2                    18                10  18
 */

void test_avl_add2(){
  avl_tree_t tree;
  avl_init(&tree,int_cmp);
  avl_add(&tree,10);
  avl_add(&tree,5);
  avl_add(&tree,2);
  avl_add(&tree,18);
  avl_add(&tree,16);
  assert(5==tree.root->item);
  assert(2==tree.root->left->item);
  assert(16==tree.root->right->item);
  assert(18==tree.root->right->right->item);
  assert(10==tree.root->right->left->item);

  assert(2==tree.root->height);
  assert(0==tree.root->left->height);
  assert(1==tree.root->right->height);
  assert(0==tree.root->right->right->height);
  assert(0==tree.root->right->left->height);
}

/*
     10           5                    5                    5                   5                10
   5    --->    2  10   ---->      2      16 ---->       2    16       --->   2    10          5    16
 2                    18                10  18              10   18               8  16       2  8     18
                                                           8                            18
 */

void test_avl_add3(){
  avl_tree_t tree;
  avl_init(&tree,int_cmp);
  avl_add(&tree,10);
  avl_add(&tree,5);
  avl_add(&tree,2);
  avl_add(&tree,18);
  avl_add(&tree,16);
  avl_add(&tree,8);
  assert(10==tree.root->item);
  assert(5==tree.root->left->item);
  assert(16==tree.root->right->item);
  assert(2==tree.root->left->left->item);
  assert(8==tree.root->left->right->item);
  assert(16==tree.root->right->item);
  assert(18==tree.root->right->right->item);

  assert(2==tree.root->height);
  assert(1==tree.root->left->height);
  assert(1==tree.root->right->height);
  assert(0==tree.root->left->left->height);
  assert(0==tree.root->left->right->height);
  assert(0==tree.root->right->right->height);
}

void test_avl_find(){
  Item out;
  avl_tree_t tree;
  avl_init(&tree,int_cmp);
  avl_add(&tree,10);
  avl_add(&tree,5);
  avl_add(&tree,2);
  avl_add(&tree,18);
  avl_add(&tree,16);
  avl_add(&tree,8);

  assert(-1 == avl_find(&tree,100,&out));

  assert(0 == avl_find(&tree,5,&out));
  assert(5 ==out);
  assert(0 == avl_find(&tree,10,&out));
  assert(10 ==out);
}

int main(int argc, char *argv[]){
  test_avl_single_right_rotate();
  test_avl_single_left_rotate();
  test_right_left_rotate();
  test_left_right_rotate();
  test_avl_add();
  test_avl_add2();
  test_avl_add3();
  test_avl_find();
  test_avl_del();
  test_avl_del2();
  test_avl_del3();
  test_avl_del4();
  test_avl_del5();
  return 0;
}
