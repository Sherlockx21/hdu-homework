//
// Created by hang on 2022/10/20.
//
#include "stack.h"
#include "check.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int Check(char* s){
    int i = 0;
    Stack *stack = CreateStack();
    while(s[i] != '\0'){
        if(StackGetSize(stack)  == 0){
            if(s[i] == ')') return 0;
            else if(s[i] == '(') PushStack(stack,s[i]);
        }else{
            if(s[i] == '(') PushStack(stack,s[i]);
            else if(s[i] == ')'){
                if(StackGetTop(stack) != '(') return 0;
                else PopStack(stack);
            }
        }
        i++;
    }
    if(!StackIsEmpty(stack)) return 0;
    return 1;
}

int Exist(char* s){
    int i = 0;
    while(s[i] != '\0'){
        if(s[i] == '(') return 1;
        i++;
    }
    return 0;
}