//myqueue.h
#ifndef __MYQUEUE_H__
#define __MYQUEUE_H__

#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 1000

struct node{
  int x;
  int y;
}elem[MAXSIZE];

typedef struct _CNode{

    struct node elem[MAXSIZE];
    int front;        //下标可取,指向队头元素
    int rear;            //下标不可取,指向元素应放入的位置
}CNode, *CQueue;


void InitCQueue(CQueue pQueue);             //初始化队列
void Push(CQueue pQueue,struct node val);       //入队，从队尾(rear)入
struct node Pop(CQueue pQueue);     //出队，从队首(front)出
int GetCQueueLen(CQueue pQueue);         //获取队列长度
void ShowQueue(CQueue pQueue);           //输出队列所有元素
bool IsEmpty(CQueue pQueue);             //队列为空则返回true
bool IsFull(CQueue pQueue);                 //队列满则返回false
struct node GetFront(CQueue pQueue); //获取队首元素

#endif
