//
// Created by hang on 2022/11/24.
//


#include "map.h"
#include "visitor.h"
int Judge_Input(int num){
    if (num < 1 || num > M){
        printf("\n输入的编号有误，请输入1-%d之间的数字！\n",M);
        return 0;
    }
    return num;
}

void Search_Location(map *g){
    int s;
    while(1){
        printf("\n请输入你要查找的景点编号(1~10,按0退出)：");
        scanf("%d", &s);
        if(s == 0) break;
        if(!Judge_Input(s)) continue;
        printf("\n景点名称：[%s]\n\n", g->spots[s - 1].name);
        printf("景点简介： %s\n\n", g->spots[s - 1].intro);
    }
}

void PrintShortPath(map *g) {
    int spotNum, pathNum;                                             /*起点编号，终点编号*/
    while(1) {
        printf("\n请输入起点编号：");
        scanf("%d", &spotNum);
        if(!Judge_Input(spotNum)) continue;
        else break;
    }
    while(1) {
        printf("\n请输入终点编号：");
        scanf("%d", &pathNum);
        if(!Judge_Input(pathNum)) continue;
        else break;
    }
    printf("\n%s到%s的最短距离是：%dm\n", g->spots[--spotNum].name, g->spots[--pathNum].name, Dist(g,spotNum,pathNum));
    printf("\n这是最佳游览路线：");
    printf("%s->", g->spots[spotNum].name);                                       /*输出路径上的起点*/
    PrintPath(g, spotNum, pathNum);                                               /*输出路径上的中间点*/
    printf("%s\n\n", g->spots[pathNum].name);                                     /*输出路径上的终点*/
}