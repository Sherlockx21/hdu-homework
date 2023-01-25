#ifndef COMMON_DEF
#define COMMON_DEF

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// ��̬��ϣ�����С
const int MAXH = ((1 << 25) - 1);
#define StateType long long 

// ��ͼ��С
const int MAXN = 13;

// ������Ӹ���
const int MAXBOX = 6;

// �ķ�������
const int dir[4][2] = {
    { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 }
};


enum BlockType {
    BT_EMPTY = 0,    // �յ�
    BT_WALL = 1,     // �ϰ��ǽ
    BT_BOX = 2,      // ����
    BT_TARGET = 3,   // Ŀ��λ��
    BT_MAN = 4,      // �����ӵ���
    BT_MAX
};

// ��Щ���ǿ��ַ���ռ��2���ֽڣ������ַ���ĩβ '\0'���ܹ�3���ֽ�
const char BlockSign[BT_MAX][3] = {
    "��", "��", "��", "��", "��"
};

enum VisitType {
    VT_UNVISITED = -1,
    VT_VISITED = 0,
};

#endif // !COMMON_DEF