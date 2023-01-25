#include <iostream>

using namespace std;

#define MAXN 1000010

///////////////////////��������//////////////////////////
// ������������ģ��
// �����������е� data ������ԭ������±꣬ӳ���ȥ��Ҫ��֤��Щ�� data �е�ԭ���������ǵ���������

#define MAXN 1000010
#define Type int
#define NullIndex -1

class Deque {
private:
	int* data;                  // �洢 rawdata ���±�
	Type* rawdata;              // ����Դ���ݣ������������ԱȽ�
	int head, tail;             // ����ͷβָ��
	int range;                  // ��ʾ״̬ת��ʱ������䷶Χ

	Deque() {
		data = new int[MAXN];
	}
public:
	void init(int r, Type* rd);
	void insert(int index);
	int query();
	int size();

	static Deque& instance() {
		static Deque inst;
		return inst;
	}
};


void Deque::init(int r, Type* rd) {
	head = tail = 0;
	range = r;
	rawdata = rd;
}

/* ά����һ�����������Ķ��� (data[]��������) */
// dp[i] = min{ dp[i-j] | 0 < j <= range } + C
void Deque::insert(int index) {

	// 1. ��ǰ���ݵ��±� - ����ͷ���ݵ��±� < range
	while (head < tail && index - data[head] >= range)
		++head;

	// 2. ά�������������У������Ҫ�����������У��� '>=' �ĳ� '>'��
	while (head < tail && rawdata[data[tail - 1]] >= rawdata[index])
		--tail;

	// 3. ����Ԫ��
	data[tail++] = index;
}

/* ȡ����ͷԪ�أ��������Ϊ�գ��򷵻� NullIndex */
int Deque::query() {
	if (head == tail) {
		return NullIndex;
	}
	return data[head];
}

int Deque::size() {
	return tail - head;
}