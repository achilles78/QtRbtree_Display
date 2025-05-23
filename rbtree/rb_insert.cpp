//
// Created by tangjun on 5/9/24.
//
#ifndef RB
#define RB
#endif
//#include "drawtree.h"
#include "include/head4tree.h"
#include "include/head4rb.h"

void insert_fixup(linktree *proot, linktree pNode_new) {
    if (pNode_new->parent == NULL)
    {
        pNode_new->color=BLACK;
        *proot=pNode_new;
        return;
    }

    if(pNode_new->parent->color == BLACK)  // 1: 黑父
        return;
    else
        insert_case1(proot, pNode_new);
}

void insert_case1(linktree *proot, linktree pNode)  // 2: 红父 + 红叔
{

    if (uncle(pNode) != NULL && uncle(pNode)->color == RED)
    {
        pNode->parent->color=BLACK;
        uncle(pNode)->color=BLACK;
        grandparent(pNode)->color=RED;

        insert_fixup(proot, grandparent(pNode));
    }
    else
    {
        insert_case2(proot, pNode);
    }
}
extern void rb_rotate_left(linktree *proot , linktree n);

extern void rb_rotate_right(linktree *proot, linktree pNode);
void insert_case2(linktree *proot, linktree pNode) // 3: 红父 + 黑叔
{
    if(pNode == pNode->parent->rchild &&
       pNode->parent == grandparent(pNode)->lchild)
    {
        rb_rotate_left(proot, pNode);
        pNode=pNode->lchild;
    }
    else if (pNode == pNode->parent->lchild &&
             pNode->parent == grandparent(pNode)->rchild)
    {
        rb_rotate_right(proot, pNode);
        pNode=pNode->rchild;
    }

    insert_case3(proot, pNode);

}

void insert_case3(linktree *proot, linktree pNode)  //3: 红父 + 黑叔
{
    pNode->parent->color=BLACK;
    grandparent(pNode)->color=RED;

    if (pNode == pNode->parent->lchild && pNode->parent == grandparent(pNode)->lchild)
    {
        rb_rotate_right(proot, pNode->parent);
    }
    else
        rb_rotate_left(proot, pNode->parent);
}

linktree bst_insert(linktree root, linktree pNode)
{
    if (root==NULL)
        return pNode;
    pNode->parent=root;
    if(pNode->data < root->data)
    {
        root->lchild= bst_insert(root->lchild, pNode);
    }
    else if(pNode->data > root->data)
    {
        root->rchild= bst_insert(root->rchild, pNode);
    }
    else
    {
        printf("%d exist.\n", pNode->data);
    }

    return root;
}

void rb_insert(linktree *proot, linktree pNode)
{
    *proot= bst_insert(*proot, pNode);
    insert_fixup(proot, pNode);
}




