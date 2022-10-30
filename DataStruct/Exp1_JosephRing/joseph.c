//
// Created by hang on 2022/10/5.
//
#include "mylist.h"

void Joseph(LinkList *l,int n,int m){
    ListNode *s = l->head;
    ListNode *nxt;
    while(n){
        m = (m - 1) % n + 1;
        for(int i = 1;i < m;i++){
            s = s->next;
        }
        Print(s->data);
        m = s->data.password;
        nxt = s->next;
        Remove(l,s);
        s = nxt;
        n--;
    }
}
