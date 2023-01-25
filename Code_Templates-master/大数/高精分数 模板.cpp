#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
 
using namespace std;
typedef int hugeint;
typedef unsigned long long ULL;
//Ӧ������,�Է��˷�ʱ���
const int Base = 1000;
const int Capacity = 100;

struct xnum
{
    int Len;
    int Data[Capacity];
    xnum() : Len(0) {}
    xnum(const xnum& V) : Len(V.Len) {
        memcpy(Data, V.Data, Len * sizeof *Data);
    }
    xnum(int V) : Len(0) { 
        for (; V > 0; V /= Base) Data[Len++] = V % Base;
    }
    xnum(ULL V) : Len(0) { 
        for (; V > 0; V /= Base) Data[Len++] = V % Base;
    }
    xnum(char S[]);
    xnum& operator=(const xnum& V) { 
        Len = V.Len;
        memcpy(Data, V.Data, Len * sizeof *Data); 
        return *this;
    }
    int& operator[](int Index) { return Data[Index]; }
    int operator[](int Index) const { return Data[Index]; }

    void print(){
        printf("%d",Len==0?0:Data[Len-1]);
        for(int i=Len-2;i>=0;i--)
            for(int j=Base/10;j>0;j/=10)
                printf("%d",Data[i]/j%10);
    }
};

xnum::xnum(char S[])
{
    int I, J;
    Data[Len = 0] = 0;
    J = 1;
    for (I = strlen(S)-1; I>=0; I--) {
        Data[Len] += (S[I] - '0') * J;
        J *= 10;
        if (J >= Base) J = 1, Data[++Len] = 0;
    }
    if (Data[Len] > 0) Len++;
}

int compare(const xnum& A, const xnum& B)
{
    int I;
    if (A.Len != B.Len) return A.Len > B.Len ? 1 : -1;
    for (I = A.Len - 1; I >= 0 && A[I] == B[I]; I--);
    if (I < 0) return 0;
    return A[I] > B[I] ? 1 : -1;
}

xnum operator+(const xnum& A, const xnum& B)
{
    xnum R;
    int I;
    int Carry = 0;
    for (I = 0; I < A.Len || I < B.Len || Carry > 0; I++)
    {
        if (I < A.Len) Carry += A[I];
        if (I < B.Len) Carry += B[I];
        R[I] = Carry % Base;
        Carry /= Base;
    }
    R.Len = I;
    return R;
}

xnum operator-(const xnum& A, const xnum& B)
{
    xnum R;
    int Carry = 0;
    R.Len = A.Len;
    int I;
    for (I = 0; I < R.Len; I++)
    {
        R[I] = A[I] - Carry;
        if (I < B.Len) R[I] -= B[I];
        if (R[I] < 0) Carry = 1, R[I] += Base;
        else Carry = 0;
    }
    while (R.Len > 0 && R[R.Len - 1] == 0) R.Len--;
    return R;
}

xnum operator*(const xnum& A, const int B)
{
    int I;
    if (B == 0) return 0;
    xnum R;
    hugeint Carry = 0;
    for (I = 0; I < A.Len || Carry > 0; I++)
    {
        if (I < A.Len) Carry += hugeint(A[I]) * B;
        R[I] = Carry % Base;
        Carry /= Base;
    }
    R.Len = I;
    return R;
}

xnum operator*(const xnum& A, const xnum& B)
{
    int I;
    if (B.Len == 0) return 0;
    xnum R;
    for (I = 0; I < A.Len; I++)
    {
        hugeint Carry = 0;
        for (int J = 0; J < B.Len || Carry > 0; J++)
        {
            if (J < B.Len) Carry += hugeint(A[I]) * B[J];
            if (I + J < R.Len) Carry += R[I + J];
            if (I + J >= R.Len) R[R.Len++] = Carry % Base;
            else R[I + J] = Carry % Base;
            Carry /= Base;
        }   
    }
    return R;
}

xnum operator/(const xnum& A, const int B)
{
    xnum R;
    int I;
    hugeint C = 0;
    for (I = A.Len - 1; I >= 0; I--)
    {
        C = C * Base + A[I];
        R[I] = C / B;
        C %= B;
    }
    R.Len = A.Len;
    while (R.Len > 0 && R[R.Len - 1] == 0) R.Len--;
    return R;
}

//div
xnum operator/(const xnum& A, const xnum& B)
{
    int I;
    xnum R, Carry = 0;
    int Left, Right, Mid;
    for (I = A.Len - 1; I >= 0; I--)
    {
        Carry = Carry * Base + A[I];
        Left = 0;
        Right = Base - 1;
        while (Left < Right)
        {
            Mid = (Left + Right + 1) / 2;
            if (compare(B * Mid, Carry) <= 0) Left = Mid;
            else Right = Mid - 1;
        }
        R[I] = Left;
        Carry = Carry - B * Left;
    }
    R.Len = A.Len;
    while (R.Len > 0 && R[R.Len - 1] == 0) R.Len--;
    return R;
}

