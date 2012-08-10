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
rb_node_t *rb_right_left_rotate(rb_node_t* a){
  a->right=rb_single_right_rotate(a->right);
  a->right->parent=a;
  return rb_single_left_rotate(a);
}

/* rb_node_t *rb_right_left_rotate(rb_node_t* a){ */
/*   rb_node_t* b=a->right; */
/*   rb_node_t* c=b->left; */

/*   b->left=c->right; */
/*   c->right= b; */
/*   b->height=1+rb_max_height(rb_node_height(b->left),rb_node_height(b->right)); */
/*   c->height=1+rb_max_height(rb_node_height(c->left),rb_node_height(c->right)); */
/*   /\* 第二轮 *\/ */
/*   a->right=c->left; */
/*   c->left=a; */
/*   a->height =1+rb_max_height(rb_node_height(a->left),rb_node_height(a->right)); */
/*   c->height =1+rb_max_height(rb_node_height(c->left),rb_node_height(c->right)); */
/*   return c; */
/* } */
/* 先左旋，后右旋
     ##a        ##a         ###
     #b#------> #c#-------> #c#
     ##c        b##         b#a
     第一轮旋转(左旋)，如果c有左子树(比c小，比b大)，则旋转后，成为b的右子树(首轮旋转与a无关,以b为轴，使c转到轴心处)
     第二转旋转(右旋),c有右子树(比c大，比a小)，则旋转后，成为a的左子树(以c为轴)
 */

