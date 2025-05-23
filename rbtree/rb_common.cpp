//
// Created by tangjun on 9/11/24.
//
#ifndef RB
#define RB
#endif

//#include "drawtree.h"
#include "include/head4tree.h"
#include "include/head4rb.h"

void rb_rotate_left(linktree *proot, linktree n)
{
    linktree gp = grandparent(n);
    linktree p = n->parent;

    p->rchild = n->lchild;
    if (n->lchild != NULL)
        n->lchild->parent = p;
    n->lchild = p;
    p->parent = n;

    if (*proot == p)
        *proot = n;

    n->parent = gp;
    if (gp != NULL) {
        if (p == gp->lchild)
            gp->lchild = n;
        else
            gp->rchild = n;
    }

}

void rb_rotate_right(linktree *proot, linktree pNode)
{
    linktree gp= grandparent(pNode);
    linktree p=pNode->parent;

    p->lchild=pNode->rchild;
    if (pNode->rchild != NULL)
        pNode->rchild->parent= p;

    pNode->rchild=p;
    p->parent=pNode;

    if(*proot==p)
        *proot=pNode;

    pNode->parent=gp;

    if (gp!=NULL)
    {
        if (p==gp->lchild)
            gp->lchild=pNode;
        else
            gp->rchild=pNode;
    }

}
