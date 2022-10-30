#ifndef __LIST_H_INCLUDED_
#define __LIST_H_INCLUDED_
typedef char DataElem;

//链表节点类型 
struct Node{
  DataElem data;
  struct Node *next;
};

//线性表类型 
struct List{
  struct Node *pHead;
  struct Node *pTail;
};

typedef struct Node*   Position;

//创建线性表 
struct List Create();
//清空表 
void Clear(struct List *pList);
//销毁表
void Destroy(struct List *pList);
//复制表
struct List Copy(struct List srcList);
//判空
int IsEmpty(struct List list);
//求长度
int Length(struct List list);
//起始位置
Position BeginPosition(struct List list);
//结束位置
Position EndPosition(struct List list);
//迭代下一位置
Position NextPosition(struct List list,Position pos);
//获取元素位置
Position LocatePosition(struct List list,int i);
//定位元素位置
Position LocateElem(struct List list,DataElem e);
//获取元素
DataElem GetElem(struct List list,Position pos);
//设置元素
void SetElem(struct List list,Position pos,DataElem e);
//插入元素
int InsertBdfore(struct List *plist,Position pos,DataElem e);
//删除元素
void Delete(struct List*pList,Position pos);

#endif// __LIST_H_INCLUDED_
