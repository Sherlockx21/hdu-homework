#include <iostream>
#include <algorithm>

using namespace std;

struct Pair {
    int w, s;
    int idx;
    bool read(int i) {
        idx = i;
        return scanf("%d %d", &w, &s) != EOF;
    }
    bool operator < (const Pair&  p) const {
        if (s != p.s)
            return s > p.s;
        return w < p.w;
    }

};

/*******************************************����������� ģ��*******************************************/
typedef Pair ValueType;
const int maxn = 100010;
const int inf = -1;
// �� g �������ҵ�ʱ��
// ������ϸ񵥵������� <= 
// ����Ƿǵ�����ǵݼ������� < 
ValueType g[maxn];
int idx[maxn];
int pre[maxn];
int f[maxn];
int gsize;
int path[maxn], pasize;

enum LISType {
    LIST_STRICTLY = 0,            // �ϸ񵥵�
    LIST_NOTSTRICTLY = 1,         // ���ϸ񵥵�
};

bool cmpLIS(LISType lt, ValueType a, ValueType b) {
    if (LIST_STRICTLY == lt) {
        return a.w <= b.w;
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

void findPath(int asize) {
    int maxIdx = inf;
    for (int i = asize; i >= 1; --i) {
        if (maxIdx == -1 || f[i] > f[maxIdx]) {
            maxIdx = i;
        }
    }
    pasize = 0;
    while (maxIdx != inf) {
        path[pasize++] = maxIdx;
        maxIdx = pre[maxIdx];
    }

    for (int i = 0; i < pasize / 2; ++i) {
        swap(path[i], path[pasize - 1 - i]);
    }
}

void findLIS(LISType lt, ValueType *a, int asize) {
    gsize = 0;
    idx[0] = inf;
    for (int i = 1; i <= asize; ++i) {
        int ans = findLISIndex(lt, a[i], g, gsize);
        if (ans == -1) {
            ans = ++gsize;
        }
        g[ans] = a[i];            // g[ans]: ����Ϊans����������������һ��ֵ����Сֵ
        idx[ans] = i;             // idx[ans]: ƥ�� g ������±�
        pre[i] = idx[ans - 1];    // pre[i]: ��i������Ϊ���������е����һ������ǰ���� pre[i]
        f[i] = ans;               // f[i]:   ��a[i]��β������������г���
    }
    findPath(asize);
}


/*******************************************����������� ģ��*******************************************/