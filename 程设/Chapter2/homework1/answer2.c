#include <stdio.h>
#include <stdlib.h>

struct point{
	int x;
	int y;
};
typedef struct point Point;

struct node{
	Point data;
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
void Push(Stack *s, Point e){
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
Point GetTop(Stack *s){
	if(s->top == NULL){
		Point tmp={-1,-1};
		return tmp;
  }
	return (s->top->data);
}

//元素出栈
Point Pop(Stack *s){
	Point e;
	if(s->top == NULL){
    Point tmp={-1,-1};
		return tmp;
	}
	Node *p = s->top;
	e = p->data;
	s->top = p->next;
	free(p);
	s->count--;
  return e;
}

#define MAX 25
int a[MAX][MAX];//地图
int book[MAX][MAX]={0};
int done[MAX][MAX]={2};
int next[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
int n, m;

Point cur;
Stack *part;

void dfs(int x,int y, int num){
  cur.x = x;
	cur.y = y;
	book[x][y] = a[x][y];
	Push(part,cur);
	while(!EmptyStack(part)){
		cur = GetTop(part);
   while(done[cur.x][cur.y]){
		 if(a[cur.x][cur.y + 1] != a[cur.x][cur.y] || cur.y == n - 1) done[cur.x][cur.y]--;
		 if(a[cur.x + 1][cur.y] != a[cur.x][cur.y] || cur.x == m - 1) done[cur.x][cur.y]--;
		 if(a[cur.x][cur.y - 1] != a[cur.x][cur.y] || cur.y == 0) done[cur.x][cur.y]--;
		 if(a[cur.x - 1][cur.y] != a[cur.x][cur.y] || cur.x == 0) done[cur.x][cur.y]--;
		while(book[cur.x ][cur.y + 1] == 0 && a[cur.x][cur.y + 1] == a[cur.x][cur.y] && cur.y != n - 1){
			Push(part,cur);
			done[cur.x][cur.y]--;
			cur.y++;
		}
		while(book[cur.x + 1][cur.y] == 0 && a[cur.x + 1][cur.y] == a[cur.x][cur.y] && cur.x != m - 1){
			Push(part,cur);
			done[cur.x][cur.y]--;
			cur.x++;
		}
		while(book[cur.x][cur.y - 1] == 0 && a[cur.x][cur.y - 1] == a[cur.x][cur.y] && cur.y != 0){
			Push(part,cur);
			done[cur.x][cur.y]--;
			cur.y--;
		}
		while(book[cur.x - 1][cur.y] == 0 && a[cur.x - 1][cur.y] == a[cur.x][cur.y] && cur.x != 0){
			Push(part,cur);
			done[cur.x][cur.y]--;
			cur.x--;
		}
  }
	Pop(part);
 }
}

int main(){
    int i, j;
    int count=0;
    scanf("%d %d\n", &m, &n);
    for (i = 0; i < m; i++){
        for (j = 0; j < n; j++){
            scanf("%d",&a[i][j]);
        }
    }

    for (i = 0; i < m; i++){
        for (j = 0; j < n; j++){
            if (book[i][j] == 0){
                book[i][j] = a[i][j];
                dfs(i,j,a[i][j]);
                count++;
            }
        }
    }/*
		for(int i = 0;i < m;i++){
			for(int j = 0;j < n;j++){
				printf("%d ",book[i][j]);
				if(j == n-1) printf("\n");
			}
		}*/
		printf("\n");
		printf("%d", count);
    return 0;
}
