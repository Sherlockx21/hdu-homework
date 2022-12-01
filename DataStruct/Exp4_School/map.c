//
// Created by hang on 2022/11/24.
//

#include "map.h"

int dist[M][M];  //距离
int path[M][M];  //路径

void Create_Map(map *g){
    int i, j, k, e;
    g->spotNum = 0;
    g->pathNum = 0;
    FILE *fp = fopen("map.txt", "r");
    if(fp){
        fscanf(fp, "%d%d", &g->spotNum, &g->pathNum);
        for(i = 0;i < g->spotNum;i++)
            fscanf(fp, "%d%s%s", &g->spots[i].num, g->spots[i].name, g->spots[i].intro);
        for(i = 0;i < g->spotNum;i++) {
            for (j = 0;j < g->spotNum;j++) {
                if (i == j) g->path[i][j] = 0;
                else g->path[i][j] = INFINITY;
            }
        }
        for(k = 0;k < g->pathNum;k++){
            fscanf(fp, "%d%d%d", &i, &j, &e);
            g->path[i][j] = g->path[j][i] = e;
        }
        fclose(fp);
    }
    else g->pathNum = 0;
}

void Print_Map(){
    system("mspaint map.png");
}

//Floyd算法求两景点间的一条最短的路径

void ShortPath(map *g) {
    int i, j, k;
    for(i = 0;i < g->spotNum;i++) {                                /*初始化距离向量矩阵与路径向量矩阵*/
        for (j = 0; j < g->spotNum; j++) {
            dist[i][j] = g->path[i][j];
            if (i != j && dist[i][j] < INFINITY) path[i][j] = i;
            else path[i][j] = -1;                                  /*-1代表当前两点不可达*/
        }
    }
    for(k = 0;k < g->spotNum;k++) {                                /*递推求解每两景点的最短路径*/
        for (i = 0; i < g->spotNum; i++) {
            for (j = 0; j < g->spotNum; j++) {                        /*更新dist[i][j]的值*/
                if (dist[i][j] > (dist[i][k] + dist[k][j])) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    path[i][j] = k;                                /*path用于记录最短路径上的经结点*/
                }
            }
        }
    }
}

//递归实现打印两点间的最短路径
void PrintPath(map *g, int spotNum, int pathNum) {
	if (path[spotNum][pathNum] == -1 || path[spotNum][pathNum] == pathNum || path[spotNum][pathNum] == spotNum)
		return;
	else {
		PrintPath(g, spotNum, path[spotNum][pathNum]);                 /*将中间点作为终点继续打印路径*/
		printf("%s->", g->spots[path[spotNum][pathNum]].name);         /*打印中间景点名字*/
		PrintPath(g, path[spotNum][pathNum], pathNum);                 /*将中间点作为起点继续打印路径*/
	}
}

int Dist(map *g,int spotNum,int pathNum){
    ShortPath(g);
    return dist[spotNum][pathNum];
}