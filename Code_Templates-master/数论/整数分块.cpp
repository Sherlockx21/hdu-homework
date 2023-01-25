#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

#define ll long long
const int maxn = 200010;
const double eps = 1e-8;

struct Interval {
    int l, r;  
    Interval(int _l, int _r): l(_l), r(_r) {}
    void print() {
        printf("[%d, %d]\n", l, r);
    }
};

//  g(x) = n / x     (x in [1, maxx])
// �� g(x) �Ķ����� x �ֲ�� ��� 2sqrt(n) �����䣬�洢�� ret ���� 
void integerSplit(int maxx, int n, vector<Interval> &ret) {
    ret.clear();
    double sqrtn = sqrt(n + 0.0);
    int last = 1;
    // 1. ���� x <= sqrt(n) �Ĳ��֣� 
    for(int x = 1; x <= sqrtn; ++x) {
        if(x > maxx) {
            return;
        } 
        ret.push_back( Interval(x, x) );
        last = x;
    }
    int intsqrtn = (int)(sqrtn + eps);
    // 2. ���� x > sqrt(n) �Ĳ��� ���� g(x) < sqrt(n) ��������� 
    for(int x = intsqrtn; x >= 1; --x) {
        int now = n / x;
        
        if(last+1 > now) {
            continue;
        }
        
        if(now > maxx) {
            now = maxx;
            ret.push_back( Interval(last+1, now) );
            return ;
        }
        ret.push_back( Interval(last+1, now) );
        last = now;
    }
}
