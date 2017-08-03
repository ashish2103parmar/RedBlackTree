/*
   demo RB tree code
 */

#include <stdio.h>
#include <stdlib.h>
#include <rbtree.h>

extern int err;

/* user menu */
char *menu = 			\
"enter :				\n\
\t1. Insert 			\n\
\t2. Search 			\n\
\t3. find min	 		\n\
\t4. find max		 	\n\
\t5. Delete Node 		\n\
\t6. BF print			\n\
\t0. Exit\n :";

/* main funciton */
void main()
{
  rb_node *root = NULL, *tmp;
  int choice;
  int buff;
  uint pos;

  while (1)
  {
	/* give user menu and read choice */
	printf("%s", menu);
	scanf("%d", &choice);

	/* processes user choice */
	switch (choice)
	{
	  case 0:
		/* Exit */
		break;

	  case 1:
		/* Insert */
		printf("Enter Data :");
		scanf("%d", &buff);

		/* insert data */
	
		root = insert_rbnode(root, buff);	
		root->col = black;
		if (err == success)
			printf("data inserted in tree\n");
		else
			printf("insert failed");
		continue;

	  case 2:
		/* search tree */
		if (!root)
		{
		  printf("no tree\n");
		  continue;
		}
		printf("Enter val :");
		scanf("%d", &buff);

		tmp = search_tree(root, buff);
		if (tmp)
		  printf("node found, val = %d\n", *tmp->data);
		else
		  printf("node not found\n");
		continue;

	  case 3:
		/* get min */
		if (!root)
		{
		  printf("no tree\n");
		  continue;
		}
		tmp = find_min(root);
		if (tmp)
		  printf("min value is %d\n", *tmp->data);
		else
		  printf("root is empty\n");
		continue;

	  case 4:
		/* get max */
		if (!root)
		{
		  printf("no tree\n");
		  continue;
		}
		tmp = find_max(root);
		if (tmp)
		  printf("max value is %d\n", *tmp->data);
		else
		  printf("root is empty\n");
		continue;

	  case 5:
		/* delete node */
		if (!root)
		{
		  printf("no tree\n");
		  continue;
		}
		printf("Enter val :");
		scanf("%d", &buff);

		root = del_rbnode(root, buff);
		if (root)
			root->col = black;
		if (err == success)
		  printf("deleted\n");
		else
		  printf("failed: %d\n", err);
		continue;

	  case 6:
		/* print tree */
		if (!root)
		{
		  printf("no tree\n");
		  continue;
		}
		bfprint(root);
		printf("\n");
		continue;

	  case 7:
		/* rb tree black height and validation */
		printf(" rb - %d\n", check_rbtree(root));
		continue;

	  default:
		/* invalid choice */
		printf("Invalid choice.. \n");
		continue;
	}  
	break;
  }
}
