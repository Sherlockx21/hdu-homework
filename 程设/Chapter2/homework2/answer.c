#include <stdio.h>
#include <stdlib.h>
#define N 10

int visit(int, int);

int maze[N][N] = {
{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
{ 2, 0, 2, 2, 0, 2, 2, 0, 0, 0},
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


int visit(int i, int j) {
	maze[i][j] = 1;

	if (i == endI && j == endJ) success = 1;

	if (!success && maze[i][j + 1] == 0 && j!=N-1) visit(i, j + 1);
	if (!success && maze[i + 1][j] == 0 && i!=N-1) visit(i + 1, j);
	if (!success && maze[i][j - 1] == 0 && j != 0) visit(i, j - 1);
	if (!success && maze[i - 1][j] == 0 && i != 0) visit(i - 1, j);

	if (success != 1) maze[i][j] = 0;

	return success;
}

int main() {
	int i, j;
  port(maze);
	//打印地图
	printf("Maze\n");
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++)
			if (maze[i][j] == 2)
				printf("#");
			else
				printf(" ");
		printf("\n");
	}
  //printf("%d %d %d %d\n",startI,startJ,endI,endJ);
	if (visit(startI, startJ) == 0)
		printf("\nNo answer!\n");
	else {
		printf("\nWay\n");
		for (i = 0; i < N; i++) {
			for (j = 0; j < N; j++) {
				if (maze[i][j] == 2)
					printf("#");
				else if (maze[i][j] == 1)
					printf("o");
				else
					printf(" ");
			}
			printf("\n");
		}
	}
	return 0;
}
