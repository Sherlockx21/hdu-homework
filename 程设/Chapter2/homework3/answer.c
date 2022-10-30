//                        .::::.
//                      .::::::::.
//                    :::::::::::
//                 ..:::::::::::'
//              '::::::::::::'
//                .::::::::::
//           '::::::::::::::..
//                ..::::::::::::.
//              ``::::::::::::::::
//               ::::``:::::::::'        .:::.
//              ::::'   ':::::'       .::::::::.
//            .::::'      ::::     .:::::::'::::.
//           .:::'       :::::  .:::::::::' ':::::.
//          .::'        :::::.:::::::::'      ':::::.
//         .::'         ::::::::::::::'         ``::::.
//     ...:::           ::::::::::::'              ``::.
//    ```` ':.          ':::::::::'                  ::::..
//                       '.:::::'                    ':'````..
//                    美女保佑 永无BUG
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 10

int maze[N][N] = {
{ 2, 0, 2, 2, 2, 2, 2, 2, 2, 2},
{ 2, 0, 2, 2, 0, 2, 2, 0, 0, 2},
{ 2, 0, 0, 0, 0, 2, 2, 2, 0, 2},
{ 2, 2, 0, 2, 0, 2, 0, 0, 0, 2},
{ 2, 0, 0, 0, 0, 0, 0, 2, 0, 2},
{ 2, 0, 2, 2, 2, 2, 0, 2, 0, 2},
{ 2, 0, 2, 0, 0, 0, 0, 2, 2, 2},
{ 2, 0, 2, 2, 2, 0, 0, 0, 0, 2},
{ 0, 0, 0, 0, 0, 0, 2, 0, 2, 2},
{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
};


int startI=0,startJ=0,endI=0,endJ=0;
int success = 0;

//寻找出入口
void port(int maze[N][N]){
  for(int i = 0;i < N;i++){
		for(int j = 0;j <N;j++){
			if((i == 0 || i == N-1 || j == 0 || j == N-1) && maze[i][j] == 0){
				if(startI != 0 || startJ != 0){
					endI = i;
					endJ = j;
				}else{
					startI = i;
					startJ = j;
				}
			}
		}
	}
	return;
}

#define MAXSIZE 1000

typedef struct node{
  int x;
  int y;
}Node;


typedef struct _CNode{

    Node elem[MAXSIZE];
    int front;        //下标可取,指向队头元素
    int rear;            //下标不可取,指向元素应放入的位置
}CNode, *CQueue;
//初始化队列
void InitCQueue(CQueue pQueue){
    if (NULL == pQueue)
        return;
    pQueue->front = 0;
    pQueue->rear = 0;
}

//队列为空则返回true
bool IsEmpty(CQueue pQueue){
    return pQueue->rear == pQueue->front;
}


//队列满则返回false
bool IsFull(CQueue pQueue){
    return (pQueue->rear + 1)%MAXSIZE == pQueue->front;
}

//入队，从队尾(rear)入
void Push(CQueue pQueue,Node val){
    //入队之前应该先判断队列是否已经满了
    if (IsFull(pQueue)){
        return;
    }
    pQueue->elem[pQueue->rear]= val;               //将元素放入队列，这里也说明front是可取的
    pQueue->rear = (pQueue->rear+ 1) % MAXSIZE;    //更新队尾位置
}

//出队，从队首(front)出
Node Pop(CQueue pQueue){
    //出队之前应该先判断队列是否是空的
    Node rtval = {-1,-1};
    if (IsEmpty(pQueue)){
        return rtval;
    }
    rtval = pQueue->elem[pQueue->front];           //取出队头元素
    pQueue->front = (pQueue->front+ 1) % MAXSIZE;  //更新队头位置

    return rtval;
}

//获取队列长度
int GetCQueueLen(CQueue pQueue){
    return ((pQueue->rear - pQueue->rear + MAXSIZE) % MAXSIZE);
}

//输出队列所有元素
void ShowQueue(CQueue pQueue){
    int front = pQueue->front;
    int rear = pQueue->rear;
    while (front != rear){
        printf("{%d.%d}", pQueue->elem[front].x,pQueue->elem[front].y);
        front++;
    }
    printf("\n");
    return;
}


//获取队首元素
Node GetFront(CQueue pQueue){
  Node rtval = {-1,-1};
    if (!IsEmpty(pQueue)){
        rtval = pQueue->elem[pQueue->front];   //将队头元素通过*rtval返回
        return rtval;
    }
    return rtval;
}

int dirx[]={0,1,0,-1};
int diry[]={1,0,-1,0};
int dis1[N][N];
int dis2[N][N];
int minrode=0;
int fx,fy;
CQueue que;

void BFS(int dis[][N],int sx,int sy){

	for(int i = 0;i < N;i++){//初始化记录层数的dis数组
		for(int j = 0;j < N;j++){
			dis[i][j] = -1;
    }
  }
	while(!IsEmpty(que)) Pop(que);//初始化队列
  Node cur={sx,sy};
  Push(que,cur);//放入起点
	dis[sx][sy] = 0;//(sx,sy)为起点
	while(!IsEmpty(que)){
		cur = GetFront(que);//当前状态
		Pop(que);
		for(int k = 0;k < 4;k++){
			Node nxt;
			nxt.x = cur.x + dirx[k];
			nxt.y = cur.y + diry[k];
			if(maze[nxt.x][nxt.y] == 2){//墙壁无法通行
				continue;
			}
			if(nxt.x >= 0 && nxt.x < N && nxt.y >= 0 && nxt.y<N && dis[nxt.x][nxt.y] == -1){
				if(nxt.x == endI && nxt.y == endJ){
					fx = nxt.x;fy = nxt.y;
					minrode = dis[cur.x][cur.y]+1;
          dis[fx][fy] = minrode;
					return ;
				}else{
				 Push(que,nxt);
				  dis[nxt.x][nxt.y] = dis[cur.x][cur.y]+1;//不断的记录层数
			  }
			}
		}
	}
}


void Print(int maze[][N]){//对起点进行上下左右找，满足的mark=true的进行输出
  for(int i = 0;i < N;i++){
    for(int j = 0;j < N;j++){
      if(maze[i][j] == 2) printf("#");
      if(maze[i][j] == 0) printf(" ");
      if(maze[i][j] == 1) printf("o");
    }
    printf("\n");
  }
}


int main(){
  printf("Maze:\n");
  Print(maze);
  printf("\n");
	BFS(dis1,startI,startJ);//正向遍历
	BFS(dis2,endI,endJ);//逆向遍历



	int total = minrode;

	for(int i = 0;i < N;i++){
		for(int j = 0;j < N;j++){
			if(dis1[i][j] + dis2[i][j] == total){
			//	mark[i][j] = true;//如果符合的话就是最短路，mark数组该点标记为true
        maze[i][j] = 1;
      }
		}
	}

	Print(maze);//调用print函数进行打印mark上面为true的点
	return 0;
}
