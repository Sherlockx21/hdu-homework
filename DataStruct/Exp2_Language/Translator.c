//
// Created by hang on 2022/10/20.
//

#include "check.h"
#include "parse.h"
#include "queue.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>


char lang[MAXSIZE];


int main(){
    system("chcp 65001");
    printf("请输入魔王语言：\n");
    scanf("%s",lang);
    while(!Check(lang)){
        printf("语言语法不正确，请重新输入：");
        scanf("%s",lang);
    }
    Queue *parshed = CreateQueue();
    Queue *translated = CreateQueue();
    parshed = Parse(lang);
    translated = Translate(parshed);
    printf("翻译结果为：");
    while(!QueueIsEmpty(translated)){
        printf("%c", QueueGetFront(translated));
        PopQueue(translated);
    }
}