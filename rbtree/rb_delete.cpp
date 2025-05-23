//
// Created by tangjun on 12/25/24.
//

#ifndef RB
#define RB
#endif

//#include "drawtree.h"
#include "include/head4tree.h"
#include "include/head4rb.h"

linktree rb_find(linktree root, tn_datatype data)
{
    if (root == NULL)
        return NULL;

    if (data < root->data)
        return rb_find(root->lchild, data);
    else if (data > root->data)
        return rb_find(root->rchild, data);

    return root;
}

extern void rb_rotate_left(linktree *proot, linktree n);

extern void rb_rotate_right(linktree *proot, linktree pNode);

void delete_fixup(linktree *proot, linktree pNode_new, linktree parent)
{
    printf("%s\n", __FUNCTION__);
    linktree ln, rn; // left nephew & right nephew
    linktree s, gp;  // sibling & grandparent
    ln = rn = s = gp = NULL;

    if (pNode_new == NULL && parent == NULL) // 原来的old是树的唯一节点
    {
        *proot = NULL;
        return;
    } else if (pNode_new != NULL && parent == NULL) // 原来的old是根节点
    {
        *proot = pNode_new;
        return;
    } else if (parent != NULL) {
        /*
         * 这里找兄弟节点的语句有问题：向上调整时，待调整的黑色游离权重节点不总为NULL节点
         * 比如：按顺序1->2.2调整，或者连续2次2.2调整，这2种情况中
         * 第2次2.2调整中parent的lchild和rchild不为空。
         */
        //s = parent->lchild ? parent->lchild : parent->rchild;
        s = (pNode_new == parent->lchild) ? parent->rchild : parent->lchild;
        gp = parent->parent;
        if (s != NULL) {
            ln = s->lchild;
            rn = s->rchild;
        }
    }
    // 1, 红兄
    if (Color(s) == RED)
    {
        if (pNode_new == parent->lchild) {
            rb_rotate_left(proot, s);
            parent->color = RED;
            s->color = BLACK;

            delete_fixup(proot, pNode_new, parent);
        }
        if (pNode_new == parent->rchild) {
            rb_rotate_right(proot, s);
            parent->color = RED;
            s->color = BLACK;

            delete_fixup(proot, pNode_new, parent);
        }
    }


    //2 黑兄
    if (Color(s) == BLACK)
    {
        //2.1，黑兄，二黑侄，红父
        if (Color(parent)==RED && Color(ln)==BLACK && Color(rn)==BLACK)
        {
            parent->color=BLACK;
            if (s!=NULL)  //todo: 这里应该不用判断
                s->color=RED;
            return;
        }

        //2.2 黑兄，二黑侄，黑父
        if(Color(parent)==BLACK && Color(ln)==BLACK && Color(rn)==BLACK)
        {
            if (s!=NULL)  //todo: 这里应该不用判断
                s->color=RED;
            delete_fixup(proot,parent,parent->parent);
        }

        //2.3，黑兄，同边红侄（同为左孩子）
        if (Color(ln)==RED && pNode_new == parent->lchild)
        {
            rb_rotate_right(proot,ln);
            //加了这2行，更容易理解一点，和网上算法介绍中一致，不加也不影响结果。
            //ln->color=BLACK;
            //s->color=RED;
            rb_rotate_left(proot,ln);

            ln->color=parent->color;
            s->color=BLACK;

            parent->color=BLACK;
        }
        // (同为右孩子)
        else if (Color(rn)==RED && pNode_new == parent->rchild)
        {
            rb_rotate_left(proot,rn);
            //加了这2行，更容易理解一点，和网上算法介绍中一致，不加也不影响结果。
            //rn->color=BLACK;
            //s->color=RED;
            rb_rotate_right(proot,rn);

            rn->color = parent->color;
            parent->color = BLACK;
        }
        // 对边红侄(左右)
        else if (Color(ln)==RED && pNode_new == parent->rchild)
        {
            rb_rotate_right(proot,s);
            s->color=parent->color;

            parent->color=BLACK;
            ln->color=BLACK;
        }
        // 对边红侄(右左)
        else if (Color(rn)==RED && pNode_new == parent->lchild)
        {
            rb_rotate_right(proot,s);
            s->color=parent->color;

            parent->color=BLACK;
            rn->color=BLACK;
        }
    }
}

void real_delete(linktree *proot, linktree old)
{
    printf("%s\n", __FUNCTION__);
    linktree pTreeNode = old->lchild ? old->lchild : old->rchild;
    linktree parent = old->parent;
    // old不可能为NULL，new可能为NULL
    if (old->parent != NULL) {

        if (old == old->parent->lchild)
            old->parent->lchild = pTreeNode;
        else
            old->parent->rchild = pTreeNode;

        old->parent = NULL;
    }
    if (pTreeNode != NULL)
        // pTreeNode->parent=old->parent;
        //貌似错了,应该改成：
        pTreeNode->parent = parent;

    //针对替换节点的3种情况处理
    if (Color(old) == BLACK && Color(pTreeNode) == RED) {
        //情况1：替换节点是黑色的，且有一个后继节点new，根据红黑树的性质，new只能是红色的
        pTreeNode->color = BLACK;
    } else if (Color(old) == BLACK && Color(pTreeNode) == BLACK) {
        // 情况2:替换节点old没有后继节点(new为黑色，根据红黑树的性质，只能是空节点)
        delete_fixup(proot, pTreeNode, parent);
    }
    //情况3:替换节点old是红节点，
    // 根据红黑树的性质，替换节点是红色时，不会有非空子节点了，可以直接删除，不用特别处理。

    free(old);
}

void rb_delete(linktree *proot, tn_datatype data)
{
    linktree tmp = rb_find(*proot, data);
    if (tmp == NULL) {
        printf("%d is NOT exist.\n", data);
        return;
    }

    linktree n = tmp;

    /*
    * 书里这个算法的实现是优先使用前驱节点作为被删除节点的替换节点。
    * 而且多了一步：在没有前驱节点的情况下，就会使用后继节点作为替换节点(感觉这一步有点多余，增加了复杂性)
    * 网上介绍红黑树的文章都习惯使用后继节点作为替换节点，更简洁。
    */
    if (tmp->lchild != NULL) {
        n = tmp->lchild;
        for (; n->rchild != NULL; n = n->rchild);
        tmp->data = n->data;
    } else if (tmp->rchild != NULL) {
        n = tmp->rchild;
        for (; n->lchild != NULL; n = n->lchild);
        tmp->data = n->data;
    }

    real_delete(proot, n);

}
