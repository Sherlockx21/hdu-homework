//
// Created by hang on 2022/11/24.
//

#ifndef EXP4_SCHOOL_MAP_H
#define EXP4_SCHOOL_MAP_H

#include<stdio.h>
#include <stdlib.h>
#include<string.h>

#define INFINITY 10000
#define M 10         //最大景点数
typedef struct {
    int num;
    char name[50];
    char intro[5000];
}scenic_spot;

typedef struct {
    scenic_spot spots[M];
    int path[M][M];         //邻接矩阵
    int spotNum;
    int pathNum;
}map;



void Create_Map(map *g);
void Print_Map();
void ShortPath(map *g);
void PrintPath(map *g, int spotNum, int pathNum);
int Dist(map *g,int spotNum,int pathNum);

#endif //EXP4_SCHOOL_MAP_H
