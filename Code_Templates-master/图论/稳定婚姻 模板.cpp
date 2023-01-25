#include <iostream>
#include <cstring>
#include <string>
#include <cmath>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;


//***************************************** �ȶ������㷨 ģ�� *****************************************//
const int maxn = 1010;
const int NULL_MATCH = -1;

class Male {
    int femaleIndex;        // ��ǰö�ٵ���Ů�Ե�����
    int females[maxn];      // �к���׷���б����պøж�˳�����εݼ�
public:
    void init();
    void fillFemales(int n, int* f);
    int popNextFemale();
};

void Male::init() {
    femaleIndex = 0;
}
void Male::fillFemales(int n, int* f) {
    for (int i = 0; i < n; ++i) {
        females[i] = f[i];
    }
}
int Male::popNextFemale() {
    return females[femaleIndex++];
}



class Female {
    int matchMale;          // ������Ե�����
    int maleRank[maxn];     // ��ϣ���飬�洢��Ӧ�������Լ����е�����
public:
    int getMatch() const;
    void init();
    void setMaleRanks(int n, int *m);
    int exchange(int maleId);
};

int Female::getMatch() const {
    return matchMale;
}

void Female::init() {
    matchMale = NULL_MATCH;
}

void Female::setMaleRanks(int n, int *m) {
    for (int i = 0; i < n; ++i) {
        maleRank[m[i]] = i;
    }
}

int Female::exchange(int maleId) {
    if (matchMale == NULL_MATCH) {
        matchMale = maleId;
        return NULL_MATCH;
    }
    int pre = maleRank[matchMale];
    int now = maleRank[maleId];
    if (pre < now) {
        return maleId;
    }
    else {
        int tmp = matchMale;
        matchMale = maleId;
        return tmp;
    }
}

class stableMarriage {
private:
    int count;
    Male M[maxn];
    Female F[maxn];

public:
    stableMarriage() {}
    ~stableMarriage() {}
    void init(int n);
    void addFemaleListToMale(int maleId, int* femalesSort);
    void addMaleRankToFemale(int femaleId, int *malesSort);
    void doStableMarriage();
    void getCouples(int *males, int *females);
}SM;

void stableMarriage::init(int n) {
    count = n;
    for (int i = 0; i < count; ++i) {
        F[i].init();
        M[i].init();
    }
}

void stableMarriage::addFemaleListToMale(int maleId, int* femalesSort) {
    M[maleId].fillFemales(count, femalesSort);
}

void stableMarriage::addMaleRankToFemale(int femaleId, int *malesSort) {
    F[femaleId].setMaleRanks(count, malesSort);
}

void stableMarriage::doStableMarriage() {
    queue <int> que;
    for (int i = 0; i < count; ++i) {
        que.push(i);
    }
    while (!que.empty()) {
        int maleId = que.front();
        que.pop();
        int femaleId = M[maleId].popNextFemale();
        maleId = F[femaleId].exchange(maleId);
        if (maleId != NULL_MATCH) {
            que.push(maleId);
        }
    }
}

void stableMarriage::getCouples(int *males, int *females) {
    for (int i = 0; i < count; ++i) {
        males[i] = i;
        females[F[i].getMatch()] = i;
    }
}
//***************************************** �ȶ������㷨 ģ�� *****************************************//