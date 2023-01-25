#include <iostream>
#include <algorithm>
#include <cstring>
#include <stack>
using namespace std;

typedef char ValueType;
const int maxn = 1010;
int f[maxn][maxn];
#define I 1
#define D 1
#define R 1

int min3(int a, int b, int c) {
    return min(min(a, b), c);
}

int minEditCost(int ssize, ValueType *src, int tsize, ValueType *tar) {
    f[0][0] = 0;
    // �մ���Ŀ�괮�Ĵ���
    for (int j = 1; j <= tsize; ++j) {
        f[0][j] = f[0][j - 1] + I;
    }
    // Դ�����մ��Ĵ���
    for (int i = 1; i <= ssize; ++i) {
        f[i][0] = f[i - 1][0] + D;
    }
    for (int i = 1; i <= ssize; ++i) {
        for (int j = 1; j <= tsize; ++j) {
            int rcost = (src[i] == tar[j]) ? 0 : R;       // �滻������
            f[i][j] = min3(
                f[i - 1][j] + D,         // Դ��1��������Ŀ����Ҫɾ��1��
                f[i][j - 1] + I,         // Ŀ����1��������Դ��Ҫ����1��
                f[i - 1][j - 1] + rcost  // Դ��Ŀ�� �� �滻 ���һ���ַ�
                );
        }
    }
    return f[ssize][tsize];
}