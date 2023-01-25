#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;


//************************************ ���鱳�� ģ�� ************************************
const int MAXN = 110;           // ��Ʒ���� 
const int MAXC = 10010;           // �������� 
typedef int ValueType;            // ������ֵ������ 
const ValueType inf = -1e9;       // �����ֵ����С������Сֵ����� 
const ValueType init = 0;         // һ�����������ֵ������Сֵ�����̶�Ϊ 0 

ValueType dp[MAXN][MAXC];

struct Knapsack {
    int groupId;
    int capacity;
    ValueType weight;
    Knapsack(){
    }
    Knapsack(int g, int c, ValueType w) : groupId(g), capacity(c), weight(w) {
    }

    bool operator < (const Knapsack& knap) const {
        return groupId < knap.groupId;
    }
}Knap[MAXN];

struct GroupKnapsack {
    vector <Knapsack> items;
    void clear() {
        items.clear();
    }
    void add(const Knapsack& knap) {
        items.push_back(knap);
    }
    int size() const {
        return items.size();
    }
    int getGroupId() {
        if (size()) {
            return items[0].groupId;
        }
        return -1;
    }
    const Knapsack& get(int idx) const {
        return items[idx];
    }
}GKnap[MAXN];

ValueType opt(ValueType x, ValueType y) {
    return x > y ? x : y;
}

ValueType opt(ValueType x, ValueType y, ValueType z) {
    return opt(opt(x, y), z);
}

void groupKnapsackInit(int maxCapacity) {
    for (int i = 0; i <= maxCapacity; ++i) {
        dp[0][i] = (!i) ? init : inf;
    }
}

int groupKnapsackRegroup(int knapsackSize, Knapsack *knap) {
    sort(knap, knap + knapsackSize);
    int groupId = -1;
    for (int i = 0; i < knapsackSize; ++i) {
        if (groupId == -1 || knap[i].groupId != GKnap[groupId].getGroupId())
            GKnap[++groupId].clear();

        GKnap[groupId].add(knap[i]);
    }
    return ++groupId;
}

// ע�⣺
// 1���������������ں�ԭ�������ж���
// 2�������п���Ϊ0��ע��״̬ת��˳���ȼ��㵱ǰ�顢�ټ�����һ��
int groupKnapsack(int knapSize, Knapsack *knap, int m) {
    groupKnapsackInit(m);
    int t = groupKnapsackRegroup(knapSize, knap);
    for (int k = 1; k <= t; ++k) {
        for (int j = 0; j <= m; ++j) {
            dp[k][j] = inf;
        }
        for (int i = 0, s = GKnap[k - 1].size(); i < s; ++i) {
            const Knapsack &item = GKnap[k - 1].get(i);
            for (int j = m; j >= item.capacity; --j) {
                dp[k][j] = opt(
                    dp[k][j],
                    dp[k][j - item.capacity] + item.weight,
                    dp[k - 1][j - item.capacity] + item.weight
                    );
            }
        }
    }
    return t;
}

//************************************ ���鱳�� ģ�� ************************************