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

    /* 待删除的节点按照儿子的个数可以分为三种： */
    /* 1）没有儿子，即为叶节点。直接把父节点的对应儿子指针设为NULL，删除儿子节
       点就OK了。 */
    /* 2）只有一个儿子。那么把父节点的相应儿子指针指向儿子的独生子，删除儿子节
       点也OK了。 */
    /* 3）有两个儿子。这是最麻烦的情况，因为你删除节点之后，还要保证满足搜索二
       叉树的结构。其实也比较容易，我们可以选择左儿子中的最大元素或者右儿子中的
       最小元素放到待删除节点的位置，就可以保证结构的不变。当然，你要记得调整子
       树，毕竟又出现了节点删除。习惯上大家选择左儿子中的最大元素，其实选择右儿
       子的最小元素也一样，没有任何差别，只是人们习惯从左向右。这里咱们也选择左
       儿子的最大元素，将它放到待删节点的位置。左儿子的最大元素其实很好找，只要
       顺着左儿子不断的去搜索右子树就可以了，直到找到一个没有右子树的节点。那就
       是最大的了（很好证明）。 */
    /* 初略的一看，你可能觉得要递归了，删除了左子树的最大元素不是还要调整吗？其
       实你可以看到，这个元素是没有右子树的（左子树有没有无所谓），我们只要将最
       大元素的父节点指向最大元素的左儿子就可以了。最后，清理掉待删除的儿子节点。
        */

    /*  还有其他情况么？没有了。但要注意一点问题，那就是待删除的节点可能没有父
        亲，也就是可能本身就是根节点。那就要改变根节点指针了。这样在编程时，是
        首先按照有无父节点分成两种情况呢？还是按照儿子个数分为三种情况然后在处
        理没有父亲的特殊情况呢？我个人选择第二种，代码量会小一点（两个儿子的情
        况处理代码较多） */

int tree_del(tree_t *root ,Item item){
  node_t *to_be_del,*parent,*n,*p;
  int val;
  val=tree_seek(root->root,item,&to_be_del,&parent);
  if (val==-1) return -1;       /* 如果没找到要删除的 */
  /* int cmp=item_cmp(&(root->root->item),&item); */
  /* 根据 to_be_del的子节点个数分别进行处理 */
  if(to_be_del->left==NULL && to_be_del->right ==NULL){ /* 无左右子树， */
    if(parent==NULL){           /* 如果 to_be_del是根 */
      root->root=NULL;
    }else{
      /* 无子树，直接将此节点删了，然后其其父节点指向null */
      /* 需要得到其父节点，以便致空 */
      if (parent->right==to_be_del){ /* to_be_del是parent的右子树 */
        parent->right=NULL;
      }else{                      /* parent 是to_be_del的父 节点,故不必考虑两者相等状*/
        parent->left=NULL;
      }
    }
  }else if(to_be_del->left==NULL && to_be_del->right !=NULL){ /* 无左子树， */
    if(parent==NULL){/* 如果 to_be_del是根 */
      root->root=to_be_del->right;
    }else{
      if(parent->right==to_be_del){ /* to_be_del是parent的右子树 */
        parent->right=to_be_del->right;
      }else{                      /* parent 是to_be_del的父 节点,故不必考虑两者相等状*/
        parent->left=to_be_del->right;
      }
    }
  }else if(to_be_del->left!=NULL && to_be_del->right ==NULL){ /* 无右子树， */
    if(parent==NULL){/* 如果 to_be_del是根 */
      root->root=to_be_del->left;
    }else{
      if(parent->right==to_be_del){ /* to_be_del是parent的右子树 */
        parent->right=to_be_del->left;
      }else{                      /* parent 是to_be_del的父 节点,故不必考虑两者相等状*/
        parent->left=to_be_del->left;
      }
    }
  }else if(to_be_del->left!=NULL && to_be_del->right !=NULL){ /* 有左右子树， */
    tree_largest(to_be_del->left,&n,&p);                      /* 找到 to_be_del左子树中的最大值，存到n中，其父节点则存到p */
    if(p==NULL){                                              /* 左子树只有一个叶子节点,只须让to_be_del->left 代替to_be_del的原来位置即可 */
      if(parent==NULL){                                       /* to_be_del是根 */
        /* to_be_del->left是叶子节点，让其成为root,代代替 to_be_del,并将其指向 to_be_del的右节点 */
        root->root=to_be_del->left;
        root->root->right=to_be_del->right;
      }else{
        if(parent->right==to_be_del){ /* to_be_del是parent的右子树 */
          parent->right=to_be_del->left;
        }else{                      /* parent 是to_be_del的父 节点,故不必考虑两者相等状*/
          parent->left=to_be_del->left;
        }
      }
    }else{                     /* n!=NULL,p!=NULL */
      p->right=NULL;            /* p不在指向这个刚到的最大值n,因为要把n移到 to_be_del的位置 */
      n->left=to_be_del->left;
      n->right=to_be_del->right;
      if(parent==NULL){
        root->root=n;
      }else{
        if(parent->right==to_be_del){ /* to_be_del是parent的右子树 */
          parent->right=n;
        }else{                      /* parent 是to_be_del的父 节点,故不必考虑两者相等状*/
          parent->left=n;
        }
      }
    }
  }
  free_node(to_be_del);
  root->size--;
  return 0;
}

/* private 从parent树中寻找最大的node,存到no中，其父节点存到par中，若无父，则par=NULL ,
   只需一路寻找右节点，直到null即寻到最大值
 */
int tree_largest(node_t *parent ,node_t **no,node_t **par){
  if(parent==NULL){
    *no=NULL;
    *par=NULL;
    return -1;
  }
  node_t *p,*n;
  p=NULL;
  n=parent;
  while(n->right!=NULL){
    p=n;
    n=n->right;
  }
  *no=n;
  *par=p;
  return 0;
}

/*private  在tree中搜索item,如果成功return 0 ,
  搜到的node_t 存到no中，其父节点则存到par中返回，若无父节点，则par为NULL
  失败返回-1 */
int tree_seek(node_t *parent ,Item item,node_t **no,node_t **par){
  if(parent==NULL) return -1;
  node_t *p,*n;
  int cmp;
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
int free_node(node_t *n){
  free(n);
}

int main(int argc, char *argv[]){
  tree_t t ;
  node_t *n,*p;
  int val;
  tree_init(&t);
  tree_add(&t,10);
  tree_add(&t,100);
  tree_add(&t,5);
  tree_add(&t,95);
  printf ("%d\n",t.size);
  printf ("%d\n",t.root->item);
  printf ("%d\n",t.root->right->item);
  printf ("%d\n",t.root->right->left->item);
  printf ("%d\n",t.root->left->item);
  tree_seek(t.root ,95,&n,&p);
  printf ("\n%d\n",n->item);

  tree_largest(t.root,&n,&p);
  printf ("\n%d,%d\n",n->item,p->item);


  tree_del(&t,5);
  printf ("%d\n",t.root->item);

  return 0;
}
