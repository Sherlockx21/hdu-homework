

#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>

using namespace std;

typedef int TrieData;
typedef int AnsType;                         // �޸ĵ� 1
typedef int ValueType;                       // �޸ĵ� 2
const int MAXBIT = 32;                       // �޸ĵ� 3

const int TRIE_NODE_CACHES = MAXBIT * 100010;
const int TRIE_NODE_COUNT = 2;
const int TRIE_DATA_INIT = 0;
const int TRIE_NODE_NULL = -1;

#define samebit(i) ((v & ((ValueType)1 << i)) ? 1 : 0)
#define diffbit(i) ((v & ((ValueType)1 << i)) ? 0 : 1)


// �ֵ��������
class TrieNode {
private:
    bool isword_;                 // �Ƿ���1����������
    int num_;                     // �ж��ٸ����ξ���������
    TrieData td_;                 // ÿ������Ȩֵ��������һЩ������;
    int nodes_[TRIE_NODE_COUNT];  // ע���������ǽ���ڴ�ص��±꣬��ȴ�ָ��ĺô��ǣ��ֽ�����һ��

public:
    inline void setNode(int nodeIdx, int node) {
        nodes_[nodeIdx] = node;
    }
    inline int getNode(int nodeIdx) {
        return nodes_[nodeIdx];
    }
    inline bool hasNode(int nodeIdx) {
        // ��㷶Χ�ж�
        if (nodeIdx < 0 || nodeIdx >= TRIE_NODE_COUNT) {
            return false;
        }
        return nodes_[nodeIdx] != TRIE_NODE_NULL;
    }
    inline void reset() {
        resetData();
        memset(nodes_, TRIE_NODE_NULL, sizeof(nodes_));
    }
    inline void resetData(){
        num_ = 0;
        isword_ = false;
        td_ = TRIE_DATA_INIT;
    }
    inline void addNum(int d) {
        num_ += d;
    }
    inline int  getNum() {
        return num_;
    }
    inline void setTrieData(TrieData v){
        if (td_ == TRIE_DATA_INIT)
            td_ = v;
    }
    inline TrieData  getTrieData() {
        return td_;
    }
    inline void setWord(bool isw) {
        isword_ = isw;
    }
    inline bool isWord(){
        return isword_;
    }
};


// �ֵ�����
class TrieTree {
public:
    TrieTree(int nodeCacheCount = TRIE_NODE_CACHES);
    virtual ~TrieTree();
    void initialize() {
        nodeId_ = 0;
        root_ = genNode();
    }

public:
    TrieNode *root() const { return node(root_); }
    TrieNode *node(int idx) const { return &(nodes_[idx]); }

    // ���� 1 ��ֵΪ v ����
    virtual void insert_value(ValueType v);
    // ɾ�� 1 ��ֵΪ v ����
    virtual void delete_value(ValueType v);
    // ��ѯֵΪ v �����ĸ���
    virtual TrieData query_value(ValueType v);
    // ��ѯ�ֵ����к͸�����ֵ XOR �������Ǹ���
    virtual void query_xor_max(ValueType v, AnsType &ans);
private:
    int genNode() {
        TrieNode *pkNode = &(nodes_[nodeId_]);
        pkNode->reset();
        return nodeId_++;
    }

    bool hasNode(TrieNode *pkNow, int nodeIdx) {
        if (pkNow->hasNode(nodeIdx)) {
            TrieNode *pkNode = node(pkNow->getNode(nodeIdx));
            if (pkNode->getNum() > 0) {
                return true;
            }
        }
        return false;
    }

    void checkNode(TrieNode *pkNow, int nodeIdx) {
        if (!pkNow->hasNode(nodeIdx)) {
            pkNow->setNode(nodeIdx, genNode());
        }
    }
private:
    int nodeId_;
    int root_;
    TrieNode *nodes_;
};

TrieTree::TrieTree(int nodeCacheCount) : nodes_(NULL), root_(0), nodeId_(0) {
    nodes_ = new TrieNode[nodeCacheCount];
}

TrieTree::~TrieTree() {
    if (nodes_) {
        delete[] nodes_;
    }
}

// �����λ��ʼ���� 01�ֵ���
void TrieTree::insert_value(ValueType v) {
    TrieNode *pkNow = root();
    for (int i = MAXBIT - 1; i >= 0; --i) {
        int nodeIdx = samebit(i);
        checkNode(pkNow, nodeIdx);
        pkNow = node(pkNow->getNode(nodeIdx));
        pkNow->addNum(1);
    }
}

// ��ѯ 01�ֵ��� �� v ���ֳ��ֵĸ���
TrieData TrieTree::query_value(ValueType v) {
    TrieNode *pkNow = root();
    for (int i = MAXBIT - 1; i >= 0; --i) {
        int nodeIdx = samebit(i);
        if (!hasNode(pkNow, nodeIdx)) {
            return 0;
        }
        pkNow = node(pkNow->getNode(nodeIdx));
    }
    return pkNow->getNum();
}

// �����λ��ʼ���� ɾ�� 01�ֵ��� �� v ����һ�� 
void TrieTree::delete_value(ValueType v) {
    TrieData cnt = query_value(v);
    if (cnt == 0) {
        return;
    }
    TrieNode *pkNow = root();
    for (int i = MAXBIT - 1; i >= 0; --i) {
        int nodeIdx = samebit(i);
        pkNow = node(pkNow->getNode(nodeIdx));
        pkNow->addNum(-1);
    }
}

// �Ӹ���㿪ʼ�� 32 ��
// �����������ʣ������Һ͵�ǰ���ĵ�iλ�෴����������Ҳ���������ͬ�ģ�
void TrieTree::query_xor_max(ValueType v, AnsType &ans) {
    TrieNode *pkNow = root();
    ans = 0;
    for (int i = MAXBIT - 1; i >= 0; --i) {
        int nodeIdx = diffbit(i);
        if (hasNode(pkNow, nodeIdx)) {
            ans |= ((ValueType)1 << i);
        }
        else {
            nodeIdx = 1 - nodeIdx;
        }
        pkNow = node(pkNow->getNode(nodeIdx));
    }
}
