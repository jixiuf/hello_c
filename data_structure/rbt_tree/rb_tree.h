#ifndef RB_TREE_H
#define RB_TREE_H

typedef int Item;

enum RB_NODE_COLOR{
  RED,BLACK
};

struct rb_node {
  Item item;
  struct rb_node * left;
  struct rb_node * right;
  struct rb_node * parent;
  enum RB_NODE_COLOR color;
};

typedef struct rb_node rb_node_t;

struct rb_tree{
  rb_node_t * root;
  int size;
  int (*item_cmp)(Item* item1,Item* item2);
};

typedef struct rb_tree rb_tree_t;

/* 初始化树,参数2是一个函数指针，主要用于用元素进行大小的比较 */
void rb_init(rb_tree_t* tree,int (*item_cmp)(Item* item1,Item* item2));
void rb_destory(rb_tree_t *tree);
int rb_add(rb_tree_t* rb,Item item);
int rb_size(rb_tree_t * rb);
int rb_del(rb_tree_t* tree,Item item);
int rb_find(rb_tree_t *root,Item item,Item *out);

/* 遍历的方式以父节点N、左子树Left ,右子树Right的访问顺序而定 */
/* 后序遍历LRN */
void after_visit(rb_tree_t *t,void (*v)(Item i));
/* 中序遍历LNR */
void mid_visit(rb_tree_t *t,void (*v)(Item i));
/* 前序遍历NLR */
void previous_visit(rb_tree_t *t,void (*v)(Item i));



#endif
