#include <iostream>
#include <vector>
#include <map>
using namespace std;

// RMQ ������Сֵѯ��
// ��ģ��������������Сֵ�����Ҫ�����ֵ�����Խ�������ȥ�෴����Ȼ������Сֵ����ȡ�����ɡ�
// LCA �����ʱ�����MAXN��Ҫ�ǹ�ģ����������Ϊ��¼�ߵ�ʱ���¼����˫��� 
#define MAXN 200020
#define MAXM 20

// typedef __int64 ValueType;
// typedef double ValueType;
typedef int ValueType;

int lg2K[MAXN];

// n val[]    ��ʾԪ����Ĵ�С��Ԫ��ֵ   -in 
// ret[i][j]  ��ʾ��õ�RMQ����          -out  
void RMQ_Init(int n, ValueType val[], int (*ret)[MAXN]) {
    int i, j, k = 0;
    for(i = 1; i <= n; i++) {
        lg2K[i] = k - 1;
        if((1<<k) == i) k++;
    }
    for(i = 0; i < MAXM; i++) {
        for(j = 1; j <= n; j++) {
            if(i == 0) {
                ret[i][j] = j;
            }else {
                // ret[i][j] = getMinIdx( ret[i-1][j], ret[i-1][ j+(1<<i-1) ] );
                ret[i][j] = ret[i-1][j];
                int ridx = j + (1<<i-1);
                if ( ridx <= n ) {
                    int r = ret[i-1][ridx];
                    if( val[r] < val[ ret[i][j] ] ) {
                        ret[i][j] = r;
                    }
                }
            }
        }
    }
}

/*
    �����䳤��Ϊ2^k����X��ʾ������Ϊ[a, a + 2^k)��Y��ʾ������Ϊ(b - 2^k, b]��
����Ҫ����һ����������X���Ҷ˵������ڵ���Y����˵�-1���� a+2^k-1 >= b-2^k��
��2^(k+1) >= (b-a+1), ����ȡ��������2Ϊ�ף����� k+1 >= lg(b-a+1)����k >= lg(b-a+1) - 1��
kֻҪ��Ҫȡ��С��������������������( lg(x)������2Ϊ��x�Ķ��� )��
*/
int RMQ_Query(ValueType val[], int (*rmq)[MAXN], int a, int b) {
    if(a == b) {
        return a;
    }else if(a > b) {
        a = a^b, b = a^b, a = a^b;
    }
    int k = lg2K[ b-a+1 ];
    return val[ rmq[k][a] ] < val[ rmq[k][b-(1<<k)+1] ] ? rmq[k][a] : rmq[k][b-(1<<k)+1];
}


/*
LCA ת��Ϊ RMQ
       ����Ҫ��һ��������7�����㣬6����Ϊ��:
              7
              (0,5) (5,2) (2,4) (3,0) (1,3) (3,6)
       1)�������㲻ȷ������ô����0Ϊ����㣬Ȼ��Ӹ���㿪ʼ����һ��������ȱ�����ԭ�б���M������ôһ�α�����Ͼͻ���2M���ߡ�
              (0,5) -> (5,2) -> (2,4) -> (4,2) -> (2,5) -> (5,0) -> (0,3) -> (3,1) -> (1,3) -> (3,6) -> (6,3) -> (3,0)
       2)�������������ߵĶ˵���һ���ģ����Կ���ѹ����һ��һά����E (edge)�У�
              E[i] = 0 5 2 4 2 5 0 3 1 3 6 3 0
         ��E�����ж�Ӧ�������ϵ���ȼ�¼������D (depth)�У�
              D[i] = 0 1 2 3 2 1 0 1 2 1 2 1 0
       3)��ÿ������E�����е�һ�γ��ֵ�λ�ü�¼��I (index)�У�
              I[i] = 0 8 2 7 3 1 10
       4) Ȼ��õ����x��y������������ȣ�
              LCA(x, y) = E[ RMQ_MIN( D, I[x], I[y] ) ]
*/

int edgeCount;
int E[MAXN], I[MAXN];
ValueType D[MAXN];
int D_RMQ[MAXM][MAXN];

// �洢���ϵ��ڽӱ� 
vector <int> edge[MAXN];

void addEdgeVertex(int vertex, int depth) {
    ++edgeCount;
    E[ edgeCount ] = vertex;
    D[ edgeCount ] = depth;        
}

void LCA_Dfs(int fat, int u, int depth) {
    addEdgeVertex(u, depth);
    for(int i = 0; i < edge[u].size(); i++) {
        int v = edge[u][i];
        if(v == fat) {
            // ����˫��ߵ����������޸��� 
            continue; 
        }
        LCA_Dfs(u, v, depth+1);
        addEdgeVertex(u, depth);    
    }    
}

// ��������Ķ��㼯��
// ������ [0, n)��Ҳ������[1, n]����ҪӰ�����I����ĳ�ʼ�� 
void LCA_Init(int n, int root) {
    int i;
    
    edgeCount = 0;
    LCA_Dfs(-1, root, 0);
    RMQ_Init(edgeCount, D, D_RMQ);
    
    for(i = 0; i <= n; i++) {
        I[i] = -1;
    }
    for(i = 1; i <= edgeCount; i++) {
        if( I[ E[i] ] == -1 ) {
            I[ E[i] ] = i;
        }
    }
    
}

int LCA_Query(int x, int y) {
    return E[ RMQ_Query(D, D_RMQ, I[x], I[y]) ];
}
