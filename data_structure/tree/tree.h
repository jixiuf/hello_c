#ifndef TREE_H
#define TREE_H
/* 此树不允许重复元素的存在 */

typedef int Item;

struct node {
  Item item;
  struct node * left;
  struct node * right;
};

typedef struct node node_t;

struct tree{
  node_t * root;
  int size;
  int (*item_cmp)(Item* item1,Item* item2);
};

typedef struct tree tree_t;


/* 初始化树,参数2是一个函数指针，主要用于用元素进行大小的比较 */
void tree_init(tree_t *root,int (*item_cmp)(Item *item1,Item *item2));
/* 添加元素 */
int tree_add(tree_t *root,Item item);
/* 删除元素 */
int tree_del(tree_t *root ,Item item);
/* 返回tree size */
int tree_size(tree_t *root);
/* 中序遍历 */
void mid_visit(tree_t *t,void (*v)(Item i));
/* 后序遍历 */
void after_visit(tree_t *t,void (*v)(Item i));
/* 前序遍历 */
void previous_visit(tree_t *t,void (*v)(Item i));

#endif
