#include <stdlib.h>
#include <stdio.h>
#include <string.h>
using namespace std;


struct clubmem{
    char name[16];  // 名字
    char phone[12]; // 电话
    struct clubmem* next;   // 下一个节点
};

// 输出所有会籍信息
void print(struct clubmem* head){
    struct clubmem* p = head;
    p=p->next;
    while(p != NULL){
        printf("%s %s\n", p->name, p->phone);
        p = p->next;
    }
}

//将*pnew的数据按其name的由小到大插入到**phead链表中
void insert(struct clubmem **phead, struct clubmem *pnew)
{
    struct clubmem *head;
    //head = (struct clubmem *)malloc(sizeof(struct clubmem));
    head = *phead;
    if(head == NULL)
    {
        head = pnew;
        *phead  = head;
    }
    else
    {
        if(strcmp(pnew -> name, head -> name) < 0)
        {
            pnew -> next = head;
            head = pnew;
            *phead = head;
        }
        else
        {
            struct clubmem *p,*pold;
            pold = head;
            p = head -> next;
            while(p != NULL)
            {
                if(strcmp(p -> name,pnew -> name) < 0)
                {
                    pold = p;
                    p = p -> next;
                }
                else
                    break;
            }

            pnew -> next = p;
            pold -> next = pnew;
        }
    }
}

struct clubmem* doregister(int n)
{
    struct clubmem *pnew;
    struct clubmem *group;
    group = (struct clubmem *)malloc(sizeof(struct clubmem)*n);
    int i;
    for(i = 0; i < n; i++)
    {
        pnew = (struct clubmem *)malloc(sizeof(struct clubmem));
        pnew -> next = NULL;
        scanf("%s %s\n",pnew -> name, pnew -> phone);
        insert(&group,pnew);
    }
    return group;
}

void delete_p(struct clubmem **phead, char name[])
{
    struct clubmem *head, *p,*pold;
    head = p = pold = *phead;
    if(strcmp(head -> name,name) == 0)
    {
        head -> next = head;
        free(p);
        *phead = head;
        p = head -> next;
    }
    else
    {
        while(p != NULL)
        {
            if(strcmp(p -> name,name) == 0)
            {
                pold -> next = p -> next;
                free(p);
                p = pold -> next;
            }
            else
            {
                pold = p;
                p = p -> next;
            }
        }
    }
}

struct clubmem* unregister(struct clubmem *group, char name[])
{

    delete_p(&group,name);
    return group;
}


#include<iostream>

int main()
{
    int n=0;
    struct clubmem* head;
    char name[16];
    //scanf("%d", &n);
    cin >> n;
    head=doregister(n);               // 注册n个会籍信息, 返回链表
    //gets(name);                        // 输入要注销会籍的名字
    cin >> name;
    head=unregister(head, name);    // 查找并注销会籍信息
    print(head);
}
