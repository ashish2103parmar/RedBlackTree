#include <stdio.h>
#include <stdlib.h>
#include <rbtree.h>

int err = 0;

rb_node *create_rbnode(int data)
{
	rb_node *node = malloc(sizeof (rb_node));
	if (node)
	{
		node->left = NULL;
		node->right = NULL;
		node->col = red;
		node->data = malloc(sizeof (int));
		*node->data = data;
	}
	return node;
}

rb_node *rb_rotate_right(rb_node *root)
{
	if (root && root->left)
	{
		char tmpc = root->col;
		root->col = root->left->col;
		root->left->col = tmpc;

		rb_node *tmp = root->left->right;
		root->left->right = root;
		root = root->left;
		root->right->left = tmp;
	}
	return root;
}

rb_node *rb_rotate_left(rb_node *root)
{
	if (root && root->right)
	{
		char tmpc = root->col;
		root->col = root->right->col;
		root->right->col = tmpc;

		rb_node *tmp = root->right->left;
		root->right->left = root;
		root = root->right;
		root->left->right = tmp;
	}
	return root;
}

rb_node *rb_insert_correct(rb_node *gpa, rb_node *pa)
{
	if (gpa && pa)
	{
		if (gpa->left == pa && pa->left && pa->left->col == red)
			gpa = rb_rotate_right(gpa);
		else if (gpa->left == pa && pa->right && pa->right->col == red)
		{
			gpa->left = rb_rotate_left(pa);
			gpa = rb_rotate_right(gpa);
		}
		else if (gpa->right == pa && pa->left && pa->left->col == red)
		{
			gpa->right = rb_rotate_right(pa);
			gpa = rb_rotate_left(gpa);
		}
		else if (gpa->right == pa && pa->right && pa->right->col == red)
			gpa = rb_rotate_left(gpa);
		else
			err = reordering;
	}
	return gpa;
}

rb_node *insert_rbnode(rb_node *root, int data)
{
	if (root)
	{
		if (root->data)
		{
			if (*root->data == data)
				err = data_exist;
			else if (*root->data < data)
			{
				root->right = insert_rbnode(root->right, data);
				if (err == red_red)
				{
					if (!root->left || root->left->col == black)
					{
						err = success;
						return rb_insert_correct(root, root->right);
					}
					else
					{
						root->right->col = black;
						root->left->col = black;
						root->col = !root->col;
						err = success;
					}
				}
				if (root->col == red && root->right && root->right->col == red)
					err = red_red;
				else
					err = 0;
			}
			else
			{
				root->left = insert_rbnode(root->left, data);
				if (err == red_red)
				{
					if (!root->right || root->right->col == black)
					{
						err = success;
						return rb_insert_correct(root, root->left);
					}
					else
					{
						root->right->col = black;
						root->left->col = black;
						root->col = !root->col;
						err = success;
					}
				}
				if (root->col == red && root->left && root->left->col == red)
					err = red_red;
				else
					err = 0;
			}
		}
		else
		{
			*root->data = data;
			root->col = red;
			err = success;
		}
	}
	else
	{	
		root = create_rbnode(data);
		err = success;
	}
	return root;
}

rb_node *get_parent(rb_node *root, rb_node *node, rb_node **parent)
{
	if (root)
	{
		if (root == node)
			*parent = (rb_node *)-1;
		else
		{
			if (root->data && node && *root->data < *node->data)
			{
				if (root->right->data && *root->right->data == *node->data)
					*parent = root;
				else
					root->right = get_parent(root->right, node, parent);
			}
			else
			{
				if (root->left->data && *root->left->data == *node->data)
					*parent = root;
				else
					root->left = get_parent(root->left, node, parent);
			}
		}
	}
	return root;
}

/* print nodes of required lvl */
int print_lvl(rb_node *root, unsigned int lvl)
{
	char *redc = "\x1b[31m";
	if (root)
	{
		/* check if required lvl is reached */
		if (!lvl)
			/* print data */
		{
			if (root->col == red) printf("%s", redc);
			if (root->data)
				return printf("%d \x1b[0m", *root->data);
			else
				return printf("N ");
		}
		else
			/* move down on both side */
			return print_lvl(root->left, lvl - 1) + print_lvl(root->right, lvl - 1);
	}
	/* return 0 if NULL is reached */
	return 0;
}

/* bf print */
void bfprint(rb_node *root)
{
	if (!root)
		return;

	int lvl = 0;
	/* print from lvl 0 to height of node */
	while (print_lvl(root, lvl++))
		printf("\n");
}

