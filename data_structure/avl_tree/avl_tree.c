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
int avl_balance(avl_node_t* node){
  if (node){
    return  avl_node_height(node->left)- avl_node_height(node->right);
  }
  return 0;
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
  if(a->left){
    a->left->parent=a;
  }

  b->right=a;
  b->parent=a->parent;
  a->parent=b;

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
  if(a->right){
    a->right->parent=a;
  }

  b->left=a;
  b->parent=a->parent;
  a->parent=b;
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
  a->right->parent=a;
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
  a->left->parent=a;
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
    n->parent=NULL;
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

int avl_node_add(avl_node_t** parent,avl_node_t *new_node,int (*item_cmp)(Item* item1,Item* item2)){
  int cmp,ret;
  if(*parent){
    new_node->parent=*parent;
    cmp=item_cmp(&((*parent)->item),&(new_node->item));
    if(cmp>0){              /* 插入到左子树中 */
      ret=avl_node_add(&((*parent)->left),new_node,item_cmp);
      if(ret>-1){
        if(2==avl_node_height((*parent)->left)-avl_node_height((*parent)->right)){ /* 如果左右不平衡 */
          if(item_cmp(&(new_node->item),&((*parent)->left->item))>0){ /* >0  ,插入到左子树的右子树中 */
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
      ret=avl_node_add(&(*parent)->right,new_node,item_cmp);
      if(ret>-1){
        if(2==avl_node_height((*parent)->right)-avl_node_height((*parent)->left)){ /* 如果左右不平衡 */
          if(item_cmp(&(new_node->item),&((*parent)->right->item))>0){ /* >0  ,插入到右子树的右子树中 */
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
}
int avl_add(avl_tree_t* avl,Item item){
  int ret;
  avl_node_t *new_node;
  if(avl_make_node(item,&new_node)==-1){
    return -1;
  }
  ret=avl_node_add(&(avl->root),new_node,avl->item_cmp);
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

int avl_seek(int (*item_cmp)(Item* item1,Item* item2) ,avl_node_t *parent ,Item item,avl_node_t **no){
  avl_node_t *n;
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

int avl_find(avl_tree_t *root,Item item,Item *out){
  avl_node_t *n;
  int ret;
  ret=avl_seek(root->item_cmp,root->root,item,&n);
  if (0==ret){
    *out=n->item;
  }
  return ret;
}
/* 册除一个节点后，通过旋转来使树平衡，有可能影响的不只一个节点，需要依次向祖宗
   节点从低到高进行判断是否需要调整 */
void avl_balance_tree_after_del(avl_node_t * node, avl_tree_t *tree){
  avl_node_t *parent ,*tmp,*n;
  n=node;
  while(n){
    int bal=avl_balance(n);
    parent=n->parent;
    if(bal==2){
      tmp=avl_single_right_rotate(n);
    }else if(bal==-2){
      tmp=avl_single_left_rotate(n);
    }else{
      tmp=n;
    }
    if(parent){
      if(parent->left==n){
        parent->left=tmp;
      }else if(parent->right==n){
        parent->right=tmp;
      }
    }else{
      tree->root=tmp;
    }
    n=tmp->parent;
  }
}
/* 删除一节点后，其父节点，祖宗节点的高度可能会受影响 ，此函数用于调整其高度到真实高度 */
void avl_reset_height_after_del(avl_node_t * node){
  int old_height;
  avl_node_t *n=node;
  while(n){
    old_height=n->height;
    n->height=1+avl_max_height(avl_node_height(n->left),
                               avl_node_height(n->right));
    if(old_height==n->height){
      break;
    }
    n=n->parent;
  }
}

/* 删除算法分析,
   对于删除无子节点，只有一个子节点的情况，相对比较简单
   只需要将此节点删除，然后调整此节点的父节点及其祖先节点的高度，根据高度判断是否需要进行旋转
   而对于有两个子节点的情况，需要找到此节点A的左子树中最大的元素B ，然后让其替代此节点，
   可以理解为将AB两个元素位置互换，此时删除A,就相当于删除一个没有右子树的节点
   关于树高的调整与旋转使其平衡:
   1). 高度的调整需要沿父节点依次向上判断是否需要调整高度,调整完高度后，
   可以正确计算各子树的平衡因子，然后根据平衡因子，依次沿父节点到根，判断是否需要进行旋转
   此时的旋转都是单左旋、或单右旋
 */
int avl_del(avl_tree_t* tree,Item item){
  int found,lh,rh;
  avl_node_t *n,*n1,*tmp;
  found=avl_seek(tree->item_cmp,tree->root , item,&n);
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
    if(n->parent==NULL){
      tree->root=NULL;
    }else if (n->parent->left==n){
      n->parent->left=NULL;
      avl_reset_height_after_del(n->parent);
      avl_balance_tree_after_del(n->parent,tree);

    }else if (n->parent->right==n){
      n->parent->right=NULL;
    }
  }else if(n->left==NULL &&n->right!=NULL){ /* 无左子树 */
    if(n->parent==NULL){
      tree->root=n->right;
    }else if (n->parent->left==n){
      n->parent->left=n->right;
    }else if (n->parent->right==n){
      n->parent->right=n->right;
    }
    n->right->parent=n->parent;
    avl_reset_height_after_del(n->parent);
    avl_balance_tree_after_del(n->parent,tree);
  }else if(n->left!=NULL &&n->right==NULL){ /* 无右子树 */
    if(n->parent==NULL){
      tree->root=n->left;
    }else if (n->parent->left==n){
      n->parent->left=n->left;
    }else if (n->parent->right==n){
      n->parent->right=n->left;
    }
    n->left->parent=n->parent;
    avl_reset_height_after_del(n->parent);
    avl_balance_tree_after_del(n->parent,tree);
  }else if(n->left!=NULL &&n->right!=NULL){ /* 有左右子树 */
    tree_largest(n->left,&n1);
    /* if(n1->parent==n){               /\* n->left节点 就是左子树中最大的元素,即n->left无右子树 *\/ */
    /*   n1->parent=n; */
    /* } */
    /* 把n1,从原处移除 */
    tmp=n1->parent;
    if(n1->parent->left==n1){
      n1->parent->left=n1->left;
    }else if(n1->parent->right==n1){
      n1->parent->right=n1->left;
    }
    if(n1->left)
      n1->left->parent=n1->parent;
    /* n1->left=NULL; */
    /* n1->right=NULL; */
    /* 把n1 移动新位置 */
    if(n->parent==NULL){
      tree->root=n1;
    }else if(n->parent->left==n) {
      n->parent->left=n1;
    }else if(n->parent->right==n) {
      n->parent->left=n1;
    }
    n1->parent=n->parent;
    n1->left=n->left;
    n1->right=n->right;
    if(n1->right)
      n1->right->parent=n1;
    if(n1->left)
      n1->left->parent=n1;
    if(n!=tmp){
      avl_reset_height_after_del(tmp);
      avl_balance_tree_after_del(tmp,tree);
    }
  }
  avl_free_node(n);
  tree->size--;
  return 0;
}

/* private 从parent树中寻找最大的node,存到no
   只需一路寻找右节点，直到null即寻到最大值
 */
int tree_largest(avl_node_t *parent ,avl_node_t **no){
  avl_node_t*n;
  n=parent;
  if(parent==NULL){
    *no=NULL;
    return -1;
  }
  while(n->right!=NULL){
    n=n->right;
  }
  *no=n;
  return 0;
}
void avl_destory_subtree(avl_node_t *node){
  if(node){
    avl_destory_subtree(node->left);
    avl_destory_subtree(node->right);
    free(node);
    node=NULL;
  }
}

void avl_destory(avl_tree_t *tree){
  avl_destory_subtree(tree->root);
}

void previous_visit_node(avl_node_t* n,void (*v)(Item i)){
  if(n){
    v(n->item);
    /* printf ("%d\n",n->item); */
  }
  if(n->left){
    previous_visit_node(n->left,v);
  }
  if(n->right){
    previous_visit_node(n->right,v);
  }
}
void previous_visit(avl_tree_t *t,void (*v)(Item i)){
  printf ("previous visit tree\n");
  previous_visit_node(t->root,v);
}

void mid_visit_node(avl_node_t* n,void (*v)(Item i)){
  if(n->left){
    mid_visit_node(n->left,v);
  }
  if(n){
    v(n->item);
    /* printf ("%d\n",n->item); */
  }
  if(n->right){
    mid_visit_node(n->right,v);
  }
}
void mid_visit(avl_tree_t *t,void (*v)(Item i)){
  printf ("middle visit tree\n");
  mid_visit_node(t->root,v);
}

void after_visit_node(avl_node_t* n,void (*v)(Item i)){
  if(n->left){
    after_visit_node(n->left,v);
  }
  if(n->right){
    after_visit_node(n->right,v);
  }
  if(n){
    v(n->item);
    /* printf ("%d\n",n->item); */
  }

}
void after_visit(avl_tree_t *t,void (*v)(Item i)){
  printf ("after visit tree\n");
  after_visit_node(t->root,v);
}


/* tests=============================================== */

int int_cmp(Item *i1, Item *i2){
  int *i1_int = (int*) i1;
  int *i2_int = (int*) i2;
  return (*i1_int - *i2_int);
}



/*          20                                           18                                        30
      10            30            del 20          10                30                      18              35
    3   15     23        35      ---->         3     15        23        35   ----->   10       23      33      38
   2  14 18  22  26   33   38                 2    14  16    22  26    33  38        3   15   22  26   32     37  40
        16      25   32  37  40                                 25    32  37 40     2   14 16    25                 41
                               41                                              41
*/

void test_avl_del8(){           /* test avl_del balance, 删除有左右子树的节点 */
  avl_tree_t tree;
  avl_init(&tree,int_cmp);
  avl_add(&tree,20);
  avl_add(&tree,10);
  avl_add(&tree,30);
  avl_add(&tree,3);
  avl_add(&tree,15);
  avl_add(&tree,23);
  avl_add(&tree,35);
  avl_add(&tree,2);
  avl_add(&tree,14);
  avl_add(&tree,18);
  avl_add(&tree,22);
  avl_add(&tree,26);
  avl_add(&tree,33);
  avl_add(&tree,38);
  avl_add(&tree,16);
  avl_add(&tree,25);
  avl_add(&tree,32);
  avl_add(&tree,37);
  avl_add(&tree,40);
  avl_add(&tree,41);

  assert(0==avl_del(&tree,20));
  assert(19==avl_size(&tree));
  /* printf ("%d\n",tree.root->item); */
  assert(tree.root->item==30);
  assert(tree.root->left->item==18);
  assert(tree.root->right->item==35);
  assert(tree.root->left->left->item==10);
  assert(tree.root->left->right->item==23);
  assert(tree.root->left->left->left->item==3);
  assert(tree.root->left->left->right->item==15);
  assert(tree.root->left->right->left->item==22);
  assert(tree.root->left->right->right->item==26);
  assert(tree.root->left->left->left->left->item==2);
  assert(tree.root->left->left->right->left->item==14);
  assert(tree.root->left->left->right->right->item==16);
  assert(tree.root->left->right->right->left->item==25);
  assert(tree.root->right->left->item==33);
  assert(tree.root->right->right->item==38);
  assert(tree.root->right->left->left->item==32);

  assert(tree.root->right->right->left->item==37);
  assert(tree.root->right->right->right->item==40);
  assert(tree.root->right->right->right->right->item==41);

  /* assert(tree.root->parent==NULL); */
  /* assert(tree.root->left->parent==tree.root); */
  /* assert(tree.root->right->parent==tree.root); */

  /* assert(tree.root->left->left->parent==tree.root->left); */
  /* assert(tree.root->left->right->parent==tree.root->left); */
  /* assert(tree.root->left->left->left->parent==tree.root->left->left); */
  /* assert(tree.root->left->left->right->parent==tree.root->left->left); */
  /* assert(tree.root->left->right->right->parent==tree.root->left->right); */

  /* assert(tree.root->right->left->parent==tree.root->right); */
  /* assert(tree.root->right->right->parent==tree.root->right); */
  /* assert(tree.root->right->right->right->parent==tree.root->right->right); */


}


/*
       10
          11
 */

void test_avl_del9(){           /* test avl_del balance, 删除无左子树的节点 ,且为根*/
  avl_tree_t tree;
  avl_init(&tree,int_cmp);
  avl_add(&tree,10);
  avl_add(&tree,11);
  assert(0==avl_del(&tree,10));
  assert(11==tree.root->item);
  assert(1==tree.size);
}



/*       20                                20                              30
   10           30     del15          10         30                   20        35
 3   15     25     35 ------->       3  16   25      35    ---->   10   25    33  36
       16     26  33 36                        26   33 36        3  16    26         40
                       40                                 40
 */
void test_avl_del7(){           /* test avl_del balance, 删除无左子树的节点 */
  avl_tree_t tree;
  avl_init(&tree,int_cmp);
  avl_add(&tree,20);
  avl_add(&tree,10);
  avl_add(&tree,30);
  avl_add(&tree,3);
  avl_add(&tree,15);
  avl_add(&tree,25);
  avl_add(&tree,35);
  avl_add(&tree,16);
  avl_add(&tree,26);
  avl_add(&tree,33);
  avl_add(&tree,36);
  avl_add(&tree,40);

  assert(0==avl_del(&tree,15));
  assert(11==avl_size(&tree));


  assert(tree.root->item==30);
  assert(tree.root->left->item==20);
  assert(tree.root->right->item==35);
  assert(tree.root->left->left->item==10);
  assert(tree.root->left->right->item==25);
  assert(tree.root->left->left->left->item==3);
  assert(tree.root->left->left->right->item==16);
  assert(tree.root->left->right->right->item==26);
  assert(tree.root->right->right->right->item==40);
  assert(tree.root->right->right->item==36);
  assert(tree.root->right->left->item==33);

  assert(tree.root->parent==NULL);
  assert(tree.root->left->parent==tree.root);
  assert(tree.root->right->parent==tree.root);

  assert(tree.root->left->left->parent==tree.root->left);
  assert(tree.root->left->right->parent==tree.root->left);
  assert(tree.root->left->left->left->parent==tree.root->left->left);
  assert(tree.root->left->left->right->parent==tree.root->left->left);
  assert(tree.root->left->right->right->parent==tree.root->left->right);

  assert(tree.root->right->left->parent==tree.root->right);
  assert(tree.root->right->right->parent==tree.root->right);
  assert(tree.root->right->right->right->parent==tree.root->right->right);


}


/*       20                                20                              30
   10           30     del 3          15         30                   20        35
 3   15     25     35 ------->       10 16   25      35    ---->   15   25    33  36
       16     26  33 36                        26   33 36        10 16    26         40
                       40                                 40
 */
void test_avl_del6(){           /* test avl_del balance, 删除无子女的节点 */
  avl_tree_t tree;
  avl_init(&tree,int_cmp);
  avl_add(&tree,20);
  avl_add(&tree,10);
  avl_add(&tree,30);
  avl_add(&tree,3);
  avl_add(&tree,15);
  avl_add(&tree,25);
  avl_add(&tree,35);
  avl_add(&tree,16);
  avl_add(&tree,26);
  avl_add(&tree,33);
  avl_add(&tree,36);
  avl_add(&tree,40);

  assert(0==avl_del(&tree,3));
  assert(11==avl_size(&tree));


  assert(tree.root->item==30);
  assert(tree.root->left->item==20);
  assert(tree.root->right->item==35);
  assert(tree.root->left->left->item==15);
  assert(tree.root->left->right->item==25);
  assert(tree.root->left->left->left->item==10);
  assert(tree.root->left->left->right->item==16);
  assert(tree.root->left->right->right->item==26);
  assert(tree.root->right->right->right->item==40);
  assert(tree.root->right->right->item==36);
  assert(tree.root->right->left->item==33);

  assert(tree.root->parent==NULL);
  assert(tree.root->left->parent==tree.root);
  assert(tree.root->right->parent==tree.root);

  assert(tree.root->left->left->parent==tree.root->left);
  assert(tree.root->left->right->parent==tree.root->left);
  assert(tree.root->left->left->left->parent==tree.root->left->left);
  assert(tree.root->left->left->right->parent==tree.root->left->left);
  assert(tree.root->left->right->right->parent==tree.root->left->right);

  assert(tree.root->right->left->parent==tree.root->right);
  assert(tree.root->right->right->parent==tree.root->right);
  assert(tree.root->right->right->right->parent==tree.root->right->right);


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
  assert(tree.root->parent==NULL);
  assert(tree.root->left->parent==tree.root);
  assert(tree.root->right->parent==tree.root);
  assert(tree.root->right->left->parent==tree.root->right);

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

  assert(tree.root->parent==NULL);
  assert(tree.root->left->parent==tree.root);
  assert(tree.root->right->parent==tree.root);
  assert(tree.root->right->left->parent==tree.root->right);
  assert(tree.root->left->left->parent==tree.root->left);
  assert(tree.root->left->right->parent==tree.root->left);
  assert(tree.root->left->left->left->parent==tree.root->left->left);

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
  assert(tree.root->parent==NULL);
  assert(tree.root->right->parent==tree.root);
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
  a.parent=NULL;

  b.height=1;
  b.left=&c;
  b.right=NULL;
  b.parent=&a;

  c.height=0;
  c.right=NULL;
  c.left=NULL;
  c.parent=&b;

  result= avl_single_right_rotate(&a);

  assert(4==result->item);
  assert(3==result->left->item);
  assert(5==result->right->item);
  assert(0==a.height);
  assert(1==b.height);
  assert(0==c.height);
  assert(a.parent==&b);
  assert(b.parent==NULL);
  assert(c.parent==&b);
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
  a.parent=NULL;

  b.height=1;
  b.right=&c;
  b.left=NULL;
  b.parent=&a;

  c.height=0;
  c.right=NULL;
  c.left=NULL;
  c.parent=&b;
  result= avl_single_left_rotate(&a);
  printf ("test_avl_single_left_rotate:");
  assert(2==result->item);
  assert(1==result->left->item);
  assert(3==result->right->item);
  assert(1==result->height);
  assert(0==result->left->height);
  assert(0==result->right->height);
  assert(a.parent==&b);
  assert(b.parent==NULL);
  assert(c.parent==&b);

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
  a.parent=NULL;

  b.height=2;
  b.left=&c;
  b.right=NULL;
  b.parent=&a;


  cr.item=9;
  cr.height=0;
  cr.left=NULL;
  cr.right=NULL;
  cr.parent=&c;

  cl.item=6;
  cl.height=0;
  cl.left=NULL;
  cl.right=NULL;
  cl.parent=&c;

  c.height=1;
  c.right=&cr;
  c.left=&cl;
  c.parent=&b;

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

  assert(c.parent==NULL);
  assert(a.parent==&c);
  assert(b.parent==&c);
  assert(cr.parent==&b);
  assert(cl.parent==&a);

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
  a.parent=NULL;


  b.right=&c;
  b.left=NULL;
  b.height=2;
  b.parent=&a;

  cr.item=9;
  cr.left=NULL;
  cr.right=NULL;
  cr.height=0;
  cr.parent=&c;

  cl.item=6;
  cl.left=NULL;
  cl.right=NULL;
  cl.height=0;
  cl.parent=&c;

  c.height=1;
  c.right=&cr;
  c.left=&cl;
  c.parent=&b;

  result= avl_left_right_rotate(&a);
  assert(0==cr.height);
  assert(0==cl.height);
  assert(1==a.height);
  assert(1==b.height);
  assert(2==c.height);

  assert(c.parent==NULL);
  assert(a.parent==&c);
  assert(b.parent==&c);
  assert(cr.parent==&a);
  assert(cl.parent==&b);

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

  assert(tree.root->parent==NULL);
  assert(tree.root->left->parent==tree.root);
  assert(tree.root->right->parent==tree.root);
  assert(tree.root->right->right->parent==tree.root->right);
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
  assert(tree.root->parent==NULL);
  assert(tree.root->left->parent==tree.root);
  assert(tree.root->right->parent==tree.root);
  assert(tree.root->right->left->parent==tree.root->right);
  assert(tree.root->right->right->parent==tree.root->right);

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
  assert(tree.root->parent==NULL);
  assert(tree.root->left->parent==tree.root);
  assert(tree.root->right->parent==tree.root);
  assert(tree.root->left->left->parent==tree.root->left);
  assert(tree.root->left->right->parent==tree.root->left);
  assert(tree.root->right->right->parent==tree.root->right);

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
void test(){
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
  test_avl_del6();
  test_avl_del7();
  test_avl_del8();
  test_avl_del9();
}

int main(int argc, char *argv[]){
  test();
  return 0;
}
