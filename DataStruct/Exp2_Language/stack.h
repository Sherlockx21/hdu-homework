//
// Created by hang on 2022/10/20.
//

#ifndef EXP2_LANGUAGE_STACK_H
#define EXP2_LANGUAGE_STACK_H

typedef char DataType;

typedef struct StackNode {
    DataType data;
    struct StackNode *next;
}StackNode;

typedef struct Stack {
    struct StackNode *top;
    int size;
}Stack;

StackNode* CreateStackNode();
Stack* CreateStack();
void PushStack(struct Stack *stk, DataType dt);
void PopStack(struct Stack* stk);
DataType StackGetTop(struct Stack* stk);
int StackGetSize(struct Stack* stk);
int StackIsEmpty(struct Stack* stk);
void StackClear(struct Stack* stk);

#endif //EXP2_LANGUAGE_STACK_H
