#include <stdio.h>
#include <stdlib.h>

struct node{
	int data;
	struct node *next;
};
typedef struct node Node;

struct stack{
	Node *top;
	int count;
};
typedef struct stack Stack;

int InitStack(Stack *l){
	l->top = NULL;
	l->count = 0;
	return 1;
}

//判断栈是否为空
int EmptyStack(Stack *s){
	return s->count == 0;
}

//压入元素
void Push(Stack *s, int e){
	Node *p = (Node *)malloc(sizeof(Node));
	if(p == NULL){
		return;
	}
	p->data = e;
	p->next = s->top;
	s->top = p;
	s->count++;
	return;
}

//返回顶端元素
int GetTop(Stack *s){
	if(s->top == NULL){
		return -1;
  }
	return (s->top->data);
}

//确定符号优先级
int Priority(char s){
	switch(s){
		case '(':
			return 3;
		case '*':
		case '/':
			return 2;
		case '+':
		case '-':
			return 1;
		default:
			return 0;
	}
}

//元素出栈
int Pop(Stack *s){
	int e;
	if(s->top == NULL){
		return -1;
	}
	Node *p = s->top;
	e = p->data;
	s->top = p->next;
	free(p);
	s->count--;
  return e;
}

int main(){
	Stack num, opt;//创建数字链表num，操作链表opt
	char str[100]={0};
	int i = 0, tmp = 0, j;

  if(InitStack(&num) != 1 || InitStack(&opt) != 1){
		exit(1);
	}

	scanf("%s",str);

	while(str[i] != '#' || EmptyStack(&opt) != 1){
		if(str[i] >= '0' && str[i] <= '9'){//读取数字
			tmp = tmp * 10 + str[i] - '0';
			i++;
			if(str[i] < '0' || str[i] > '9'){
				Push(&num,tmp);
				tmp = 0;
			}
		}else{//读取操作符
			if((EmptyStack(&opt) == 1) || (GetTop(&opt) == '(' && str[i] != ')') || Priority(str[i]) > Priority(GetTop(&opt))){//进栈不参与运算
				Push(&opt,str[i]);
				i++;
				continue;
			}
			if(GetTop(&opt) == '(' && str[i] == ')'){//出栈不参与运算
				Pop(&opt);
				i++;
				continue;
			}
			if((str[i] == '\0' && EmptyStack(&opt) != 1) || (str[i] == ')' && GetTop(&opt) != '(') || Priority(str[i]) <= Priority(GetTop(&opt))){//出栈并参与运算
				switch(Pop(&opt)){
					case '+':
						Push(&num, Pop(&num) + Pop(&num));
						break;
					case '-':
						j = Pop(&num);
						Push(&num, Pop(&num) - j);
						break;
					case '*':
						Push(&num, Pop(&num) * Pop(&num));
						break;
					case '/':
						j = Pop(&num);
						Push(&num, Pop(&num) / j);
				}
				continue;
			}
		}
	}

	printf("%d",Pop(&num));
  printf("\n");
  return 0;
}
