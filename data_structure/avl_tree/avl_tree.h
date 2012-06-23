#ifndef AVL_TREE_H
#define AVL_TREE_H

typedef int Item;

struct avl_node {
  Item item;
  struct avl_node * left;
  struct avl_node * right;
  struct avl_node * parent;
  int height;
};

typedef struct avl_node avl_node_t;

struct avl_tree{
  avl_node_t * root;
  int size;
  int (*item_cmp)(Item* item1,Item* item2);
};

typedef struct avl_tree avl_tree_t;

/* 初始化树,参数2是一个函数指针，主要用于用元素进行大小的比较 */
void avl_init(avl_tree_t* tree,int (*item_cmp)(Item* item1,Item* item2));
void avl_destory(avl_tree_t *tree);
int avl_add(avl_tree_t* avl,Item item);
int avl_size(avl_tree_t * avl);
int avl_del(avl_tree_t* tree,Item item);
int avl_find(avl_tree_t *root,Item item,Item *out);

/* 遍历的方式以父节点N、左子树Left ,右子树Right的访问顺序而定 */
/* 后序遍历LRN */
void after_visit(avl_tree_t *t,void (*v)(Item i));
/* 中序遍历LNR */
void mid_visit(avl_tree_t *t,void (*v)(Item i));
/* 前序遍历NLR */
void previous_visit(avl_tree_t *t,void (*v)(Item i));

#endif
