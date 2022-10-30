#include<stdio.h>
#include<malloc.h>

struct Node{
  int data;
  int times;
  struct Node* next;
};

//分配新节点
struct Node* newNode(){
  struct Node* p;
  p=(struct Node*)malloc(sizeof(struct Node));
  if(p==NULL){
    printf("Error: out of memory\n");
    exit(-1);
  }
  return p;
}

//插入元素
void insert(struct Node* la,int x){
  //查找插入位置
  struct Node* p =la;
    //申请节点
    struct Node* q=newNode();
    q->data=x;
    q->times=1;
  //链表不为空
  while(p->next){
    if(x==p->next->data){
      p->next->times++;
      return;
    }else{
      p=p->next;
    }
  }
  q->next=p->next;
  p->next=q;
  return;
}

//销毁链表
void destroy(struct Node* la){
  while(la){
    struct Node* q=la->next;
    free(la);
    la=q;
  }
  return;
}

int lenlist(struct Node* la){
  if(la==NULL){
    return 0;
  }
  struct Node *p = la;
	int len = 0;
	while(p != NULL)
	{
		len++;
		p = p->next;
	}
	return len;
}

//排序
void listsort(struct Node* la){
  int len = lenlist(la);
  	if (len == 0)
  		return;
  	struct Node* p = la;
  	int i, j, tmp;
  	for (i = 0; i < len - 1; i++)
  	{
  		p = la;
  		for (j = 0; j < len -i -1; j++)
  		{
  			if (p->times < p->next->times)
  			{
  				tmp = p->data;
  				p->data = p->next->data;
  				p->next->data = tmp;
          tmp = p->times;
          p->times = p->next->times;
          p->next->times = tmp;
  			}
  			p = p->next;
  		}
  	}
  return;
}

//打印
void print(struct Node* la){
  la=la->next;
  while(la){
    printf("%d:%d\n",la->data,la->times);
    la=la->next;
  }
  return;
}


int main(){
  //带头节点
  struct Node* la=newNode();
  la->next=NULL;
  int x;
  while(scanf("%d",&x)){
    if(x==0) break;
    insert(la,x);
    listsort(la);
  }
  print(la);
  destroy(la);
}
