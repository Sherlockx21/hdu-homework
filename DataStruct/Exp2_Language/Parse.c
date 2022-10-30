//
// Created by hang on 2022/10/20.
//
#include "queue.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include "parse.h"

char A[3] = "sae";
char B[4] = "tAdA";

Queue* Parse(char *s){
    int i = 0;
    Stack *stack1 = CreateStack();
    Stack *stack2 = CreateStack();
    Stack *stack3 = CreateStack();
    StackNode *t = CreateStackNode();
    while(s[i] != '\0'){
        if(s[i] == ')') {
            while (StackGetTop(stack1) != '(') {
                PushStack(stack2, StackGetTop(stack1));
                PopStack(stack1);
            }
            PopStack(stack1);
            t = StackGetTop(stack2);
            PopStack(stack2);
            PushStack(stack3, t);
            while (!StackIsEmpty(stack2)) {
                PushStack(stack3, StackGetTop(stack2));
                PushStack(stack3, t);
                PopStack(stack2);
            }
            while (!StackIsEmpty(stack3)) {
                PushStack(stack1, StackGetTop(stack3));
                PopStack(stack3);
            }
        }else{
            PushStack(stack1,s[i]);
        }
        i++;
    }
    while(!StackIsEmpty(stack1)){
        PushStack(stack2, StackGetTop(stack1));
        PopStack(stack1);
    }
    Queue *queue = CreateQueue();
    while(!StackIsEmpty(stack2)){
        PushQueue(queue, StackGetTop(stack2));
        PopStack(stack2);
    }
    return queue;
}


Queue* Translate(Queue* q){
    Queue *queue = CreateQueue();
    while(!QueueIsEmpty(q)){
        if(QueueGetFront(q) == 'A'){
           for(int i = 0;i < 3;i++){
               PushQueue(queue,A[i]);
           }
        }else if(QueueGetFront(q) == 'B'){
            for(int i = 0;i < 4;i++){
                if(B[i] == 'A'){
                    for(int j = 0;j < 3;j++){
                        PushQueue(queue,A[j]);
                    }
                }else{
                    PushQueue(queue,B[i]);
                }
            }
        }else{
            PushQueue(queue, QueueGetFront(q));
        }
        PopQueue(q);
    }
    return queue;
}

//Queue* Translate(Queue* q){
//    Queue *queue = (Queue*) malloc(sizeof(Queue*));
//    while(!QueueIsEmpty(q)){
//        if(QueueGetFront(q) >= 'A' && QueueGetFront(q) <= 'Z'){
//            int key = QueueGetFront(q) - 'A';
//            int i = 0;
//            while(Map[key][i] != '\0'){
//                PushQueue(queue,Map[key][i]);
//                i++;
//            }
//        }else{
//            PushQueue(queue, QueueGetFront(q));
//        }
//        PopQueue(q);
//    }
//    return queue;
//}