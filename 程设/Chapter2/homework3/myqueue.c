//myueue.c
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "myqueue.h"

//初始化队列
void InitCQueue(CQueue pQueue){
    if (NULL == pQueue)
        return;
    pQueue->front = 0;
    pQueue->rear = 0;
}

//入队，从队尾(rear)入
void Push(CQueue pQueue,struct node val){
    //入队之前应该先判断队列是否已经满了
    if (IsFull(pQueue)){
        return;
    }
    pQueue->elem[pQueue->rear]= val;               //将元素放入队列，这里也说明front是可取的
    pQueue->rear = (pQueue->rear+ 1) % MAXSIZE;    //更新队尾位置
}

//出队，从队首(front)出
struct node Pop(CQueue pQueue){
    //出队之前应该先判断队列是否是空的
    if (IsEmpty(pQueue)){
        return {-1,-1};
    }
    struct node rtval = pQueue->elem[pQueue->front];           //取出队头元素
    pQueue->front = (pQueue->front+ 1) % MAXSIZE;  //更新队头位置

    return rtval;
}

//获取队列长度
int GetCQueueLen(CQueue pQueue){
    return ((pQueue->rear - pQueue->rear + MAXSIZE) % MAXSIZE);
}

//输出队列所有元素
void ShowQueue(CQueue pQueue){
    int front = pQueue->front;
    int rear = pQueue->rear;
    while (front != rear){
        printf("{%d.%d}", pQueue->elem[front].x,pQueue->elem[front].y);
        front++;
    }
    printf("\n");
    return;
}

//队列为空则返回true
bool IsEmpty(CQueue pQueue){
    return pQueue->rear == pQueue->front;
}

//队列满则返回false
bool IsFull(CQueue pQueue){
    return (pQueue->rear + 1)%MAXSIZE == pQueue->front;
}

//获取队首元素
struct node GetFront(CQueue pQueue){
    if (!IsEmpty(pQueue)){
        struct node rtval = pQueue->elem[pQueue->front];   //将队头元素通过*rtval返回
        return rtval;
    }
    return {-1,-1};
}


int main(){
    CNode head;
    InitCQueue(&head);

    for (int i = 1; i < 10; ++i){
        Push(&head,{i,i});
    }

    printf("Qlength: %d\n", GetCQueueLen(&head));

    ShowQueue(&head);

    int tmp = 0;    //用于暂存出队的元素

    while (!IsEmpty(&head)){
        node p = Pop(&head);
            printf("Poped Item: %d %d\n", p.x, p.y);

    }

    return 0;
}
