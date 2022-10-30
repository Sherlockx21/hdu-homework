#include<stdlib.h>
#include<assert.h>
#include "List.h"

//创建线性表 
struct List Create(){
  struct List list;
  list.pHead=list.pTail=(struct Node*)malloc (sizeof(struct Node));
  if (list.pHead!=NULL){
    list.pHead->next=NULL;
  }
  return list;
}

//清空表 
void Clear(struct List *pList){
  struct Node *p=pList->pHead->next;
  while(p!=NULL){
    struct Node *q=p;
    p=p->next;
    free(q);
  }
  pList->pHead->next=NULL;
  pList->pTail=pList->pHead;
}

//销毁表
void Destroy(struct List *pList){
	Clear(pList);
	free(pList->pHead);
	pList->pHead=pList->pTail=NULL;
} 

//复制表
struct List Copy(struct List srcList){
	struct List destList;
	destList=Create();
	if(destList.pHead==NULL){
		return destList;
	}
	struct Node *p;
	p=srcList.pHead->next;
	while(p!=NULL){
		struct Node *s;
		s=(struct Node*)malloc(sizeof(struct Node));
		if(s==NULL){
			Destroy(&destList);
			return destList;
		}
		s->data=p->data;
		destList.pTail->next=s;
		s->next=NULL;
		destList.pTail=s;
		p=p->next;
	}
	return destList;
} 

//判空
int IsEmpty(struct List list){
	return (list.pHead->next==NULL);
}

//求长度
int Length(struct List list){
	int iCount=0;
	struct Node *p=list.pHead->next;
	while(p!=NULL){
		iCount++;
		p=p->next;
	}
	return iCount;
} 

//起始位置
Position BeginPosition(struct List list){
	return list.pHead;
} 

//结束位置
Position EndPosition(struct List list){
	return list.pTail; 
} 

//迭代下一位置
Position NextPosition(struct List list,Position pos){
	return pos->next;
} 

//获取元素位置
Position LocatePosition(struct List list,int i){
	Position pos=list.pHead;
	while(--i>0&&pos->next!=NULL){
		pos=pos->next;
	}
	return pos;
} 

//定位元素位置
Position LocateElem(struct List list,DataElem e){
	Position pos=list.pHead;
	while(pos->next!=NULL&&pos->next->data!=e){
		pos=pos->next;
	}
	return pos;
} 

//获取元素
DataElem GetElem(struct List list,Position pos){
	assert(pos!=EndPosition(list));
	return pos->next->data;
} 

//设置元素
void SetElem(struct List list,Position pos,DataElem e){
	assert(pos!=EndPosition(list));
	pos->next->data=e;
} 

//插入元素
int InsertBdfore(struct List *pList,Position pos,DataElem e){
	struct Node *s=(struct Node*)malloc(sizeof(struct Node));
	if(s==NULL){
		return 0;
	}
	s->data=e;
	s->next=pos->next;
	pos->next=s;
	if(pList->pTail==pos){
		pList->pTail=s;
	}
	return 0;
} 

//删除元素
void Delete(struct List *pList,Position pos){
	assert(pos!=EndPosition(*pList));
	struct Node*s=pos->next;
	pos->next=s->next;
	free(s);
	if(pList->pTail==s){
		pList->pTail=pos;
	} 
} 
