#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
#include <string>
#include <cstdio>
using namespace std;

/*
    �������ظ��ַ����٣��ַ��Ƚ�ϡ������
    ��A����B���е��±갴���������к�����ӳ���һ���µ����У������������ �ϸ������������
    ʱ�临�Ӷ���õ���� O(nlogn)�� ���� O(n^2logn)
*/

/*******************************************����������� ģ��*******************************************/
typedef int ValueType;
const int maxn = 100010;
const int inf = -1;
// �� g �������ҵ�ʱ��
// ������ϸ񵥵������� <= 
// ����Ƿǵ�����ǵݼ������� < 
ValueType g[maxn];
int gsize;

enum LISType {
    LIST_STRICTLY = 0,            // �ϸ񵥵�
    LIST_NOTSTRICTLY = 1,         // ���ϸ񵥵�
};

bool cmpLIS(LISType lt, ValueType a, ValueType b) {
    if (LIST_STRICTLY == lt) {
        return a <= b;
    }
    else if (LIST_NOTSTRICTLY == lt) {
        return a < b;
    }
}

int findLISIndex(LISType lt, ValueType val, ValueType *g, int& gsize) {
    int l = 1, r = gsize, ans = -1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (cmpLIS(lt, val, g[mid])) {
            ans = mid;
            r = mid - 1;
        }
        else {
            l = mid + 1;
        }
    }
    return ans;
}

void findLIS(LISType lt, ValueType *a, int asize) {
    gsize = 0;
    for (int i = 1; i <= asize; ++i) {
        int ans = findLISIndex(lt, a[i], g, gsize);
        if (ans == -1) {
            ans = ++gsize;
        }
        g[ans] = a[i];            // g[ans]: ����Ϊans����������������һ��ֵ����Сֵ
    }
}


/*******************************************����������� ģ��*******************************************/

typedef int LCSType;
const int maxc = 100001;

void preLCS(int hsize, LCSType *h, int maxv, vector<int> pos[maxc]) {
    for (int i = 0; i <= maxv; ++i) {
        pos[i].clear();
    }
    for (int i = 1; i <= hsize; ++i) {
        pos[h[i]].push_back(i);
    }
    for (int i = 0; i <= maxv; ++i) {
        reverse(pos[i].begin(), pos[i].end());
    }
}

int a[maxn];

int getLCS(int vsize, LCSType *v, vector<int> pos[26]) {
    int s = 0;
    for (int i = 1; i <= vsize; ++i) {
        int idx = v[i];
        for (int j = 0; j < pos[idx].size(); ++j) {
            a[++s] = pos[idx][j];
        }
    }
    findLIS(LIST_STRICTLY, a, s);
    return gsize;
}
