/*
	��չŷ������ǰ����Ҫ��
		1������ɸѡ
		2��ŷ���������
		3�����ֿ�����
	�� b >= phi(c) ʱ
		a^b mod c = a^(b mod phi(c) + phi(c)) mod c
*/

#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <memory.h>
#include <cmath>
using namespace std;

#pragma warning(disable : 4996)

#define ll long long
#define MAXP 65540

int primes[MAXP];
bool notprime[MAXP];

// �����������ɸѡ�� 
void Eratosthenes() {
	memset(notprime, false, sizeof(notprime));
	notprime[1] = true;
	primes[0] = 0;
	for (int i = 2; i < MAXP; i++) {
		if (!notprime[i]) {
			primes[++primes[0]] = i;
			//��Ҫע��i*i�������ͺ��ɸ��������⣬����ת���� long long
			for (ll j = (ll)i * i; j < MAXP; j += i) {
				notprime[j] = true;
			}
		}
	}
}

// ŷ������ - ��ȡС��n��������n���ص����ĸ��� 
// ������
// Phi(10) = 4
// �� 1��3��7��9  �ܹ�4�� 
int Phi(int n) {
	if (n == 1)
		return 1;
	int ans = 1;
	for (int i = 1; i <= primes[0]; i++) {
		int p = primes[i];
		if (0 == n % p) {
			n /= p;
			ans *= (p - 1);
			while (0 == n % p) {
				n /= p;
				ans *= p;
			}
		}
		if (n == 1)
			return ans;
	}
	return ans * (n - 1);
}

ll Exp(ll a, ll n, ll Mod) {
	ll ans = 1;
	while (n) {
		if (n & 1) ans = ans * a % Mod;
		a = a * a % Mod;
		n >>= 1;
	}
	return ans;
}
