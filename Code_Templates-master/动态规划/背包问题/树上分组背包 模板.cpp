#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;


//************************************ ���Ϸ��鱳�� ģ�� ************************************
const int MAXN = 110;             // ��Ʒ���� 
const int MAXC = 110;             // �������� 
typedef int ValueType;            // ������ֵ������ 
const ValueType inf = -1e9;       // �����ֵ����С������Сֵ����� 
const ValueType init = 0;         // һ�����������ֵ������Сֵ�����̶�Ϊ 0 

ValueType dp[MAXN][MAXC];

struct Knapsack {
    int capacity;
    ValueType weight;
    Knapsack(){
    }
    Knapsack(int c, ValueType w) : capacity(c), weight(w) {
    }
}Knap[MAXN];

ValueType opt(ValueType x, ValueType y) {
    return x > y ? x : y;
}

vector <int> edges[MAXN];

void treeGroupKnapsack(int father, int u, int m) {
    int i, j, k;
    int maxCapacity = m - Knap[u].capacity;            // 1����Ҫ������������
    for (i = 0; i <= maxCapacity; ++i)                 // 2�����鱳��������ʼ��
        dp[u][i] = 0;
    for (int idx = 0; idx < edges[u].size(); ++idx) {  // 3�����鱳��ö���飨1������1���飩
        int v = edges[u][idx];
        if (v == father) continue;                     // 4���������Ĵ���
        treeGroupKnapsack(u, v, maxCapacity);          // 5���ݹ�����ӽ���������״̬ dp[v][0 ... capacity]
        for (i = maxCapacity; i >= 0; --i) {           // 6�����鱳������ö������
            for (j = 0; j <= i; ++j) {                 // 7��(����Ϊk, ��ֵΪdp[v][k]) ����Ʒ���о��ߣ�ע�� j Ϊ 0��dp[v][j]��Ϊ0�����
                dp[u][i] = opt(
                    dp[u][i],
                    dp[u][i - j] + dp[v][j]);
            }
        }
    }
    for (i = m; i >= Knap[u].capacity; --i)            // 8��������ѡ����ͬ�����ͬ����
        dp[u][i] = dp[u][i - Knap[u].capacity] + Knap[u].weight;
    for (i = 0; i < Knap[u].capacity; ++i)
        dp[u][i] = 0;

    // ���ĳ���ӽ��Ϊ 0 ������������ߣ����ע��
    // dp[u][0] = 0;
}

//************************************ ���Ϸ��鱳�� ģ�� ************************************