//mod
xnum operator%(const xnum& A, const xnum& B)
{
    int I;
    xnum R, Carry = 0;
    int Left, Right, Mid;
    for (I = A.Len - 1; I >= 0; I--)
    {
        Carry = Carry * Base + A[I];
        Left = 0;
        Right = Base - 1;
        while (Left < Right)
        {
            Mid = (Left + Right + 1) / 2;
            if (compare(B * Mid, Carry) <= 0) Left = Mid;
            else Right = Mid - 1;
        }
        R[I] = Left;
        Carry = Carry - B * Left;
    }
    R.Len = A.Len;
    while (R.Len > 0 && R[R.Len - 1] == 0) R.Len--;
    return Carry;
}

istream& operator>>(istream& In, xnum& V)
{
    char Ch;
    for (V = 0; In >> Ch;)
    {
        V = V * 10 + (Ch - '0');
        if (cin.peek() <= ' ') break;
    }
    return In;
}

ostream& operator<<(ostream& Out, const xnum& V)
{
    int I;
    Out << (V.Len == 0 ? 0 : V[V.Len - 1]);
    for (I = V.Len - 2; I >= 0; I--) 
        for (int J = Base / 10; J > 0; J /= 10) 
            Out << V[I] / J % 10;
        return Out;
}

xnum gcd(xnum a,xnum b) {
    if(!compare(b, 0)) {
		return a;
	}
    else {
    	return gcd(b, a % b);
	}
}

xnum combNumber(int n,int m) {
    int i;
    xnum sum = 1;

    for(i = n; i >= n-m+1; i --)
        sum = sum*i;
    for(i = 1; i <= m; i ++)
        sum = sum/i;

    return sum;
}


class fraction {
private:
	int s;   //short for symbol
    xnum u;
    xnum d;

public:
    fraction() : s(1), u(0), d(1) {
	}
    fraction(int n, ULL up, ULL down) : s(n), u(up), d(down) {
    	int us = up >= 0 ? 1 : -1;
    	int ds = down >= 0 ? 1 : -1;
    	// 1.ȷ������λȫ���ŵ� s �� 
    	n = up * down * n;
    	
    	// 2.ȷ�� u �� d ��Ϊ���� 
    	if(us == -1) {
    		u = xnum(-up);
		}
		if(ds == -1) {
			d = xnum(-down);
		}
		
		normalize();
	}
	fraction(int n, xnum up, xnum down) : 
		s(n), u(up), d(down) {
		normalize();
		// �κμ�����̣�xnum ȷ��һ�������� 
	}
	
    fraction operator+(const fraction&) const;
    fraction operator-(const fraction&) const;
    fraction operator*(const fraction&) const;
    fraction operator/(const fraction&) const;
    fraction reciprocal() const;
    fraction opposite() const; 
    void normalize();
    
    int Compare(const fraction& ) const;
    bool IsZero() const;
    void Print();

};

bool fraction::IsZero() const {
    return (u.Len == 0);
}

void fraction::normalize() {
	// 1. ����Ӻͷ�ĸ�� gcd 
	xnum val = gcd(u, d);
	// 2. ���ӷ�ĸ��ͬ���� gcd 
	u = u / val;
	d = d / val;
	// 3. ȷ����ĸ����Ϊ0 
    if( compare(d,0) == 0 ) d = xnum(1);
    // 4. ����� 0������λ��λ 1��
	if(IsZero()) {
		s = 1;
	}
}

fraction fraction::opposite() const {
	// 1. ֱ�ӷ���λȡ������ 
	return fraction(-s, u, d);
}

fraction fraction::reciprocal() const {
	// 1. ֱ�ӷ��ӷ�ĸ�������� 
	return fraction(s, d, u);
}

fraction fraction::operator + (const fraction& o) const {
    // 1. �ж���ӵ����������Ƿ�ͬ�� 
	if(s * o.s == 1) {
    	return fraction(s, u * o.d + d * o.u, d * o.d);
	}else {
		// 2. �ȽϷ��Ӵ�С����������λ 
		xnum lup = u * o.d;
		xnum rup = d * o.u;
		if(compare(lup, rup) >= 0) {
			return fraction(s, lup - rup, d * o.d);
		}else {
			return fraction(-s, rup - lup, d * o.d);
		}
	} 
}

fraction fraction::operator-(const fraction& o) const {
    // 1. ȡ�������෴�� 
    // 2. ʵ�ּӷ� 
    return (*this) + o.opposite();
}

fraction fraction::operator*(const fraction& o) const {
    // 1. ����λ���
	// 2. �������
	// 3. ��ĸ��� 
	return fraction(s * o.s, u * o.u, d * o.d);
}


fraction fraction::operator/(const fraction& o) const {
    // 1. ȡ�����ĵ���
    // 2. ʵ�ֳ˷�
	return (*this) * o.reciprocal();
}

int fraction::Compare(const fraction& o) const {
	// 1. �ȽϷ���λ 
	if(s == 1 && o.s == -1) {
		return 1;
	}else if(s == 0 && o.s == 1) {
		return -1;
	}
	// 2. ����λΪ���������Ƚϣ�����ȡ��
	return s * compare(u * o.d, o.u * d);
}

void fraction::Print() {
	// 1.�������������λ 
    if(s == -1)
        printf("-");
    // 2.������� 
    u.print();
    // 3.��ĸ�������1����� 
    if( !(d.Len == 1 && d.Data[0] == 1 ) ) {
        printf("/");
        d.print();
    }
    puts("");
}

