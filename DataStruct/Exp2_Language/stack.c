//
// Created by hang on 2022/10/20.
//
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

StackNode* CreateStackNode(){
    StackNode *sn = (StackNode*) malloc(sizeof(StackNode*));
    sn->next = NULL;
    sn->data =NULL;
    return sn;
}

Stack* CreateStack(){
    Stack *s = (Stack*) malloc(sizeof(Stack*));
    s->size = 0;
    s->top = NULL;
    return s;
}

void PushStack(struct Stack *stk, DataType dt) {
    struct StackNode *insertNode = (struct StackNode *) malloc( sizeof(struct StackNode) );
    insertNode->next = stk->top;
    insertNode->data = dt;
    stk->top = insertNode;
    ++ stk->size;
}
void PopStack(struct Stack* stk) {
    struct StackNode *temp = stk->top;
    stk->top = temp->next;
    --stk->size;
    free(temp);
}

DataType StackGetTop(struct Stack* stk) {
    return stk->top->data;
}
int StackGetSize(struct Stack* stk) {
    return stk->size;
}

int StackIsEmpty(struct Stack* stk) {
    return !StackGetSize(stk);
}

void StackClear(struct Stack* stk) {
    while(!StackIsEmpty(stk)) {
        PopStack(stk);
    }
    stk->top = NULL;
    stk->size = 0;
}