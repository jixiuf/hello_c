//file name : test.c
//created at: 2012年06月03日 星期日 14时31分07秒
//author:  纪秀峰

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include "tree.h"

int item_cmp2(Item *i1, Item *i2){
  int *i1_int = (int*) i1;
  int *i2_int = (int*) i2;
  return (*i1_int - *i2_int);
}
void print(Item i ){
  printf ("visit %d\n",i);
}

       /*              10 */
       /*       5              15 */
       /*   2       8       13      18 */
       /* 1   3   6   9   11   14  16  19 */
       /*      4    7       12       17 */
int main(int argc, char *argv[]){
  tree_t t ;
  node_t *n,*p;
  int val;
  tree_init(&t,item_cmp2);
  tree_add(&t,10);
  tree_add(&t,5);
  tree_add(&t,15);
  tree_add(&t,2);
  tree_add(&t,8);
  tree_add(&t,13);
  tree_add(&t,18);
  tree_add(&t,1);
  tree_add(&t,3);
  tree_add(&t,6);
  tree_add(&t,9);
  tree_add(&t,11);
  tree_add(&t,14);
  tree_add(&t,16);
  tree_add(&t,19);
  tree_add(&t,4);
  tree_add(&t,7);
  tree_add(&t,12);
  tree_add(&t,17);
  /* printf ("%d\n",t.size); */
  /* printf ("%d\n",t.root->item); */
  /* printf ("%d\n",t.root->right->item); */
  /* printf ("%d\n",t.root->right->left->item); */
  /* printf ("%d\n",t.root->left->item); */
  /* tree_seek(t.root ,95,&n,&p); */
  /* printf ("\n%d\n",n->item); */

  /* tree_largest(t.root,&n,&p); */
  /* printf ("\n%d,%d\n",n->item,p->item); */
  /* tree_del(&t,5); */
  /* printf ("%d\n",t.root->item); */
  previous_visit(&t,print);
  printf ("size=%d\n",tree_size(&t));
  /* after_visit(&t,print_); */
  /* mid_visit(&t,print_); */

  return 0;
}
