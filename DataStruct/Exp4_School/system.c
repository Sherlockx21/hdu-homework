//
// Created by hang on 2022/11/24.
//

#include "map.h"
#include "visitor.h"
#include <pthread.h>
int menu() {
    int s;
    printf("\t\t          ┌─────────────────────────────┐                \n");
    printf("\t\t┌──────├── 欢迎使用杭州电子科技大学校园导游程序 ──┤───────┐\n");
    printf("\t\t│         └─────────────────────────────┘          │\n");
    printf("\t\t│  ┌────────────┐  ┌────────────────┐  ┌────────┐  │\n");
    printf("\t\t│  │1.景点信息查询│  │2.景点间最短路径查询│  │3.显示地图│ │\n");
    printf("\t\t│  └────────────┘  └────────────────┘  └────────┘  │\n");
    printf("\t\t└──────────────────────────────────────────────────┘\n\n");
    printf("\t\t请根据你的需求选择操作：");
    scanf_s("%d", &s);
    printf("\n\n");
    return s;
}

int main() {
    system("chcp 65001");
    int quit = 0;
    pthread_t m;
    map g;
    Create_Map(&g);
    ShortPath(&g);
    while (!quit) {
        switch (menu()) {
            case 1:system("cls");Search_Location(&g); break;
            case 2:system("cls");PrintShortPath(&g); break;
            case 3:system("cls");Print_Map();break;
            default:printf("\t\t\t\t\t错误！没有该选项对应的操作。\n\n");
        }
        system("pause");
//        system("cls");
    }
}