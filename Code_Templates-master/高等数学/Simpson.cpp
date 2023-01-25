#include <iostream>
#include <cmath>
#include <cstdio>
using namespace std;

#define EPS 1e-9
#define ValType double

// y = f(x)        ԭ����
typedef ValType(*origFunc)(ValType);
// F(x) = f'(x)    ���ֺ��� 
typedef ValType(*inteFunc)(ValType);

class IntegrationApproximation {
public:
	IntegrationApproximation() : m_kOrigFunc(NULL), m_kInteFunc(NULL) {}
	virtual ~IntegrationApproximation() {}
	inline void SetOrigFunc(origFunc oFunc) {
		m_kOrigFunc = oFunc;
	}
	inline void SetInteFunc(inteFunc iFunc) {
		m_kInteFunc = iFunc;
	}
	void    test(ValType s, ValType t);
	ValType getVal(ValType s, ValType t);
private:
	inline ValType _ladder(ValType u, ValType d, ValType h) {
		return (u + d) * h;
	}
	ValType ladder(ValType s, ValType t, ValType cnt);                                       // ���η���
	ValType integration(ValType s, ValType t);                                               // ������
	ValType simpson(ValType s, ValType t);                                                   // ����ɭ
	ValType self_adapt_simpson(ValType s, ValType t, ValType simpsonval);  // ����Ӧ����ɭ

	origFunc             m_kOrigFunc;
	inteFunc             m_kInteFunc;
};


// ���η���
ValType IntegrationApproximation::ladder(ValType s, ValType t, ValType cnt) {
	if (m_kOrigFunc == NULL) {
		return 0;
	}
	ValType sum = 0;
	ValType step = (t - s) / cnt;
	ValType prex = s, prey = m_kOrigFunc(s);
	ValType nowx, nowy;
	for (ValType x = s; x < t; x += step) {
		nowx = x;
		nowy = m_kOrigFunc(nowx);

		sum += _ladder(prey, nowy, step);

		// �洢 prey ������һ�� f(x) �ļ���
		prex = nowx;
		prey = nowy;
	}

	nowx = t;
	nowy = m_kOrigFunc(nowx);

	sum += _ladder(prey, nowy, nowx - prex);

	return sum / 2;
}

// ������
ValType IntegrationApproximation::integration(ValType s, ValType t) {
	if (m_kInteFunc == NULL) {
		return 0.0;
	}
	return m_kInteFunc(t) - m_kInteFunc(s);
}

// ����ɭ
ValType IntegrationApproximation::simpson(ValType s, ValType t) {
	if (m_kOrigFunc == NULL) {
		return 0.0;
	}
	ValType m = (s + t) / 2;
	return (t - s) / 6 * (m_kOrigFunc(s) + 4 * m_kOrigFunc(m) + m_kOrigFunc(t));
}

// ����Ӧ����ɭ
ValType IntegrationApproximation::self_adapt_simpson(ValType s, ValType t, ValType simpsonval) {
	ValType m = (s + t) / 2;
	ValType lval = simpson(s, m);
	ValType rval = simpson(m, t);
	ValType reval = lval + rval;
	// reval һ���� simpsonval ����׼ȷ
	// �����з�ԽС�϶�Խ׼ȷ��
	if (fabs(reval - simpsonval) < EPS) {
		return reval;
	}
	// ����ע�⣺����Ҳ�����۰�
	return self_adapt_simpson(s, m, lval) + self_adapt_simpson(m, t, rval);
}

// ����Ӧ����ɭ ����ӿ� 
ValType IntegrationApproximation::getVal(ValType s, ValType t) {
	return self_adapt_simpson(s, t, simpson(s, t));
}

void IntegrationApproximation::test(ValType s, ValType t) {
	printf("���η���(�ֶ�100):     %30.9lf\n", ladder(s, t, 100));
	printf("���η���(�ֶ�10000):   %30.9lf\n", ladder(s, t, 10000));
	printf("���η���(�ֶ�1000000): %30.9lf\n", ladder(s, t, 1000000));
	printf("����ɭ�㷨:            %30.9lf\n", simpson(s, t));
	printf("����Ӧ����ɭ�㷨:      %30.9lf\n", self_adapt_simpson(s, t, simpson(s, t)));
	printf("����:                  %30.9lf\n", integration(s, t));	
}

ValType f(ValType x) {
return 20 * sin(x / 5) + x / 3 + 20;
}

ValType f_integration(ValType x) {
return - 100 * cos(x / 5) + x * x / 6 + 20 * x;
}


/*
ValType f(ValType x) {
	return 27 * x*x - 36 * x + 65;
}

ValType f_integration(ValType x) {
	return 9*x*x*x - 18*x*x + 65*x;
}
*/
double a, b, c, d;
double l, r;

/*
ValType f(ValType x) {
	return (c*x+d) / (a*x+b);
}
*/

int main() {
	IntegrationApproximation A;
	A.SetOrigFunc(f);
	A.SetInteFunc(f_integration);
	A.test(30, 80);
	/*while (scanf("%lf %lf %lf %lf %lf %lf", &a, &b, &c, &d, &l, &r) != EOF) {
		//A.test(l, r);
		double ans = A.getVal(l, r);
		printf("%.6lf\n", ans);
	}
	*/
	return 0;
}

/*

15.720084231086
72.77300

34
10000 10000 -10000 10000
*/