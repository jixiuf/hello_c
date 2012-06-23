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

void avl_init(avl_tree_t* tree,int (*item_cmp)(Item* item1,Item* item2));
int avl_add(avl_tree_t* avl,Item item);
int avl_size(avl_tree_t * avl);

#endif
