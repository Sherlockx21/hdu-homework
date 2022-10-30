#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define maxn 100010


struct StackInt {
    int data[maxn];
    int top;
};

void StackIntClear(struct StackInt* stk) {
    stk->top = 0;
}
void StackIntPushStack(struct StackInt *stk, int dt) {
    stk->data[ stk->top++ ] = dt;
}
void StackIntPopStack(struct StackInt* stk) {
    --stk->top;
}
int StackIntGetTop(struct StackInt* stk) {
    return stk->data[ stk->top - 1 ];
}
int StackIntGetSize(struct StackInt* stk) {
    return stk->top;
}
int StackIntIsEmpty(struct StackInt* stk) {
    return !StackIntGetSize(stk);
}

struct StackChar {
    char data[maxn];
    int top;
};

void StackCharClear(struct StackChar* stk) {
    stk->top = 0;
}
void StackCharPushStack(struct StackChar *stk, char dt) {
    stk->data[ stk->top++ ] = dt;
}
void StackCharPopStack(struct StackChar* stk) {
    --stk->top;
}
char StackCharGetTop(struct StackChar* stk) {
    return stk->data[ stk->top - 1 ];
}
int StackCharGetSize(struct StackChar* stk) {
    return stk->top;
}
int StackCharIsEmpty(struct StackChar* stk) {
    return !StackCharGetSize(stk);
}

int main(){
    int N,num,sum;
    int cal1,cal2;
    struct StackInt *S1 = (struct StackInt*) malloc (sizeof(struct StackInt));
    struct StackChar *S2 = (struct StackChar*) malloc (sizeof(struct StackChar));
    char op;
    scanf("%d",&N);
    for(int i = 0;i < N;i++){
        scanf("%d",&num);
        StackIntPushStack(S1,num);
    }
    for(int i = 0;i < N;i++){
        scanf("%c",&op);
        if(op == ' ') scanf("%c",&op);
        StackCharPushStack(S2,op);
        //printf("%c ",StackCharGetTop(S2));
    }
    while(StackIntGetSize(S1) != 1){
        cal1 = StackIntGetTop(S1);
        StackIntPopStack(S1);
        cal2 = StackIntGetTop(S1);
        StackIntPopStack(S1);
        op = StackCharGetTop(S2);
        StackCharPopStack(S2);
        // printf("\n %d %c %d = ",cal2,op,cal1);
        switch (op) {
          case '+':{
            sum = cal2 + cal1;
            StackIntPushStack(S1,sum);
            break;
          }
          case '-':{
            sum = cal2 - cal1;
            StackIntPushStack(S1,sum);
            break;
          }
          case '*':{
            sum = cal2 * cal1;
            StackIntPushStack(S1,sum);
            break;
          }
          case '/':{
            if(cal1 == 0){
                printf("ERROR: %d/%d\n",cal2,cal1);
                return 0;
            }
            sum = cal2 / cal1;
            StackIntPushStack(S1,sum);
            break;
          }
        }
        // printf("%d ",StackIntGetTop(S1));
    }
    printf("%d\n",StackIntGetTop(S1));
    return 0;
}
