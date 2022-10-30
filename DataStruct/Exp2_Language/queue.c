//
// Created by hang on 2022/10/20.
//
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

QueueNode* CreateQueueNode(){
    QueueNode *qn = (QueueNode*) malloc(sizeof(QueueNode*));
    qn->next = NULL;
    qn->data = NULL;
}

Queue* CreateQueue(){
    Queue *q = (Queue*) malloc(sizeof(Queue*));
    q->size = 0;
    q->tail = NULL;
    q->head = NULL;
    return q;
}
void PushQueue(struct Queue *que, DataType dt) {
    struct QueueNode *insertNode = (struct QueueNode *) malloc( sizeof(struct QueueNode) );
    insertNode->data = dt;
    insertNode->next = NULL;
    if(que->tail) {
        que->tail->next = insertNode;
        que->tail = insertNode;
    }else {
        que->head = que->tail = insertNode;
    }
    ++que->size;
}

void PopQueue(struct Queue* que) {
    struct QueueNode *temp = que->head;
    que->head = temp->next;
    free(temp);
    --que->size;
    if(que->size == 0) {
        que->tail = NULL;
    }
}

DataType QueueGetFront(struct Queue* que) {
    return que->head->data;
}
int QueueGetSize(struct Queue* que) {
    return que->size;
}
int QueueIsEmpty(struct Queue* que) {
    return !QueueGetSize(que);
}
void QueueClear(struct Queue* que) {
    que->head = que->tail = NULL;
    que->size = 0;
}