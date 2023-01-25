#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;


//************************************ ��ά 01���� ģ�� ************************************
const int MAXN = 110;             // ��Ʒ���� 
const int MAXC = 410;             // �������� 
typedef int ValueType;            // ������ֵ������ 
const ValueType inf = -1e9;       // �����ֵ����С������Сֵ����� 
const ValueType init = 0;         // һ�����������ֵ������Сֵ�����̶�Ϊ 0 

ValueType dp[MAXC][MAXC];

struct Knapsack {
    int capacity1;
    int capacity2;
    ValueType weight;
    Knapsack(){
    }
    Knapsack(int c1, int c2, ValueType w) : capacity1(c1), capacity2(c2), weight(w) {
    }
}Knap[MAXN];

ValueType opt(ValueType x, ValueType y) {
    return x > y ? x : y;
}

void zeroOneKnapsackInit(int maxCapacity1, int maxCapacity2) {
    for (int i = 0; i <= maxCapacity1; ++i) {
        for (int j = 0; j <= maxCapacity2; ++j) {
            dp[i][j] = (!i && !j) ? init : inf;
        }
    }
}

void zeroOneKnapsack(int knapsackSize, Knapsack *knap, int maxCapacity1, int maxCapacity2) {
    zeroOneKnapsackInit(maxCapacity1, maxCapacity2);
    for (int i = 0; i < knapsackSize; ++i) {
        for (int j = maxCapacity1; j >= knap[i].capacity1; --j) {
            for (int k = maxCapacity2; k >= knap[i].capacity2; --k) {
                dp[j][k] = opt(dp[j][k], dp[j - knap[i].capacity1][k - knap[i].capacity2] + knap[i].weight);
            }
        }
    }
}

//************************************ ��ά 01���� ģ�� ************************************
