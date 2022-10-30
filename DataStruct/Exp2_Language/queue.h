//
// Created by hang on 2022/10/20.
//

#ifndef EXP2_LANGUAGE_QUEUE_H
#define EXP2_LANGUAGE_QUEUE_H

typedef char DataType;

typedef struct QueueNode {
    DataType data;
    struct QueueNode *next;
}QueueNode;

typedef struct Queue {
    struct QueueNode *head, *tail;
    int size;
}Queue;

QueueNode* CreateQueueNode();
Queue* CreateQueue();
void PushQueue(struct Queue *que, DataType dt);
void PopQueue(struct Queue* que);
DataType QueueGetFront(struct Queue* que);
int QueueGetSize(struct Queue* que);
int QueueIsEmpty(struct Queue* que);
void QueueClear(struct Queue* que);

#endif //EXP2_LANGUAGE_QUEUE_H