/* find min value in tree */
rb_node *find_min(rb_node *root)
{
  /* keep moving to left */
  if ( root && root->left)
	return  find_min(root->left);
  else if (root)
  {
	/* save the left most data */
	return root;
  }
  else
	return NULL; 
}

/* find max value in tree */
rb_node *find_max(rb_node *root)
{  
  /* keep moving to right */
  if ( root && root->right)
	return  find_max(root->right);
  else if (root)
  {
	/* save the left most data */
	return root;
  }
  else
	return NULL; 
}

/* search for node in tree */
rb_node *search_tree(rb_node *root, int val)
{
  if (root)
  {
	/* if val found return root */
	if (root->data && *root->data == val)
	  return root;
	else if (root->data)
	  /* move to right if val is greater than node data then move to right else move to left */
	  return search_tree( (val > *root->data) ? root->right : root->left ,val);
  }
	/* return NULL if not found */
	return NULL;
}

rb_node *correct_dblack(rb_node *root, rb_node *dbnode)
{
	if (root)
	{
		int pos = (root->left == dbnode);
		rb_node *sib = pos ? root->right : root->left;
		if (sib && sib->col == red)
		{
			if (pos)
			{
				root = rb_rotate_left(root);
				root->left = correct_dblack(root->left, dbnode);
			}
			else
			{
				root = rb_rotate_right(root);
				root->right = correct_dblack(root->right, dbnode);
			}
		}
		else if (sib && sib->col == black && (!sib->left || sib->left->col == black) && (!sib->right || sib->right->col == black))
		{
			root->col += black;
			sib->col = red;
			if (dbnode && dbnode->data)
				dbnode->col = black;
			else
			{
				free(dbnode);
				if (pos)
					root->left = NULL;
				else
					root->right = NULL;
			}
		}
		else if (sib && sib->col == black)
		{
			if (pos)
			{
				if (!(sib->right && sib->right->col == red))
				{
					root->right = rb_rotate_right(sib);
					return correct_dblack(root, dbnode);
				}
				else
				{
					root = rb_rotate_left(root);
					root->right->col = black;
					if (dbnode && dbnode->data)
						dbnode->col = black;
					else
					{
						free(dbnode);
						root->left->left = NULL;
					}
				}
			}
			else
			{
				if (!(sib->left && sib->left->col == red))
				{
					root->left = rb_rotate_left(sib);
					return correct_dblack(root, dbnode);
				}
				else
				{
					root = rb_rotate_right(root);
					root->left->col = black;
					if (dbnode && dbnode->data)
						dbnode->col = black;
					else
					{
						free(dbnode);
						root->right->right = NULL;
					}
				}
			}
		}
		else
			err = failure;
	}
	else
		err = failure;
	return root;
}

rb_node *del_rbnode(rb_node *root, int val)
{
	if (root)
	{
		if (root->data && *root->data == val)
		{
			if (root->left  && root->left->data && root->right && root->right->data)
			{
				rb_node *min;
				if (min = find_min(root->right))
				{
					int *tmp = root->data;
					root->data = min->data;
					min->data = tmp;
					root->right = del_rbnode(root->right, val);
					if (root->right && root->right->col == dblack)
						return correct_dblack(root, root->right);
				}
			}
			else if ((root->left && root->left->data) || (root->right && root->right->data))
			{
				rb_node *tmp = (root->left && root->left->data) ? root->left : root->right;
				free(root);
				tmp->col += black;
				err = success;
				return tmp;
			}
			else
			{
				if (root->left)
				{
					free(root->left);
					root->left = NULL;
				}
				if (root->right)
				{
					free(root->left);
					root->left = NULL;
				}
				free(root->data);
				root->data = NULL;
				err = success;
				root->col += black;
				if (root->col != dblack)
					return NULL;
			}
		}
		else if (root->data && *root->data < val)
		{
			root->right = del_rbnode(root->right, val);
			if (root->right && root->right->col == dblack)
				return correct_dblack(root, root->right);
		}
		else if (root->data && *root->data > val)
		{
			root->left = del_rbnode(root->left, val);
			if (root->left && root->left->col == dblack)
				return correct_dblack(root, root->left);
		}
		else
			err = failure;
	}
	return root;
}


int check_rbtree(rb_node *root)
{
	if (!root || !root->data)
		return 1;

	int l_height, r_height;
	l_height = check_rbtree(root->left);
	r_height = check_rbtree(root->right);

	if (l_height == r_height)
		return (root->col == black) + l_height;
	else
		return 0;
}
