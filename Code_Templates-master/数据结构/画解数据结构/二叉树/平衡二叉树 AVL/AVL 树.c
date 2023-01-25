#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>

#define false 0
#define true 1

typedef struct KeyValue {
    int key;
    int value;
}KeyValue;

typedef KeyValue DataType;
typedef int bool;

typedef struct TreeNode {
    DataType data;                    // (1) ����ƽ�����ļ�ֵ����������Ҫ���ܹ��Ƚϴ�С�� 
    int height;                       // (2) ���ĸ߶ȣ� 
    struct TreeNode* left, * right;    // (3) ���Һ��ӽ���ָ�룻 
}TreeNode;                            // (4) Ϊ����дһ�� struct��

TreeNode* AVLRemove(TreeNode* T, DataType data);

int Max(int a, int b) {
    return a > b ? a : b;
}

int CompareData(DataType* a, DataType* b) {
    if (a->key < b->key) {
        return -1;
    }
    else if (a->key > b->key) {
        return 1;
    }
    return 0;
}

TreeNode* AVLCreateNode(DataType data) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->data = data;
    node->height = 1;
    node->left = node->right = NULL;
    return node;
}

int AVLGetHeight(TreeNode* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

void AVLCalcHeight(TreeNode* node) {
    if (NULL == node) {
        return;
    }
    node->height = 1 + Max(AVLGetHeight(node->left), AVLGetHeight(node->right));
}

int AVLGetBalanceFactor(TreeNode* node) {
    if (node == NULL)
        return 0;
    return AVLGetHeight(node->left) - AVLGetHeight(node->right);
}


/*
  ������һ������������ T�����һ������������
*/
TreeNode* RRotate(TreeNode* T) {
    TreeNode* L = T->left;  // (1) L Ϊ T �����ӽ�㣻
    T->left = L->right;     // (2) �� L ����������Ϊ T ���������� 
    L->right = T;           // (3) �� T ��Ϊ L ����������
    AVLCalcHeight(T);       // (4) T �����ӽ������仯��������Ҫ���¼������ߣ� 
    AVLCalcHeight(L);       // (5) L �� T �ĸ���㣬T�����߱��ˣ�LҲ��Ҫ���¼��㣻 
    return L;               // (6) ��ԭ�ȵ� L ��Ϊ�µ��������أ� 
}


/*
  ������һ������������ T�����һ������������
*/
TreeNode* LRotate(TreeNode* T) {
    TreeNode* R = T->right; // (1) R ��Ϊ T ���Һ��ӽ�㣻 
    T->right = R->left;     // (2) �� R ����������Ϊ T ���������� 
    R->left = T;            // (3) �� T ��Ϊ R ���������� 
    AVLCalcHeight(T);       // (4) T ���Һ��ӽ������仯��������Ҫ���¼������ߣ� 
    AVLCalcHeight(R);       // (5) R �� T �ĸ���㣬T�����߱��ˣ�R ������Ҳ��Ҫ���¼��㣻 
    return R;               // (6) ��ԭ�ȵ� R ��Ϊ�µ��������أ� 
}

// LL �� 
TreeNode* AVLTreeLL(TreeNode* T) {
    return RRotate(T);
}

// RR �� 
TreeNode* AVLTreeRR(TreeNode* T) {
    return LRotate(T);
}

// LR �� 
TreeNode* AVLTreeLR(TreeNode* T) {
    T->left = LRotate(T->left);
    return RRotate(T);
}

// RL ��
TreeNode* AVLTreeRL(TreeNode* T) {
    T->right = RRotate(T->right);
    return LRotate(T);
}

TreeNode* AVLBalance(TreeNode* T) {
    int bf = AVLGetBalanceFactor(T);

    if (bf > +1) {
        if (AVLGetBalanceFactor(T->left) > 0)
            T = AVLTreeLL(T);                 // (1) LL ��
        else
            T = AVLTreeLR(T);                 // (2) LR ��
    }

    if (bf < -1) {
        if (AVLGetBalanceFactor(T->right) > 0)
            T = AVLTreeRL(T);                 // (3) RL ��
        else
            T = AVLTreeRR(T);                 // (4) RR ��
    }

    AVLCalcHeight(T);

    return T;                                 // (5) �Ѿ�ƽ�⣬��������� 
}

/*
  ƽ�����Ĳ��룬�����ں��������ʱ�����ƽ�⣬����������������Ҷ�ӵ���������ƽ��ģ�
*/
TreeNode* AVLInsert(TreeNode* T, DataType data) {
    int cmpResult;
    if (T == NULL) {
        T = AVLCreateNode(data);               // (1) ������������һ����㣬��ֱ������һ����㷵�ؼ��ɣ� 
        return T;
    }
    cmpResult = CompareData(&data, &T->data);
    if (cmpResult == 0) {
        return T;                              // (2) �����ֵ���ڵ�ǰ������㣬ֱ�ӷ��ص�ǰ�������൱��û��ִ�в��룻 
    }
    else if (cmpResult < 0) {
        T->left = AVLInsert(T->left, data);    // (3) �����������룻 
    }
    else {
        T->right = AVLInsert(T->right, data);  // (4) �����������룻 
    }
    return AVLBalance(T);                      // (5) ƽ���Ե����� 
}

/*
  ƽ�����Ĳ��ң����ڲ��ҹ��̲��ı�������̬�����Բ���Ҫִ��ƽ�������
*/
bool AVLFind(TreeNode* T, DataType data) {
    int cmpResult;
    if (T == NULL) {
        return false;
    }
    cmpResult = CompareData(&data, &T->data);
    if (cmpResult < 0) {
        return AVLFind(T->left, data);
    }
    else if (cmpResult > 0) {
        return AVLFind(T->right, data);
    }
    return true;
}

TreeNode* AVLGetMin(TreeNode* T) {
    while (T && T->left) {
        T = T->left;
    }
    return T;
}

TreeNode* AVLGetMax(TreeNode* T) {
    while (T && T->right) {
        T = T->right;
    }
    return T;
}

/*
    �Ƴ� T �ĸ���㣬���ұ�������ƽ���ԣ�
*/
TreeNode* AVLRemoveRoot(TreeNode* T) {

    TreeNode* retNode;
    if (T == NULL) {
        return NULL;
    }
    if (!T->left && !T->right) {        // (1) Ҷ�ӽ�㣬��ֱ��ɾ����ɾ���󷵻ؿ����� 
        free(T);
        return NULL;
    }
    else if (T->left && !T->right) {   // (2) ֻ���������������ɾ������������������ 
        retNode = T->left;
        free(T);
        return retNode;
    }
    else if (!T->left && T->right) {   // (3) ֻ���������������ɾ������������������ 
        retNode = T->right;
        free(T);
        return retNode;
    }

    if (AVLGetHeight(T->left) > AVLGetHeight(T->right)) {  // (4) ���������أ����������ѡ�����ֵ�滻����㣬���ҵݹ�ɾ����������Ӧ��㣻
        T->data = AVLGetMax(T->left)->data;
        T->left = AVLRemove(T->left, T->data);
    }else {                                                // (5) ���������أ����������ѡ����Сֵ�滻����㣬���ҵݹ�ɾ����������Ӧ��㣻         
        T->data = AVLGetMin(T->right)->data;
        T->right = AVLRemove(T->right, T->data);
    }
    AVLCalcHeight(T);
    return T;
}

TreeNode* AVLRemove(TreeNode* T, DataType data) {
    int cmpResult;
    if (T == NULL) {
        return NULL;
    }
    cmpResult = CompareData(&data, &T->data);
    if (cmpResult == 0) {
        return AVLRemoveRoot(T);
    }else if (cmpResult < 0) {
        T->left = AVLRemove(T->left, data);
    }
    else if (cmpResult > 0) {
        T->right = AVLRemove(T->right, data);
    }
    return AVLBalance(T);
}



void AVLDestroy(TreeNode* T) {
    if (T == NULL) {
        return;
    }
    AVLDestroy(T->left);
    AVLDestroy(T->right);
    free(T);
}
