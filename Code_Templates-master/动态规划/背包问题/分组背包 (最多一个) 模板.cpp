#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;


//************************************ ���鱳�� ģ�� ************************************
const int MAXN = 210;             // ��Ʒ���� 
const int MAXC = 40010;           // �������� 
typedef int ValueType;            // ������ֵ������ 
const ValueType inf = -1e9;       // �����ֵ����С������Сֵ����� 
const ValueType init = 0;         // һ�����������ֵ������Сֵ�����̶�Ϊ 0 

ValueType dp[MAXC];

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

void groupKnapsackInit(int maxCapacity) {
    for (int i = 0; i <= maxCapacity; ++i) {
        dp[i] = (!i) ? init : inf;
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

int groupKnapsack(int knapSize, Knapsack *knap, int m) {
    groupKnapsackInit(m);
    int t = groupKnapsackRegroup(knapSize, knap);
    for (int k = 1; k <= t; ++k) {
        for (int j = m; j >= 0; --j) {
            for (int i = 0; i < GKnap[k - 1].size(); ++i) {
                const Knapsack &item = GKnap[k - 1].get(i);
                if (j >= item.capacity) {
                    dp[j] = opt(
                        dp[j],
                        dp[j - item.capacity] + item.weight
                    );
                }
            }
        }
    }
    return t;
}

//************************************ ���鱳�� ģ�� ************************************
