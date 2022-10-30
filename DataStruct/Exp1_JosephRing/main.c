//
// Created by hang on 2022/10/4.
//
#include "mylist.h"
#include "joseph.h"
#include <stdio.h>
#include <windows.h>
DataType e[10000];

//int test(){
//    system("chcp 65001");
//    LinkList *l = CreateList();
//    ListNode *n;
//    printf("len:%d\n",GetLength(l));
//    for(int i = 0;i < 5;i++){
//        e[i].location = i + 1;
//        scanf("%d",&e[i].password);
//        Append(l,e[i]);
//    }
//    Print(GetHead(l)->data);
//    printf("len:%d\n", GetLength(l));
//    Traverse(l);
//    ListNode *s = GetHead(l);
//    s = s->next;
//    DataType e = {2,3};
//    InsertNext(l,s,e);
//    Traverse(l);
//    Print(Remove(l,s));
//    Traverse(l);
//    printf("\n");
//    Print(GetNext(l,l->head)->data);
//    return 0;
//}

int main(){
    system("chcp 65001");
    int n,m,out;
    LinkList *l = CreateList();
    printf("请输入人数：");
    scanf("%d",&n);
    printf("请按顺序输入%d个人的密码：",n);
    for(int i = 1;i <= n;i++){
        e[i].location = i;
        scanf("%d",&e[i].password);
        Append(l,e[i]);
    }

    printf("当前队列情况：\n");
    Traverse(l);

    printf("请输入初始密码：");
    scanf("%d",&m);
    printf("请输入出列人数：");
    scanf("%d",&out);

    printf("下列是出列情况\n");
    Joseph(l,out,m);

    return 0;
}