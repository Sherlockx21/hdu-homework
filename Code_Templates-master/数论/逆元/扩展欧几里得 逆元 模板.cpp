/*
����ͬ��
���ͬ�෽�̵�һ����ת����һ��ʽ��ax + by = c��������̵���ⲽ�����£�
      i) �������a��b�����Լ��d = gcd(a, b)����ôԭ���̿���ת����d(ax/d + by/d) = c������֪��(ax/d + by/d)Ϊ����������d��������b�����̱�Ȼ�޽⣬�㷨�������������ii)��
      ii) ��i)���Ե�֪�������н���һ�����Ա�ʾ�� ax + by = c = gcd(a, b)*c'����ô����������������d = gcd(a, b) = ax + by������ŷ����¶����У�
      d = gcd(a, b) = gcd(b, a%b) = bx' + (a%b)y' = bx' + [a-b*(a/b)]y' = ay' + b[x' - (a/b)y'], ������x = y',  y = x' - (a/b)y'��
      ����gcd(a, b)��һ���ݹ�ļ��㣬���������(x, y)ʱ��(x', y')��ʵ�Ѿ����õݹ��������ˣ��ݹ����Ϊb == 0��ʱ�򣨶Ա�շת�����Ҳ��b == 0��ʱ��ݹ����������ô��ʱ���̵Ľ�x0 = 1, y0 = 0��
*/

/*
��Ԫ
��֪ a �� b������ͬ��ʽ��   ax % b = 1  �� x
1) ��� a �� b �����أ�����Ԫ�����ڣ�
2������ת����   ax + bn = 1 �����һ�����н� x��
3��x = (x % n + n) % n ת������С����������
*/

#include <iostream>

using namespace std;

#define ll long long
#pragma warning(disable : 4996)

ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}

// ��չŷ�����
// aX + bY = 1 
ll ExpGcd(ll a, ll b, ll& X, ll& Y) {
    ll q, temp;
    if (!b) {
        q = a; X = 1; Y = 0;
        return q;
    }
    else {
        q = ExpGcd(b, a % b, X, Y);
        temp = X;
        X = Y;
        Y = temp - (a / b) * Y;
        return q;
    }
}

// a * x % b = 1
// �� x 
ll Inv(ll a, ll b) {
    ll X, Y;
    ExpGcd(a, b, X, Y);
    X = (X % b + b) % b;
    return X;
}