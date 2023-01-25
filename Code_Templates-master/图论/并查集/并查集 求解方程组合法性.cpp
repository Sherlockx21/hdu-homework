/*
���⣺
    ����N(N <= 200000)��Ԫ�ص�����A[i]���ٸ���һЩ��Ԫ��(i, j, k)����ʾA[i] + A[i+1] + ... A[j] = k
��M����Ԫ���д���������ж��ٸ�����ĳ����Ԫ���֮ǰ�������ͻ��ʱ��������Ǵ�ģ����Һ���������
 
��⣺ 
    ���鼯
    ��S[i]Ϊ����A��ǰi��ͣ���ôA[i] + A[i+1] + ... A[j] = k���Ա�ʾΪ S[j] - S[i-1] = k����ô��j��i-1
����������x��y (x = j, y = i-1)�� 
    ���в��鼯�Ĳ��Ҳ��������x��y����һ�������У������Ǻϲ���һ�����ϣ������Ȼ��ǣ�浽x��y�ĸ��ӹ�
ϵ����������һ����ֵ�ĸ����d[i] = S[i] - S[pre[i]]������pre[i]�����鼯������i�ĸ��׽�㣬����ģ�
��iΪ���鼯ɭ���еĸ�����ʱ��i == pre[i]����d[i] = S[i] - S[i] = 0�������Ϳ���ͨ�����ӽ����������
�ݽ�����������dֵ�ۼӣ����ܼ����S[x]��ֵ��(S[x] = d[x] + d[pre[x]] + ... + d[root])��
    �㷨���£�
    1) 
        ����x������������Ĳ�ֵ x2fx = getRelToRootVal(x); // S[x] - S[fx] = x2fx;
        ����y������������Ĳ�ֵ y2fy = getRelToRootVal(y); // S[y] - S[fy] = y2fy;
    2)  ���x��y����һ�������У� 
        �ϲ�x��y 
        a) ����ϲ���xrootΪyroot���ӽ�� 
            val[xroot] = S[xroot] - S[yroot] = (S[x] - x2fx) - (S[y] - y2fy) = (S[x] - S[y]) + (y2fy - x2fx) = -z + (y2fy - x2fx);
        b) ����ϲ���yrootΪxroot���ӽ�� 
            val[yroot] = S[yroot] - S[xroot] = (S[y] - y2fy) - (S[x] - x2fx) = (S[y] - S[x]) + (x2fx - y2fy) = z + (x2fx - y2fy);
    3)  ���x��y����һ������  
         z ������  y2fy - x2fx ����ʾ���x��y���Ϸ������ۼӣ� 
*/
#include <iostream>

using namespace std;

#define LL __int64
#define MAXN 200010

int pre[MAXN], h[MAXN];

int unionset_find(int p) {
    int x = p;
    while(pre[p] != p) {
        p = pre[p];
    }
    /*while(x != p) {
        int tmp = pre[x];
        pre[x] = p;
        x = tmp;
    }*/
    return p;
}

int unionset_union(int x, int y) {
    int fx = unionset_find(x);
    int fy = unionset_find(y);
    if(x == y) {
        return false;
    }else {
        if( h[fx] == h[fy] ) {
            pre[fy] = fx;
            h[fx]++;
        }else if( h[fx] < h[fy] ) {
            pre[fx] = fy;
        }else {
            pre[fy] = fx;
        }
        return true;
    }
}

LL val[ MAXN ];

// �õ� sum[x] ��ֵ 
int getRelToRootVal(int p) {
    int sum = 0;
    while(pre[p] != p) {
        sum += val[p];
        p = pre[p];         
    }
    return sum;
}

int n, m;

int main() {
    int i;
    while( scanf("%d %d", &n, &m) != EOF ) {
        for(i = 0; i <= n; i++) {
            pre[i] = i;
            h[i] = 1;
            val[i] = 0;
        }
        int cnt = 0;
        while(m--) {
            int x, y, z;
            
            scanf("%d %d %d", &x, &y, &z);
            x--;
            
            // s[y] - s[x] = z
            int fy = unionset_find(y);
            int fx = unionset_find(x);
            if( fx != fy ) {
                int x2fx = getRelToRootVal(x); // s[x] - s[fx] = x2fx;
                int y2fy = getRelToRootVal(y); // s[y] - s[fy] = y2fy;
                unionset_union(x, y);
                if(pre[fx] == fy) {
                    // val[fx] = s[fx] - s[fy] = (s[x] - x2fx) - (s[y] - y2fy) = (s[x] - s[y]) + (y2fy - x2fx);
                    val[fx] = -z + (y2fy - x2fx);
                }else {
                    // val[fy] = s[fy] - s[fx] = (s[y] - y2fy) - (s[x] - x2fx) = (s[y] - s[x]) + (x2fx - y2fy);
                    val[fy] = z + (x2fx - y2fy);
                }
            }else {
                int x2fx = getRelToRootVal(x); // s[x] - s[root] = x2fx;
                int y2fy = getRelToRootVal(y); // s[y] - s[root] = y2fy;
                if( z != y2fy - x2fx ) cnt++;
            }
        }
        printf("%d\n", cnt);
    }
}

