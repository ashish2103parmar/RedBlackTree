/*
   Red Black Tree
 */

#ifndef RBTREE_H
#define RBTREE_H

typedef enum 
{
	red = 0,
	black,
	dblack,
} rb_col;

typedef struct RB_TREE_ST
{
	struct RB_TREE_ST *left, *right;
	unsigned char col;
	int *data;
} rb_node;

typedef enum
{
	in_process = -1,
	success = 0,
	failure,
	data_exist,
	red_red,
	reordering
} err_t;


/* insert a node */
rb_node *insert_rbnode(rb_node *root, int data);
/* print tree */
void bfprint(rb_node *root);
/* get min */
rb_node *find_min(rb_node *root);
/* get max */
rb_node *find_max(rb_node *root);
/* search tree */
rb_node *search_tree(rb_node *root, int val);
/* delete node */
rb_node *del_rbnode(rb_node *root, int val);
/* check validity */
int check_rbtree(rb_node *root);

#endif
