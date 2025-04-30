
#ifndef _HEAD4TREE_H_
#define _HEAD4TREE_H_


#ifndef TREE_NODE_DATATYPE
#define TREE_NODE_DATATYPE int
#endif

#include "commonheader.h"

#define MAX(a, b) ({ \
		typeof(a) _a = a; \
		typeof(b) _b = b; \
		(void)(&_a == &_b);\
		_a > _b? _a : _b; \
		})

typedef TREE_NODE_DATATYPE tn_datatype;
#ifndef RB
#define RB
#endif
#ifdef RB
#define RED   0
#define BLACK 1
#endif

typedef struct _tree_node
{
	tn_datatype data;
	struct _tree_node *lchild;
	struct _tree_node *rchild;

#ifdef AVL
	int height;
#endif

#ifdef RB
	struct _tree_node *parent;
	int color;
#endif
}treenode, *linktree;

void pre_travel(linktree, void (*handler)(linktree));
void mid_travel(linktree, void (*handler)(linktree));
void post_travel(linktree, void (*handler)(linktree));
void level_travel(linktree, void (*handler)(linktree));

linktree bst_insert(linktree root, linktree pNode);
linktree bst_remove(linktree root, tn_datatype data);
linktree bst_find(linktree root, tn_datatype data);

#ifdef AVL
linktree avl_insert(linktree root, linktree new);
linktree avl_remove(linktree root, tn_datatype data);

linktree avl_rotate_left (linktree root);
linktree avl_rotate_right(linktree root);
linktree avl_rotate_leftright(linktree root);
linktree avl_rotate_rightleft(linktree root);

static int height(linktree root)
{
	return root==NULL ? 0 : root->height;
}
#endif

static linktree new_node(tn_datatype data)
{
	linktree pNode_new = (linktree)malloc(sizeof(treenode));
	if(pNode_new != NULL)
	{
        pNode_new->data = data;
        pNode_new->lchild = NULL;
        pNode_new->rchild = NULL;

		#ifdef AVL
		pNode_new->height = 1;
		#endif

		#ifdef RB
        pNode_new->parent = NULL;
        pNode_new->color = RED;
		#endif
	}
	return pNode_new;
}

#endif
