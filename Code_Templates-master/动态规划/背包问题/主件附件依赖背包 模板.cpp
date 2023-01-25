#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;


//************************************ �������� ģ�� ************************************
//**************************** ����ֻ��һ������������������� ****************************

const int MAXN = 55;              // ��Ʒ����
const int MAXC = 100010;          // �������� 
typedef int ValueType;            // ������ֵ������ 
const ValueType inf = -1e9;       // �����ֵ����С������Сֵ����� 
const ValueType init = 0;         // һ�����������ֵ������Сֵ�����̶�Ϊ 0 

ValueType dp[2][MAXC];

enum KnapsackType {
    KT_MASTER = 0,
    KT_SLAVE = 1,
};

struct Knapsack {
    int capacity;
    ValueType weight;
    Knapsack(){
    }
    Knapsack(int c, ValueType w) : capacity(c), weight(w) {
    }
};

struct MasterKnapsack : public Knapsack {
    vector <Knapsack> slaves;
    MasterKnapsack(){}

    MasterKnapsack(int c, ValueType w) {
        capacity = c;
        weight = w;
        slaves.clear();
    }
    void add(const Knapsack& k) {
        slaves.push_back(k);
    }
    int size() const {
        return slaves.size();
    }
    const Knapsack& get(int idx) const {
        return slaves[idx];
    }
}MKnap[MAXN];

ValueType opt(ValueType x, ValueType y) {
    return x > y ? x : y;
}

// ����һ������������������⣬���ڽ������ '����' �����ȹ��� '����' ������
int relyOnelayerKnapsack(int knapsackSize, MasterKnapsack* knap, int maxCapacity) {
    int cur = 0, last = 1;
    memset(dp, 0, sizeof(dp));
    for (int i = 0; i < knapsackSize; ++i) {
        const MasterKnapsack &mItem = knap[i];

        // 1. �����Ŀ���Ǽ���� i ������һ��Ҫ������
        for (int j = 0; j <= maxCapacity; ++j) {
            if (j < mItem.capacity) {
                // 1.1 ������������
                dp[cur][j] = inf;
            }
            else {
                // 1.2 ������ǾͰ���������������һ���е����� 0/1 �����е� 1
                dp[cur][j] = dp[last][j - mItem.capacity] + mItem.weight;
            }
        }

        // 2. ���ڣ���ǰ�������Ѿ��������ˣ�Ȼ��Ϳ��Կ�ʼ���������ڲ���Ʒ�� 0/1 ������
        for (int j = 0; j < mItem.size(); ++j) {
            const Knapsack &sItem = mItem.get(j);
            for (int k = maxCapacity; k >= sItem.capacity; --k) {
                dp[cur][k] = opt(dp[cur][k], dp[cur][k - sItem.capacity] + sItem.weight);
            }
        }

        // 3. ������ǱȽ�һ�µ�������Ƚ��ţ����ǲ���Ƚ���
        for (int j = maxCapacity; j >= 0; --j) {
            dp[cur][j] = opt(dp[cur][j], dp[last][j]);
        }

        cur ^= 1;
        last = 1 - cur;
    }
    return dp[last][maxCapacity];
}

//**************************** ����ֻ��һ������������������� ****************************
//************************************ �������� ģ�� ************************************

