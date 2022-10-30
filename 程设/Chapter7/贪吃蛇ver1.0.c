#include<stdio.h>
#include<windows.h>
#include<time.h>
#include<stdlib.h>

#define SNAKE "■"
#define WALL "■"
#define SCORETABLE "■"
#define FOOD "●"
#define WINDOW "※"
#define WELCOME "■"
#define TRAP "□"



int score = 0, k = 1, snakeskin, snakelength = 0, time1 = 0, time2 = 0, trapflag;
int length,width;


enum SnakeDir{
	UP, DOWN, RIGHT, LEFT
};

enum SnakeStatus{
	Ready,WallKill,SelfKill,StoneKill
};

enum WindowFormat{
	END,PAUSE,READY
};

typedef struct node node;
struct node{
	node* prev;
	int x;
	int y;
	node* next;
};

typedef struct snake{
	node* snake;
	node* tail;
	node* food;
	node* trap;
	enum SnakeDir dir;
	enum SnakeStatus status;
	int staytime;
}snake;
//初始化长度为5的蛇
snake* CreateSnake(){
	node *head, *p, *p1;
	head = (node*)malloc(sizeof(node));
	head->prev = NULL;
	head->x = 20;
	head->y = 10;
	p = head;
	int i;
	for (i = 1; i < 5; i++){
		p1 = (node*)malloc(sizeof(node));
		p1->prev = p;
		p->next = p1;
		p1->x = p->x + 2;
		p1->y = p->y;
		p1->next = NULL;
		p = p1;
	}
	snake *p2;
	p2 = (snake*)malloc(sizeof(snake));
	p2->snake = head;
	p2->dir = RIGHT;
	p2->status = Ready;
	p2->tail = p1;
	snakelength = 5;
    return p2;
}

