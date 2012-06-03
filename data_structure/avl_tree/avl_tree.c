//file name : avl_tree.c
//created at: 2012年06月03日 星期日 22时40分51秒
//author:  纪秀峰

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

typedef int Item;

struct avl_node {
  Item item;
  struct avl_node * left;
  struct avl_node * right;
  int height;
};

typedef struct avl_node avl_node_t;

struct avl_tree{
  avl_node_t * root;
  int size;
  int (*item_cmp)(Item* item1,Item* item2);
};

typedef struct avl_tree avl_tree_t;

/* 对于
     ##a                 ###
     #b#    ------>      #b#
     c##                 c#a
 类型的转换,转换后返回b 的指针
 b如果有右子树，则旋转后成为 a的左子树(为什么要考虑b有没有子树呢， 因为以 b为轴旋转)
 */
avl_node_t *avl_single_right_rotate(avl_node_t* node){
  avl_node_t* b=node->left;
  node->left=b->right;
  b->right=node;
  return b;
}

/* 对于
     a##                 ###
     #b#    ------>      #b#
     ##c                 a#c
     如果b有左子树，则旋转后成为a的右子树(为什么要考虑b有没有子树呢， 因为以 b为轴旋转)
 */
avl_node_t *avl_single_left_rotate(avl_node_t* node){
  avl_node_t* b=node->right;
  node->right=b->left;
  b->left=node;
  return b;
}


/* 先右旋，后左旋
     a##        a##         ###
     #b#------> #c#-------> #c#
     c##        ##b         a#b
     第一轮旋转(右旋)，如果c有右子树，则旋转后，成为b的左子树(首轮旋转与a无关,以b为轴，使c转到轴心处)
     第二转旋转(左旋),c有左子树(比c小，比a大)，则旋转后，成为a的右子树(以c为轴)
 */
avl_node_t *avl_right_left_rotate(avl_node_t* a){
  avl_node_t* b=a->right;
  avl_node_t* c=b->left;

  b->left=c->right;
  c->right= b;
  /* 第二轮 */
  a->right=c->left;
  c->left=a;
  return c;
}
/* 先左旋，后右旋
     ##a        ##a         ###
     #b#------> #c#-------> #c#
     ##c        b##         b#a
     第一轮旋转(左旋)，如果c有左子树(比c小，比b大)，则旋转后，成为b的右子树(首轮旋转与a无关,以b为轴，使c转到轴心处)
     第二转旋转(右旋),c有右子树(比c大，比a小)，则旋转后，成为a的左子树(以c为轴)
 */
avl_node_t *avl_left_right_rotate(avl_node_t* a){
  avl_node_t* b=a->left;
  avl_node_t* c=b->right;

  b->right=c->left;
  c->left= b;
  /* 第二轮 */
  a->left=c->right;
  c->right=a;
  return c;
}


void avl_add(avl_tree_t* avl,Item item){

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

  a.left=&b;
  a.right=NULL;

  b.left=&c;
  b.right=NULL;

  c.right=NULL;
  c.left=NULL;
  result= avl_single_right_rotate(&a);
  printf ("%d,%d,%d\n",result->item,result->left->item,result->right->item);

  return 0;
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

  a.right=&b;
  a.left=NULL;

  b.right=&c;
  b.left=NULL;

  c.right=NULL;
  c.left=NULL;
  result= avl_single_left_rotate(&a);
  printf ("%d,%d,%d\n",result->item,result->left->item,result->right->item);

  return 0;
}


/* 先右旋，后左旋
     a##        a##         #c#
     #b#------> #c#-------> a#b
     c##        ##b         ###
     第一轮旋转(右旋)，如果c有右子树，则旋转后，成为b的左子树(首轮旋转与a无关)
     第二转旋转(左旋),c有左子树(比c小，比a大)，则旋转后，成为a的右子树
 */
int test_right_left_rotate(){
  avl_node_t a,b,c,*result,cr,cl;
  a.item=5;
  b.item =10;
  c.item=8;

  a.right=&b;
  a.left=NULL;

  b.left=&c;
  b.right=NULL;


  cr.item=9;
  cl.item=6;
  c.right=&cr;
  c.left=&cl;

  result= avl_right_left_rotate(&a);
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
 */
int test_left_right_rotate(){
  avl_node_t a,b,c,*result,cr,cl;
  a.item=10;
  b.item =5;
  c.item=8;

  a.left=&b;
  a.right=NULL;

  b.right=&c;
  b.left=NULL;


  cr.item=9;
  cl.item=6;
  c.right=&cr;
  c.left=&cl;

  result= avl_left_right_rotate(&a);
  printf ("%d,%d,%d,%d,%d\n",
          result->item,
          result->left->item,
          result->right->item,
          result->right->left->item,
          result->left->right->item);

  return 0;

}

int main(int argc, char *argv[]){
  test_avl_single_right_rotate();
  test_avl_single_left_rotate();
  test_right_left_rotate();
  test_left_right_rotate();
   return 0;
}
