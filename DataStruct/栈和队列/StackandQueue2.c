#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DataType char
#define maxn 100010

struct Stack {
    DataType data[maxn];
    int top;
};

void StackClear(struct Stack* stk) {
    stk->top = 0;
}
void StackPushStack(struct Stack *stk, DataType dt) {
    stk->data[ stk->top++ ] = dt;
}
void StackPopStack(struct Stack* stk) {
    --stk->top;
}
DataType StackGetTop(struct Stack* stk) {
    return stk->data[ stk->top - 1 ];
}
int StackGetSize(struct Stack* stk) {
    return stk->top;
}
int StackIsEmpty(struct Stack* stk) {
    return !StackGetSize(stk);
}

struct Queue {
    DataType data[maxn<<1];
    int head, tail;
};

void QueueClear(struct Queue* que) {
    que->head = maxn;
    que->tail = que->head - 1;
}

void QueueEnqueueFront(struct Queue *que, DataType dt) {
    que->data[ --que->head ] = dt;
}
void QueueEnqueueRear(struct Queue *que, DataType dt) {
    que->data[ ++que->tail ] = dt;
}
void QueueDequeueFront(struct Queue* que) {
    ++que->head;
}
void QueueDequeueRear(struct Queue* que) {
    --que->tail;
}

DataType QueueGetFront(struct Queue* que) {
    return que->data[ que->head ];
}
DataType QueueGetRear(struct Queue* que) {
    return que->data[ que->tail ];
}
int QueueGetSize(struct Queue* que) {
    return que->tail - que->head + 1;
}
int QueueIsEmpty(struct Queue* que) {
    return !QueueGetSize(que);
}



int main(){

  int len,t = 0;
  struct Stack *s = (struct Stack*)malloc(sizeof(struct Stack));
  struct Queue *q = (struct Queue*)malloc(sizeof(struct Queue));
  char str[100005];
  while(scanf("%s",str)){
    len = strlen(str);
    for(int i = 0;i < len;i++){
      if(str[i] == '('){
        StackPushStack(s,'(');
        QueueEnqueueRear(q,'(');
      }else if(str[i] == ')'){
        if(!StackIsEmpty(s) && StackGetTop(s) == '('){
          QueueEnqueueRear(q,')');
          StackPopStack(s);
        }else{
          QueueEnqueueFront(q,'(');
          QueueEnqueueRear(q,')');
          t++;
        }
      }
    //  printf("%c %c\n", QueueGetFront(q),QueueGetRear(q));
    }
    while(!StackIsEmpty(s)){
      QueueEnqueueRear(q,')');
      StackPopStack(s);
      t++;
    }
    if(t == 0){
      printf("Match\n");
      while(!QueueIsEmpty(q)) QueueClear(q);
      while(!StackIsEmpty(s)) StackClear(s);
    }else{
      printf("%d\n",t);
      while(!QueueIsEmpty(q)){
        printf("%c",QueueGetFront(q));
        QueueDequeueFront(q);
      }
    }
    printf("\n");
    t = 0;
  }
  return 0;
}
