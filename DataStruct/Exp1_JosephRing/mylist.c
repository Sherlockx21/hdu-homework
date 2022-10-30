//
// Created by hang on 2022/9/29.
//

#include "mylist.h"
#include <stdio.h>
#include <stdlib.h>

void Print(DataType e){
    printf("位置：%d，密码：%d\n",e.location,e.password);
}


ListNode* CreateListNode(DataType e){
    ListNode *node = (ListNode*) malloc(sizeof(ListNode));
    node->data = e;
    node->next = NULL;
    return node;
}

//建立循环链表
LinkList* CreateList(){
    LinkList *l = (LinkList*) malloc(sizeof(LinkList));
    l->head = NULL;
    l->length = 0;
    return l;
}

//获取头元素
ListNode* GetHead(LinkList *l){
    if(!l->length) return NULL;
    return l->head;
}

//获取链表长度
int GetLength(LinkList *l){
    return l->length;
}

//在链表末尾添加元素
void Append(LinkList *l,DataType e){
    ListNode *node = CreateListNode(e);
    if(!l->length){
        l->head = node;
    }else{
        ListNode *p = l->head;
        while(p->next != l->head) p = p->next;
        p->next = node;
    }
    node->next = l->head;
    l->length++;
}

//判断元素是否在链表中
int InList(LinkList *l,ListNode *elem){
    ListNode *p = l->head;
    while(p != elem && p->next != l->head) p = p->next;
    if(p != elem) return 0;
    else return 1;
}

//在元素后添加元素
int InsertNext(LinkList *l,ListNode *elem,DataType e){
    if(!InList(l,elem)) return 0;
    ListNode *node = CreateListNode(e);
    node->next = elem->next;
    elem->next = node;
    l->length++;
    return 1;
}

//移除元素
DataType Remove(LinkList *l,ListNode *elem){
    if(!InList(l,elem)){
        DataType temp = {0,0};
        return temp;
    }
    ListNode *p = l->head;
    while(p->next != elem) p = p->next;
    p->next = elem->next;
    l->length--;
    return elem->data;
}

//得到下一个元素
ListNode* GetNext(LinkList *l,ListNode *elem){
    if(!InList(l,elem)) return NULL;
    return elem->next;
}

void Traverse(LinkList *l){
    ListNode *p = l->head;
    while(p->next != l->head){
        Print(p->data);
        p = p->next;
    }
    Print(p->data);
}