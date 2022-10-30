//
// Created by hang on 2022/9/29.
//

#ifndef _MYLIST_H
#define _MYLIST_H

typedef struct DataType {
    int location;
    int password;
}DataType;

typedef struct ListNode {
    DataType data;
    struct ListNode *next;
}ListNode;

typedef struct LinkList {
    ListNode *head;
    int length;
}LinkList;

void Print(DataType e);
LinkList* CreateList();
ListNode* GetHead(LinkList *l);
int GetLength(LinkList *l);
void Append(LinkList *l,DataType e);
int InsertNext(LinkList *l,ListNode *elem,DataType e);
DataType Remove(LinkList *l,ListNode *elem);
ListNode* GetNext(LinkList *l,ListNode *elem);
void Traverse(LinkList *l);

#endif //_MYLIST_H
