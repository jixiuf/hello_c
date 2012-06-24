/* 红黑树 */
/* 红黑树的几个性质: */
/*     1) 每个结点只有红和黑两种颜色 */
/*     2) 根结点是黑色的 */
/*     3)空节点是黑色的（红黑树中，根节点的parent以及所有叶节点lchild、rchild都不指向NULL，而是指向一个定义好的空节点）。  */
/*     4) 如果一个结点是红色的,那么它的左右两个子结点的颜色是黑色的 */
/*     5) 对于每个结点而言,从这个结点到叶子结点的任何路径上的黑色结点的数目相同 */
/*
             D
           B  C
         A
  插入的分析，对于新插入的元素A，默认它是红色的
  1). 如果A的父节点是黑元素，则一切正常 ，不需要变换，
  2). 如果A的父节点B是红元素(可推出祖父D为黑)，则需要将父节点B变成黑元素，以维护性质4
  但是B变成黑元素后，此子树上因多了此黑元素，导致性质5不成立.()
  处理方法需要节点B的兄弟节点C(即A的uncle)的颜色而定
  2.1). 如果C为红)，则将C变成黑,然后把祖父D变成红,此时D变成红色，做法与初插入A时的处理方法一样
  ，向上依次检测是否有冲突
  2.2). 如果C为黑色，此种情况相对简单，只需要对ABD进行旋转，使A、D成为B的子节点
      此时
          D(黑)
        B(红)  --->   B(红)  ------->   B(黑)
      A（红）       A(红)  D(黑)       A(红)  D（红）
      此时，插入的A只是颜色冲突，进行上述旋转变色后，解决了红红冲突，且可以维护性质5
 当然根据A B的位置 转换方式可能不同
 */

/* http://hi.baidu.com/renjiajiaowox/blog/item/070e33c0e5e9cd3ee5dd3b93.html */
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>
#include "rb_tree.h"

/* 对于
     ##a                 ###
     #b#    ------>      #b#
     c##                 c#a
 类型的转换,转换后返回b 的指针
 b如果有右子树，则旋转后成为 a的左子树(为什么要考虑b有没有子树呢， 因为以 b为轴旋转)
 在旋转的过程中除c外，a、b节点的高度发生变化
 */
rb_node_t *rb_single_right_rotate(rb_node_t* a){
  rb_node_t* b=a->left;
  a->left=b->right;
  if(a->left){
    a->left->parent=a;
  }

  b->right=a;
  b->parent=a->parent;
  a->parent=b;
  return b;
}

/* 对于
     a##                 ###
     #b#    ------>      #b#
     ##c                 a#c
     如果b有左子树，则旋转后成为a的右子树(为什么要考虑b有没有子树呢， 因为以 b为轴旋转)
 */
rb_node_t *rb_single_left_rotate(rb_node_t* a){
  rb_node_t* b=a->right;
  a->right=b->left;
  if(a->right){
    a->right->parent=a;
  }

  b->left=a;
  b->parent=a->parent;
  a->parent=b;
  return b;
}

void rb_init(rb_tree_t* tree,int (*item_cmp)(Item* item1,Item* item2)){
  tree->size=0;
  tree->root=NULL;
  tree->item_cmp=item_cmp;
}
int rb_make_node(Item item,rb_node_t **node){
  rb_node_t* n;
  n=(rb_node_t*)malloc(sizeof(rb_node_t));
  if(n){
    n->left=NULL;
    n->right=NULL;
    n->parent=NULL;
    n->color=RED;
    n->item=item;
    *node=n;
    return 0;
  }
  return -1;
}
/* return 1,or 0 */
int rb_is_black(rb_node_t *node){
  if(node==NULL){
    return 1;
  }
  if(node->color==BLACK){
    return 1;
  }else{
    return 0;
  }
}
/* 尝试恢复因插入而引起的失衡,
   因为加入的是红节点，则加入此节点的子树因多了一个红节点
 */
int rb_node_add_fixup(rb_node_t **node){
  if(!rb_is_black((*node)->parent)){ /* 如果父节点也是红，则需要调整 */

  }
}

int rb_node_add(rb_node_t **root,rb_node_t *new_node,int (*item_cmp)(Item* item1,Item* item2)){
  int cmp ,ret;
  rb_node_t *n=*root;
  if(*root){
    while(n){                   /* 找到new_node应该插入的位置， */
      cmp=item_cmp(&(n->item),&(new_node->item));
      new_node->parent=n;
      if(cmp==0){
        return -1;
      }else if(cmp>0){
        n=>n->left;
      }else if(cmp<0){
        n=>n->right;
      }
    }
    if(cmp>0){
      new_node->parent->left= new_node;
    }else if (cmp<0){
      new_node->parent->right= new_node;
    }
    rb_node_add_fixup(new_node);
  }else{                        /* 如果树中根为空 */
    *root=new_node;
  }
  return 0;
}
int rb_add(rb_tree_t* tree,Item item){
  int ret;
  rb_node_t *new_node;
  if(rb_make_node(item,&new_node)==-1){
    return -1;
  }
  ret=rb_node_add(&(tree->root),new_node,tree->item_cmp);
  if(ret!= -1){
    tree->size++;
  }
  return ret;
}

int main(int argc, char *argv[]){

  return 0;
}