void setpos(int x, int y){
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

void Color(short x){
	if (x >= 0 && x <= 15)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
	else
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
}

void CreateFood(snake* p2){
	int flag, seed;
	node *p, *p1;
	seed = (unsigned)time(NULL);
	p = (node*)malloc(sizeof(node));
	p2->food = (node*)malloc(sizeof(node));
	p1 = p2->snake;
	flag = 1;
	while (flag||p->y==5||p->y==5 + length||p->x==10||p->x==10 + width){
		srand(seed);
		while (1){
			p->x = rand() % width + 10;
			if (p->x % 2 == 0)//保证蛇可以吃到食物
				break;
		}
		p->y = rand() % length + 5;
		while (p1 != NULL){
			if (p1->x != p->x&&p1->y != p->y){
				p1= p1->next;
			}
			else
				break;
		}
		if (p1 == NULL){
			flag = 0;
			seed = (unsigned)time(NULL);
		}
		else{
			seed = (unsigned)time(NULL)+10;
		}
	}
	p2->food->x = p->x;
	p2->food->y = p->y;
}


void CreateTrap(snake* p2){
	int flag, seed;
	node *p, *p1;
	seed = (unsigned)time(NULL);// + 10000;
	p = (node*)malloc(sizeof(node));
	p2->trap = (node*)malloc(sizeof(node));
	p1 = p2->snake;
	flag = 1;
	while (flag || p->y == 5 || p->y == 5 + length || p->x == 10 || p->x == 10 + width){
		srand(seed);
		while (1){
			p->x = rand() % width + 10;
			if (p->x % 2 == 0)
				break;
		}
		p->y = rand() % length + 5;
		while (p1 != NULL){
			if (p1->x != p->x&&p1->y != p->y){
				p1 = p1->next;
			}
			else break;
		}
		if (p1 == NULL){
			flag = 0;
			seed = (unsigned)time(NULL) + 10000;
		}
		else{
			seed = (unsigned)time(NULL) + 100000;
		}
		if (p->x == p2->food->x&&p->y == p2->food->y)	flag = 1;//和食物重合时重新生成
	}
	p2->trap->x = p->x;
	p2->trap->y = p->y;
}

void PrintSnake(snake* p2){
	node* p = NULL;
	int i;
	i = k;//保证蛇每次颜色不同
	p = p2->snake;
	while (p != NULL){
		setpos(p->x, p->y);
		Color(i);
		printf(SNAKE);
		if (i < 15) i++;
		else i = 1;
		p = p->next;
	}
	if (k < 15) k++;
	else k = 1;
	Color(16);
	setpos(0, 38);
}

void PrintFood(snake* p2){
	setpos(p2->food->x, p2->food->y);
	Color(10);
	printf(FOOD);
	Color(16);
}


void PrintTrap(snake* p2){
	setpos(p2->trap->x, p2->trap->y);
	Color(15);
	printf(TRAP);
	Color(16);
}

void PrintMap(){
	int i;
	Color(6);
	for (i = 10; i <= 10 + width; i+=2)
	{
		setpos(i, 5);
		printf(WALL);
		setpos(i, 5 + length);
		printf(WALL);
	}
	for (i = 6; i <= 6 + length - 1; i++){
		setpos(10, i);
		printf(WALL);
		setpos(10 + width, i);
		printf(WALL);
	}
	Color(16);
}

void PrintWelcome(){
	Color(10);
	int i;
	for (i = 10; i <= 110; i += 2){
		setpos(i, 5);
		printf(WELCOME);
		setpos(i, 37);
		printf(WELCOME);
	}
	for (i = 6; i <= 36; i++){
		setpos(10, i);
		printf(WELCOME);
		setpos(110, i);
		printf(WELCOME);
	}
	Color(16);
}

void PrintWindows(int color, int mode){
	Color(color);
	int i;
	switch (mode){
	case END:
		for (i = width / 2 - 3; i <= 23 + width / 2; i += 2){
			setpos(i, 1 + length / 2);
			printf(WINDOW);
			setpos(i, 9 + length / 2);
			printf(WINDOW);
		}
		for (i = 1 + length / 2; i <= 9 + length / 2; i++){
			setpos(width / 2 - 3, i);
			printf(WINDOW);
			setpos(width / 2 + 23, i);
			printf(WINDOW);
		}
		break;
	case PAUSE:
    for (i = width / 2 - 3; i <= 23 + width / 2; i += 2){
      setpos(i, 1 + length / 2);
      printf(WINDOW);
      setpos(i, 9 + length / 2);
      printf(WINDOW);
    }
    for (i = 1 + length / 2; i <= 9 + length / 2; i++){
      setpos(width / 2 - 3, i);
      printf(WINDOW);
      setpos(width / 2 + 23, i);
      printf(WINDOW);
    }
    break;
	case READY:
    for (i = width / 2 - 3; i <= 23 + width / 2; i += 2){
      setpos(i, 1 + length / 2);
      printf(WINDOW);
      setpos(i, 9 + length / 2);
      printf(WINDOW);
    }
    for (i = 1 + length / 2; i <= 9 + length / 2; i++){
      setpos(width / 2 - 3, i);
      printf(WINDOW);
      setpos(width / 2 + 23, i);
      printf(WINDOW);
    }
    break;
	}
	Color(16);
}

int hasfood(snake* p2, node* next){
	if (next->x == p2->food->x&&next->y == p2->food->y)
		return 1;
	else
		return 0;
}

int hastrap(snake* p2, node* next){
	if (p2->trap->x == next->x&&p2->trap->y == next->y)
		return 1;
	else
		return 0;
}

void nofood(snake* p2, node* next){
	node *p;
	next->next = p2->snake;
	p2->snake->prev = next;
	p2->snake = next;
	p = p2->tail;
	p2->tail = p2->tail->prev;
	setpos(p->x, p->y);
	printf(" ");
	if (p2->tail != p2->snake)
		p->prev->next = NULL;
	else
		p2->tail->next = NULL;
	free(p);
}

void eatfood(snake* p2, node* next){
	next->next = p2->snake;
	p2->snake->prev = next;
	p2->snake = next;
	p2->snake->prev = NULL;
	CreateFood(p2);
	PrintFood(p2);
	snakelength++;
}

void SnakeDirChange(snake* p2){
	node* next;
	next = (node*)malloc(sizeof(node));
	next->prev = NULL;
	next->next = NULL;
	next->x = p2->snake->x;
	next->y = p2->snake->y;
	switch (p2->dir){
	case UP:
		next->y -= 1;
		break;
	case DOWN:
		next->y += 1;
		break;
	case LEFT:
		next->x -= 2;
		break;
	case RIGHT:
		next->x += 2;
		break;
	}
	if (hasfood(p2, next)){
		score += 1;
		setpos(94, 13);
		Color(14);
		printf("%d", score);
		Color(16);
		eatfood(p2, next);
	}else if(hastrap(p2,next)){
    trapflag = 1;
  }else nofood(p2, next);
}

int killbywall(snake* p2){
	if (p2->snake->y == 5 || p2->snake->y == 5 + length || p2->snake->x == 10 || p2->snake->x == 10 + width)
		return 1;
	else
		return 0;
}


int killbytrap(snake* p2){
	if (trapflag)
		return 1;
	else
		return 0;
}

int killbyself(snake* p2){
  node *p,*p1;
  p1 = p = p2->snake;
  p = p->next;
  while(p->next != NULL){
    if(p1->x == p->x && p1->y == p->y) return 1;
    p = p->next;
  }
  return 0;
}

void GameOver(snake* p2){
	if(killbywall(p2)){
		PrintWindows(12, END);
		p2->status = WallKill;
		Color(12);
		setpos(width / 2 - 3 + 10, 1 + length / 2 + 2);
		printf("游戏结束！");
		setpos(width / 2 - 3 + 7, 1 + length / 2 + 4);
		printf("死因：撞墙而死！");
		setpos(width / 2 - 3 + 4, 1 + length / 2 + 6);
		printf("按F1重新开始，ESC退出");
		Color(16);
	}
	if(killbytrap(p2)){
		PrintWindows(12, END);
		p2->status = StoneKill;
		Color(12);
		setpos(width / 2 - 3 + 10, 1 + length / 2 + 2);
		printf("游戏结束！");
		setpos(width / 2 - 3 + 7, 1 + length / 2 + 4);
		printf("死因：掉进陷阱！");
		setpos(width / 2 - 3 + 4, 1 + length / 2 + 6);
		printf("按F1重新开始，ESC退出");
		Color(16);
	}
  if(killbyself(p2)){
    PrintWindows(12, END);
		p2->status = SelfKill;
		Color(12);
		setpos(width / 2 - 3 + 10, 1 + length / 2 + 2);
		printf("游戏结束！");
		setpos(width / 2 - 3 + 7, 1 + length / 2 + 4);
		printf("死因：咬到自己！");
		setpos(width / 2 - 3 + 4, 1 + length / 2 + 6);
		printf("按F1重新开始，ESC退出");
		Color(16);
  }
}

void PrintTips(){
	setpos(88, 17);
	printf("操作指南：");
	setpos(92, 19);
	printf("ESC--暂停");
	setpos(92, 21);
	printf("↑--向上称动");
	setpos(92, 23);
	printf("↓--向下移动");
	setpos(92, 25);
	printf("←--向左移动");
	setpos(92, 27);
	printf("→--向右移动");
  Color(10);
  setpos(92,29);
  printf(FOOD);
	Color(11);
	printf(" --食物");
  Color(10);
  setpos(92,31);
  Color(15);
	printf(TRAP);
	Color(11);
	printf(" --陷阱");
}

void PrintScoreTable(){
	Color(11);
	int i;
	for (i = 80; i <= 110; i += 2){
		setpos(i, 5);
		printf(SCORETABLE);
		setpos(i, 37);
		printf(SCORETABLE);
	}
	for (i = 6; i <= 36; i++){
		setpos(80, i);
		printf(SCORETABLE);
		setpos(110, i);
		printf(SCORETABLE);
	}
	setpos(88, 12);
	Color(11);
	printf("得分：");
	setpos(94, 13);
	Color(14);
	printf("%d", score);
	Color(11);
	PrintTips();
	Color(16);
}


void SnakeRun(snake* p2){
	while (p2->status == Ready){
		if (GetAsyncKeyState(VK_UP) && p2->dir != DOWN)
			p2->dir = UP;
		if (GetAsyncKeyState(VK_DOWN) && p2->dir != UP)
			p2->dir = DOWN;
		if (GetAsyncKeyState(VK_LEFT) && p2->dir != RIGHT)
			p2->dir = LEFT;
		if (GetAsyncKeyState(VK_RIGHT) && p2->dir != LEFT)
			p2->dir = RIGHT;
		if (GetAsyncKeyState(VK_ESCAPE)){
			PrintWindows(12, PAUSE);
			Color(11);
			setpos(width / 2 - 3 + 10, 1 + length / 2 + 3);
			printf("游戏暂停！");
			setpos(width / 2 - 3 + 6, 1 + length / 2 + 5);
			printf("按回车键继续游戏");
			Color(16);
			setpos(0, 38);
			getchar();
			system("cls");
			PrintMap();
			PrintScoreTable();
			PrintFood(p2);
			PrintTrap(p2);
		}
		SnakeDirChange(p2);
		PrintSnake(p2);
		GameOver(p2);
		Sleep(p2->staytime);
		time1++;
		time2++;
		if (time1 >= 20){
			PrintTrap(p2);
			time1 = 0;
		}
		if (time2 >= 80){
			PrintTrap(p2);
			time2 = 0;
		}
		setpos(0, 50);
	}
}


void Welcome(){
	PrintWelcome();
	Color(3);
	setpos(47, 10);
	printf("欢迎来到贪吃蛇游戏");
  setpos(47,20);
  printf("设置地图大小");
  setpos(46, 30);
	printf("按回车确认并进入游戏");
	Color(14);
	setpos(88, 35);
	printf("Created by Sherlock.X");
  setpos(47,21);
  Color(13);
  printf("长度20~32 宽度40~64");
  setpos(48,25);
  scanf("%d %d",&length,&width);
	Color(16);
	setpos(0, 38);
}

void ReadyWindow(){
	PrintWindows(12, READY);
	Color(11);
	setpos(width / 2 - 3 + 10, 1 + length / 2 + 3);
	printf("准备游戏！");
	setpos(width / 2 - 3 + 6, 1 + length / 2 + 5);
	printf("按回车键开始游戏");
	Color(16);
}

int main(void){
	system("chcp 65001");
	system("mode con cols=130 lines=55");
	snake *p2;
	snakeskin = 1;
	Welcome();
  getchar();
	system("cls");
	PrintMap();
	PrintScoreTable();
	ReadyWindow();
  getchar();
  l:system("cls");
    PrintMap();
	PrintScoreTable();
	p2 = CreateSnake();
	p2->staytime = 100;
	CreateFood(p2);
	CreateTrap(p2);
	PrintSnake(p2);
	PrintFood(p2);;
	PrintTrap(p2);
	SnakeDirChange(p2);
	SnakeRun(p2);
	system("pause");
	while (1){       //防止因误按造成的游戏退出
		if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState(VK_LEFT)){
			setpos(0, 50);
			system("pause");
		}
		if (GetAsyncKeyState(VK_F1)){
			score = 0;
			goto l;
		}
		if (GetAsyncKeyState(VK_ESCAPE))
			break;
	}
}
