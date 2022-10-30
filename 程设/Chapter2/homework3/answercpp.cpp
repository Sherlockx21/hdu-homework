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
#include<bits/stdc++.h>
using namespace std;
const int N = 10;//地图最大宽度
struct node{
	int x,y;
};
queue<node>  que;
int minrode = 0;
int fx,fy;//记录终点的坐标值
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
int startx = 0,starty = 1;
int endx = 8,endy = 0;
int dx[] = {0,1,0,-1};
int dy[] = {1,0,-1,0};
int dis1[N][N];//正向记录层数的数组
int dis2[N][N];//逆向记录层数的数组
bool mark[N][N];//用来标记是不是在最短路上

void BFS(int dis[][N],int sx,int sy){

	for(int i = 0;i < N;i++){//初始化记录层数的dis数组
		for(int j = 0;j < N;j++){
			dis[i][j] = -1;
    }
  }
	while(!que.empty()) que.pop();//初始化队列

	que.push((node){sx,sy});//放入起点
	dis[sx][sy] = 0;//(sx,sy)为起点
	while(!que.empty()){
		node cur = que.front();//当前状态
		que.pop();
		for(int k = 0;k < 4;k++){
			node nxt;
			nxt.x = cur.x + dx[k];
			nxt.y = cur.y + dy[k];
			if(maze[nxt.x][nxt.y] == 2){//墙壁无法通行
				continue;
			}
			if(nxt.x >= 0 && nxt.x < N && nxt.y >= 0 && nxt.y<N && dis[nxt.x][nxt.y] == -1){
				if(nxt.x == endx && nxt.y == endy){
					fx = nxt.x;fy = nxt.y;
					minrode = dis[cur.x][cur.y]+1;
          dis[fx][fy] = minrode;
					return ;
				}else{
				  que.push(nxt);
				  dis[nxt.x][nxt.y] = dis[cur.x][cur.y]+1;//不断的记录层数
			  }
			}
		}
	}
}

void Print(int maze[][N]){//对起点进行上下左右找，满足的mark=true的进行输出
  for(int i = 0;i < N;i++){
    for(int j = 0;j < N;j++){
      if(maze[i][j] == 2) cout<<"#";
      if(maze[i][j] == 0) cout<<" ";
      if(maze[i][j] == 1) cout<<"o";
    }
    cout<<endl;
  }
}


int main(){
  cout<<"Maze:"<<endl;
  Print(maze);
  cout<<endl;
	BFS(dis1,startx,starty);//正向遍历
	BFS(dis2,endx,endy);//逆向遍历

	memset(mark,0,sizeof(mark));//初始化最短路径记录数组

	int total = minrode;
	for(int i = 0;i < N;i++){
		for(int j = 0;j < N;j++){
			if(dis1[i][j] + dis2[i][j] == total){
				mark[i][j] = true;//如果符合的话就是最短路，mark数组该点标记为true
        maze[i][j] = 1;
      }
		}
	}

	Print(maze);//调用print函数进行打印mark上面为true的点
	return 0;
}