rb_node_t *rb_left_right_rotate(rb_node_t* a){
  a->left=rb_single_left_rotate(a->left);
  a->left->parent=a;
  return rb_single_right_rotate(a);
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
 */
/*     D */
/*   B  C */
/* A */
 /*  插入的分析，对于新插入的元素A，默认它是红色的 */
 /*  1). 如果A的父节点是黑元素，则一切正常 ，不需要变换， */
 /*  2). 如果A的父节点B是红元素(可推出祖父D为黑)，则需要将父节点B变成黑元素，以维护性质4 */
 /*  但是B变成黑元素后，此子树上因多了此黑元素，导致性质5不成立.() */
 /*  处理方法需要节点B的兄弟节点C(即A的uncle)的颜色而定 */
 /*  2.1). 如果C为红)，则将C变成黑,然后把祖父D变成红,此时D变成红色，做法与初插入A时的处理方法一样 */
 /*  ，向上依次检测是否有冲突 */
 /*  2.2). 如果C为黑色，此种情况相对简单，只需要对ABD进行旋转，使A、D成为B的子节点 */
 /*      此时 */
 /*          D(黑) */
 /*        B(红)  --->   B(红)  ------->   B(黑) */
 /*      A（红）       A(红)  D(黑)       A(红)  D（红） */
 /*      此时，插入的A只是颜色冲突，进行上述旋转变色后，解决了红红冲突，且可以维护性质5 */
 /* 当然根据A B的位置 转换方式可能不同,总之旋转之后，是上为黑下二为红 */

int rb_node_add_fixup(rb_node_t *node,rb_node_t **root){
  /* 不必考虑根为空的情况， rb_node_add里已做特殊处理,
     也就是说新插入的元素一定有父节点，
  */
  rb_node_t *n, *parent ,*grantp,*grantgrantp,*uncle,*tmp_node;
  n=node;
  while(n){
    parent=n->parent;
    if(!parent){
      n->color=BLACK;
      return 0;
    }
    grantp=parent->parent;
    if(!rb_is_black(parent)){ /* 如果父节点也是红，则需要调整 */
      grantgrantp=grantp->parent; /* 如果父节点为红，则grantp一定不为null */
      parent->color =BLACK;
      if(grantp->left==parent){
        uncle=grantp->right;
      }else{
        uncle=grantp->left;
      }
      if(rb_is_black(uncle)){   /* 根据uncle颜色而定，若为黑 ,根据 ABD的位置不同正好对应4种旋转变换，此种情况旋转后变色即可，不需要向上递归*/
        if(grantp->left==parent){
          if(parent->left==n){
            /***********/
            /*       D */
            /*    B    */
            /* A       */
            /***********/
            parent->color=BLACK;
            grantp->color=RED;
            if(grantgrantp){
              if(grantgrantp->left==grantp){
                grantgrantp->left=rb_single_right_rotate(grantp);
              }else{
                grantgrantp->right=rb_single_right_rotate(grantp);
              }
            }else{
              *root=rb_single_right_rotate(grantp);
            }
          }else{                  /* (parent->right==n) */
            /***********/
            /*       D */
            /*    B    */
            /*       A */
            /***********/
            parent->color=RED;
            grantp->color=RED;
            n->color=BLACK;
            if(grantgrantp){
              if(grantgrantp->left==grantp){
                grantgrantp->left=rb_left_right_rotate(grantp);
              }else{
                grantgrantp->right=rb_left_right_rotate(grantp);
              }
            }else{
              *root=rb_left_right_rotate(grantp);
            }
          }
        }else{                    /* (grantp->right==parent) */
          if(parent->left==n){
            /***********/
            /*  D      */
            /*    B    */
            /* A       */
            /***********/
            parent->color=RED;
            grantp->color=RED;
            n->color=BLACK;
            if(grantgrantp){
              if(grantgrantp->left==grantp){
                grantgrantp->left=rb_right_left_rotate(grantp);
              }else{
                grantgrantp->right=rb_right_left_rotate(grantp);
              }
            }else{
              *root=rb_right_left_rotate(grantp);
            }
          }else{                  /* (parent->right==n) */
            /***********/
            /* D       */
            /*    B    */
            /*       A */
            /***********/
            parent->color=BLACK;
            grantp->color=RED;
            n->color=RED;
            if(grantgrantp){
              if(grantgrantp->left==grantp){
                grantgrantp->left=rb_single_left_rotate(grantp);
              }else{
                grantgrantp->right=rb_single_left_rotate(grantp);
              }
            }else{
              *root=rb_left_right_rotate(grantp);
            }
          }
        }
        return 0;
      }else{                      /* uncle is red */
        /*  2.1). 如果C为红)，则将C变成黑,然后把祖父D变成红,此时D变成红色，做法与初插入A时的处理方法一样 */
        /*  ，向上依次检测是否有冲突 */
        uncle->color=BLACK;
        grantp->color=RED;
        n=n->parent->parent;
        /* rb_node_add_fixup(n->parent->parent,root); */
      }
    }else{                      /* 父节点是黑，不需要调整 */
      return 0;
    }
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
        n=n->left;
      }else if(cmp<0){
        n=n->right;
      }
    }
    if(cmp>0){
      new_node->parent->left= new_node;
    }else if (cmp<0){
      new_node->parent->right= new_node;
    }
    rb_node_add_fixup(new_node,root);
  }else{                        /* 如果树中根为空 */
    *root=new_node;
    (*root)->color=BLACK;         /* 默认根为黑 */
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
/* 关于删除的一些推论,
   根据二叉树的理论知，删除一个节点，其实基本等于，把这个节点与它左子树中的最大节点互换位置，然后把它从新的位置删除
   而这个位置，最多只有一个左节点
   推论1：如果这个节点A有一个左节点B,则节点A一定是黑色，（如果它是红色，则左孩子节点必为黑，而右孩子节点为空，两棵子树的黑节点不相等）,且其左孩子为红色
   推论2：这个节点可以是一个没有孩子的节点，颜色不确定
   推论3:由推论一反推出，如果被删除的节点是红色的，则它肯定无孩子,直接删除即可

需要考虑的情况，
  1. A无子节点
  2. A只有一个子节点(A必为黑色,且子节点必为红色叶子节点)
  3. A有两个子节点，此种处理方式按上面说的来处理

 */
int rb_del(rb_tree_t * tree,Item item){
  rb_node_t* n,*tmp;
  if(-1==rb_seek(tree->item_cmp,tree->root,item,&n))    return -1;
  /* n为 待删除的节点 */
  if(n->left==NULL&&n->right==NULL){ /* 无子节点 */
    if(n->parent){                 /* n有父，即n不是根节点 */
      if(rb_is_black(n)){          /* n为黑 */
        if(n->parent->left==n){
          if(rb_is_black(n->parent->right)){ /* n的兄弟节点为黑 */

          }else{                /* n的兄弟节点为红,则推出n的父必为黑 */
            /**********************************************************************************/
            /*      p(B)           del n          s(B)                                        */
            /* n(B)     s(R)       ---->   p(R)        sr(B)                                  */
            /*       sl(B)  sr(B)            sl(B)                                            */
            /*       删掉n之后,p的右子树比左子树的黑节点要多， 所以需要进行调色旋转以达到平衡              */
            /*       处理办法是：p由黑变红，s由红变黑，然后进行一次左旋                                */
            /**********************************************************************************/
            n->parent->color=RED;
            n->parent->right->color=BLACK;
            /* 进行左旋start............... */
            if(n->parent->parent){
              if(n->parent->parent->left==n->parent){
                n->parent->parent->left=rb_single_left_rotate(n->parent->right);
              }else{
                n->parent->parent->right=rb_single_left_rotate(n->parent->right);
              }
            }else{
              tree->root=rb_single_left_rotate(n->parent->right);
            }
            /* 进行左旋end............... */
          }
        }else{                               /* n->parent->right==n */
          if(rb_is_black(n->parent->right)){ /* n的兄弟节点为黑 */

          }else{                /* n的兄弟节点为红,则推出n的父必为黑 */
            /*********************************************************************************/
            /*        p(B)           del n            s(B)                                   */
            /*   s(R)       n(B)     ---->       sl(B)       p(R)                            */
            /*sl(B)  sr(B)                               sr(B)                               */
            /*       删掉n之后,p的左子树比右子树的黑节点要多， 所以需要进行调色旋转以达到平衡              */
            /*       处理办法是：p由黑变红，s由红变黑，然后进行一次右旋                                */
            /**********************************************************************************/
            n->parent->color=RED;
            n->parent->right->color=BLACK;
            /* 进行左旋start............... */
            if(n->parent->parent){
              if(n->parent->parent->left==n->parent){
                n->parent->parent->left=rb_single_right_rotate(n->parent->left);
              }else{
                n->parent->parent->right=rb_single_right_rotate(n->parent->left);
              }
            }else{
              tree->root=rb_single_right_rotate(n->parent->left);
            }
            /* 进行左旋end............... */
          }
        }

      }else{                    /* n为红色 ,直接将n删除即可*/
        if(n->parent->left==n){
          n->parent->left=NULL;
        }else{
          n->parent->right=NULL;
        }
      }
    }else{                      /* n为根节点 */
      tree->root=NULL;
    }
  }
  tree->size--;
  return 0;
}
int rb_seek(int (*item_cmp)(Item* item1,Item* item2) ,rb_node_t *parent ,Item item,rb_node_t **no){
  rb_node_t *n;
  int cmp;
  if(parent==NULL) return -1;
  n=parent;
  while(n!=NULL){
    cmp=item_cmp(&(n->item),&item);
    if(cmp==0){                    /* found */
      *no=n;
      return 0;
    }else if (cmp<0){
      n=n->right;
    }else{
      n=n->left;
    }
  }
  return -1;
}

/* test */
int int_cmp(Item *i1, Item *i2){
  int *i1_int = (int*) i1;
  int *i2_int = (int*) i2;
  return (*i1_int - *i2_int);
}
void test_del1(){               /* 删除不存在的元素 */
  rb_tree_t tree;
  rb_init(&tree,int_cmp);
  assert(-1==rb_del(&tree,1));
}
void test_del2(){               /* 删除不存在的元素 */
  rb_tree_t tree;
  rb_init(&tree,int_cmp);
  rb_add(&tree,2);
  rb_add(&tree,3);
  assert(-1==rb_del(&tree,1));
}
/**********************************************************************************/
/*      10(B)           del 5              20(B)                     */
/* 5(B)     20(R)       ---->          10(R)      30(B)                   */
/*       15(B)  30(B)                    15(B)                       */
/*            16(R)        )               16(R)                            */
/*       删掉n之后,p的右子树比左子树的黑节点要多， 所以需要进行调色旋转以达到平衡              */
/*       处理办法是：p由黑变红，s由红变黑，然后进行一次左旋                                */
/**********************************************************************************/
/* 删除n,5,且兄弟s 20为红的情况 */
void test_del3(){               /* 删除不存在的元素 */
  rb_tree_t tree;
  rb_init(&tree,int_cmp);
  rb_add(&tree,10);
  rb_add(&tree,5);
  rb_add(&tree,20);
  rb_add(&tree,15);
  rb_add(&tree,30);
  rb_add(&tree,16);
  assert(tree.root->item==10);
  assert(tree.root->left->item==5);
  assert(tree.root->right->item==20);
  assert(tree.root->right->left->item==15);
  assert(tree.root->right->right->item==30);
  assert(tree.root->right->left->right->item==16);
  assert(tree.root->color==BLACK);
  assert(tree.root->left->color==BLACK);
  assert(tree.root->right->color==RED);
  assert(tree.root->right->left->color==BLACK);
  assert(tree.root->right->right->color==BLACK);
  assert(tree.root->right->left->right->color==RED);
  /* 以上确保删除5之前的结构如注释中图所示 */
  assert(0==rb_del(&tree,5));

  assert(tree.root->item==20);
  assert(tree.root->color==BLACK);
  assert(tree.root->left->item==10);
  assert(tree.root->left->color==RED);
  assert(tree.root->right->item==30);
  assert(tree.root->right->color==BLACK);
  assert(tree.root->left->right->item==15);
  assert(tree.root->left->right->color==BLACK);
  assert(tree.root->left->right->right->item==16);
  assert(tree.root->left->right->right->color==RED);

}


/*********************************/
/*      20b                      */
/*    10r      --->      10b       */
/* 1r               1r       20r */
/*********************************/
void test_add(){
  rb_tree_t tree;
  rb_init(&tree,int_cmp);
  rb_add(&tree,20);
  rb_add(&tree,10);
  rb_add(&tree,1);

  assert(3==tree.size);

  assert(10==tree.root->item);
  assert(1==tree.root->left->item);
  assert(20==tree.root->right->item);

  assert(rb_is_black(tree.root));
  assert(!rb_is_black(tree.root->left));
  assert(!rb_is_black(tree.root->right));
}
  /**********************************************/
  /*   10b             10b              10b     */
  /* 1r    20r --->1r       20r-->   1b     20b */
  /*                  5r               5r       */
  /**********************************************/
void test_add2(){
  rb_tree_t tree;
  rb_init(&tree,int_cmp);
  rb_add(&tree,20);
  rb_add(&tree,10);
  rb_add(&tree,1);
  rb_add(&tree,5);

  assert(4==tree.size);

  assert(10==tree.root->item);
  assert(1==tree.root->left->item);
  assert(5==tree.root->left->right->item);
  assert(20==tree.root->right->item);
  assert(rb_is_black(tree.root));
  assert(rb_is_black(tree.root->left));
  assert(rb_is_black(tree.root->right));
  assert(!rb_is_black(tree.root->left->right));
}
  /**********************************************/
  /*   10b             10b                      */
  /*1b     20b-->   5b     20b                  */
  /*  5r          1r 8r                         */
  /*    8r                                      */
  /**********************************************/

void test_add3(){
  rb_tree_t tree;
  rb_init(&tree,int_cmp);
  rb_add(&tree,20);
  rb_add(&tree,10);
  rb_add(&tree,1);
  rb_add(&tree,5);
  rb_add(&tree,8);

  assert(5==tree.size);

  assert(10==tree.root->item);
  assert(5==tree.root->left->item);
  assert(20==tree.root->right->item);
  assert(1==tree.root->left->left->item);
  assert(8==tree.root->left->right->item);
  assert(rb_is_black(tree.root));
  assert(rb_is_black(tree.root->left));
  assert(rb_is_black(tree.root->right));
  assert(!rb_is_black(tree.root->left->right));
  assert(!rb_is_black(tree.root->left->left));
  assert(tree.root->left->left->parent ==tree.root->left);
  assert(tree.root->left->right->parent ==tree.root->left);
  assert(tree.root->left->parent ==tree.root);
  assert(tree.root->right->parent ==tree.root);
  assert(tree.root->parent ==NULL);
}
  /**********************************************/
  /*      10b             10b                   */
  /*   5b     20b-->  5r       20b              */
  /* 1r  8r        1b   8b                      */
  /*    6r             6r                       */
  /**********************************************/
void test_add4(){
  rb_tree_t tree;
  rb_init(&tree,int_cmp);
  rb_add(&tree,20);
  rb_add(&tree,10);
  rb_add(&tree,1);
  rb_add(&tree,5);
  rb_add(&tree,8);
  rb_add(&tree,6);

  assert(6==tree.size);

  assert(10==tree.root->item);
  assert(5==tree.root->left->item);
  assert(20==tree.root->right->item);
  assert(1==tree.root->left->left->item);
  assert(8==tree.root->left->right->item);
  assert(6==tree.root->left->right->left->item);
  assert(rb_is_black(tree.root));
  assert(!rb_is_black(tree.root->left));
  assert(rb_is_black(tree.root->right));
  assert(rb_is_black(tree.root->left->right));
  assert(rb_is_black(tree.root->left->left));
  assert(!rb_is_black(tree.root->left->right->left));
  assert(tree.root->left->left->parent ==tree.root->left);
  assert(tree.root->left->right->parent ==tree.root->left);
  assert(tree.root->left->parent ==tree.root);
  assert(tree.root->right->parent ==tree.root);
  assert(tree.root->parent ==NULL);
}
  /**********************************************/
  /*        10b                  10b            */
  /*   5r        20b       5r           20b     */
  /*1b    8b      ----> 1b     7b               */
  /*   6r                    6r    8r           */
  /*     7r                                     */
  /**********************************************/
void test_add5(){
  rb_tree_t tree;
  rb_init(&tree,int_cmp);
  rb_add(&tree,20);
  rb_add(&tree,10);
  rb_add(&tree,1);
  rb_add(&tree,5);
  rb_add(&tree,8);
  rb_add(&tree,6);
  rb_add(&tree,7);

  assert(7==tree.size);

  assert(10==tree.root->item);
  assert(5==tree.root->left->item);
  assert(20==tree.root->right->item);
  assert(1==tree.root->left->left->item);
  assert(7==tree.root->left->right->item);
  assert(6==tree.root->left->right->left->item);
  assert(8==tree.root->left->right->right->item);
  assert(rb_is_black(tree.root));
  assert(!rb_is_black(tree.root->left));
  assert(rb_is_black(tree.root->right));
  assert(rb_is_black(tree.root->left->right));
  assert(rb_is_black(tree.root->left->left));
  assert(!rb_is_black(tree.root->left->right->left));
  assert(!rb_is_black(tree.root->left->right->right));
}

void test_add6(){
  rb_tree_t tree;
  rb_init(&tree,int_cmp);
  rb_add(&tree,20);
  rb_add(&tree,10);
  rb_add(&tree,1);
  rb_add(&tree,5);
  rb_add(&tree,8);
  rb_add(&tree,6);
  rb_add(&tree,7);
  rb_add(&tree,7);              /* 两次添加7 */

  assert(7==tree.size);

  assert(10==tree.root->item);
  assert(5==tree.root->left->item);
  assert(20==tree.root->right->item);
  assert(1==tree.root->left->left->item);
  assert(7==tree.root->left->right->item);
  assert(6==tree.root->left->right->left->item);
  assert(8==tree.root->left->right->right->item);
  assert(rb_is_black(tree.root));
  assert(!rb_is_black(tree.root->left));
  assert(rb_is_black(tree.root->right));
  assert(rb_is_black(tree.root->left->right));
  assert(rb_is_black(tree.root->left->left));
  assert(!rb_is_black(tree.root->left->right->left));
  assert(!rb_is_black(tree.root->left->right->right));
}



int main(int argc, char *argv[]){
  test_add();
  test_add2();
  test_add3();
  test_add4();
  test_add5();
  test_add6();
  test_del1();
  test_del2();
  test_del3();
  return 0;
}
