#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int i, j, v;
} triple;

typedef struct{
    triple data[100];
    int m, n, t;
} matrix;

int main(){
    matrix m1, m2, m0;
    scanf("%d%d%d%d",&m1.m,&m1.n,&m1.t,&m2.t);
    m2.m = m1.m;
    m2.n = m1.n;

    for(int a = 0; a < m1.t; a++){
        scanf("%d%d%d",&m1.data[a].i,&m1.data[a].j,&m1.data[a].v);
    }
    for(int a = 0; a < m2.t; a++){
        scanf("%d%d%d",&m2.data[a].i,&m2.data[a].j,&m2.data[a].v);
    }

    int index = 0, a = 0, b = 0;
    while (a < m1.t && b < m2.t){
        if (m1.data[a].i < m2.data[b].i) m0.data[index++] = m1.data[a++];
        else if (m1.data[a].i > m2.data[b].i) m0.data[index++] = m2.data[b++];
        else if (m1.data[a].j < m2.data[a].j) m0.data[index++] = m1.data[a++];
        else if (m1.data[a].j > m2.data[b].j) m0.data[index++] = m2.data[b++];
        else{
            m1.data[a].v += m2.data[b].v;
            if (m1.data[a].v) m0.data[index++] = m1.data[a];
            a++;
            b++;
        }
    }
    for (int i = a; i < m1.t; i++){
        m0.data[index++] = m1.data[i];
    }

    for (int i = b; i < m2.t; i++){
        m0.data[index++] = m2.data[i];
    }

    printf("%d %d %d\n",m1.m,m1.n,index);

    for (int i = 0; i < index; i++){
        printf("%d %d %d\n",m0.data[i].i,m0.data[i].j,m0.data[i].v);
    }
    return 0;
}
