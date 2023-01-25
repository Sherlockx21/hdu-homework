#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;

//************************************ K �� 01���� ģ�� ************************************
const int MAXN = 110;             // ��Ʒ���� 
const int MAXC = 1010;            // ��������
const int MAXK = 31;              // �� K ��
typedef int ValueType;            // ������ֵ������ 
const ValueType inf = -1e9;       // �����ֵ����С������Сֵ����� 
const ValueType init = 0;         // һ�����������ֵ������Сֵ�����̶�Ϊ 0 

ValueType dp[MAXC][MAXK];

struct Knapsack {
    int capacity;
    ValueType weight;
    Knapsack(){
    }
    Knapsack(int c, ValueType w) : capacity(c), weight(w) {
    }
}Knap[MAXN];

void opt(int K, ValueType* x, ValueType* y, ValueType *res) {
    ValueType totala[MAXK << 1];
    int s = 0;
    for (int i = 0; i < K; ++i) {
        totala[s++] = x[i];
        totala[s++] = y[i];
    }

    sort(totala, totala + s, greater<int>());
    int residx = 0;
    for (int i = 0; i < s; ++i) {
        if (residx == 0 || totala[i] != res[residx - 1])
            res[residx++] = totala[i];
        if (residx == K) return;
    }
}

void zeroOneKthKnapsackInit(int maxCapacity) {
    for (int i = 0; i <= maxCapacity; ++i) {
        for (int j = 0; j < MAXK; ++j)
            dp[i][j] = (!i && !j) ? init : inf;
    }
}

// dp[i][j][0...k] = maxk{ dp[i-1][j][0...k], dp[i-1][j - c[i]][0...k] + w[i] }
void zeroOneKthKnapsack(int knapsackSize, int K, Knapsack *knap, int maxCapacity) {
    zeroOneKthKnapsackInit(maxCapacity);
    for (int i = 0; i < knapsackSize; ++i) {
        for (int j = maxCapacity; j >= knap[i].capacity; --j) {
            ValueType o[MAXK];
            for (int k = 0; k < K; ++k) {
                o[k] = dp[j - knap[i].capacity][k] + knap[i].weight;
            }
            opt(K, dp[j], o, dp[j]);
        }
    }
}

//************************************ K �� 01���� ģ�� ************************************

