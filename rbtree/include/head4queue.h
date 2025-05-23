//
// Created by tangjun on 9/11/24.
//

#ifndef RED_BLACK_HEAD4QUEUE_H
#define RED_BLACK_HEAD4QUEUE_H
#include "commonheader.h"
#include "head4tree.h"
#ifndef QUEUE_NODE_DATATYPE
#define QUEUE_NODE_DATATYPE int
#endif

typedef linktree qn_datatype;

struct _queue_node
{
    qn_datatype data;
    struct _queue_node *next;

};

typedef struct _queuenode
{
    struct _queue_node *front;
    struct _queue_node *rear;
#ifdef QUEUE_SIZE
    int size;
#endif
}queuenode, *linkqueue;

bool is_empty_q(linkqueue);
// bool out_queue(linkqueue, qn_datatype *);
// bool en_queue(linkqueue, qn_datatype);
bool out_queue(linkqueue, linktree *);
bool en_queue(linkqueue, linktree);
linkqueue init_queue(void);

#ifdef QUEUE_SIZE
int queue_size(linkqueue *);
#endif
#endif //RED_BLACK_HEAD4QUEUE_H
