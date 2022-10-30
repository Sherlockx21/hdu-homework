#ifndef __LIST_H_INCLUDED_
#define __LIST_H_INCLUDED_
typedef char DataElem;

//����ڵ����� 
struct Node{
  DataElem data;
  struct Node *next;
};

//���Ա����� 
struct List{
  struct Node *pHead;
  struct Node *pTail;
};

typedef struct Node*   Position;

//�������Ա� 
struct List Create();
//��ձ� 
void Clear(struct List *pList);
//���ٱ�
void Destroy(struct List *pList);
//���Ʊ�
struct List Copy(struct List srcList);
//�п�
int IsEmpty(struct List list);
//�󳤶�
int Length(struct List list);
//��ʼλ��
Position BeginPosition(struct List list);
//����λ��
Position EndPosition(struct List list);
//������һλ��
Position NextPosition(struct List list,Position pos);
//��ȡԪ��λ��
Position LocatePosition(struct List list,int i);
//��λԪ��λ��
Position LocateElem(struct List list,DataElem e);
//��ȡԪ��
DataElem GetElem(struct List list,Position pos);
//����Ԫ��
void SetElem(struct List list,Position pos,DataElem e);
//����Ԫ��
int InsertBdfore(struct List *plist,Position pos,DataElem e);
//ɾ��Ԫ��
void Delete(struct List*pList,Position pos);

#endif// __LIST_H_INCLUDED_
