//file name : avl_tree.c
//created at: 2012年06月03日 星期日 22时40分51秒
//author:  纪秀峰

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>
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


void avl_make_node(Item item,avl_node_t **node){
  avl_node_t* n;
  n=(avl_node_t*)malloc(sizeof(avl_node_t));
  n->left=NULL;
  n->right=NULL;
  n->height=0;
  n->item=item;
  *node=n;
}

avl_node_t* avl_node_add(avl_node_t* parent,Item item){
  avl_node_t *new_node;
  avl_make_node(item,&new_node);
  if(!parent){
    return new_node;
  }
}
void avl_add(avl_tree_t* avl,Item item){
  avl_node_add(avl->root,item);
}

void avl_free_node(avl_node_t *node){
  free(node);
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

int main(int argc, char *argv[]){
  test_avl_single_right_rotate();
  test_avl_single_left_rotate();
  test_right_left_rotate();
  test_left_right_rotate();
  return 0;
}
