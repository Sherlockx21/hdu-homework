#include<stdio.h>
#define MAX 25
int a[MAX][MAX];//地图
int book[MAX][MAX]={0};
int next[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
int n, m;

/*4 3
1 1 1
1 2 2
1 2 3
2 2 4
*/
/*→ ← ↓  ↑*/
void dfs(int x, int y,int num){
    int k;
    int tx, ty;

    for (k = 0; k < 4; k++){
        tx = x + next[k][0];
        ty = y + next[k][1];
        if (tx < 0 || tx >= n || ty < 0 || ty >= m)
            continue;
        if (a[tx][ty] == a[x][y] && book[tx][ty] == 0){
            book[tx][ty] = a[x][y];
            dfs(tx,ty,a[tx][ty]);
        }

    }
    return;
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
    }
/*
    for(i=0;i<m;i++){
      for(j=0;j<n;j++){
        printf("%d ",book[i][j]);
        if(j==n-1) printf("\n");
      }
    }*/
    printf("%d", count);
    return 0;
}
