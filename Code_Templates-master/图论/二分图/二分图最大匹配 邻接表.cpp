#include <iostream>
#include <cstring>

using namespace std;

//****** ����ͼ���ƥ��ģ��(�ڽӱ�) ******
// ���㷶Χ  ��ߵĵ�[1, X]���ұߵĵ�[1,Y]

const int BGMAX = 510;

class BipartiteGraph {
public:
    BipartiteGraph();
    virtual ~BipartiteGraph();

    void initialize(int lefts, int rights);
    void addEdge(int u, int v);

    int getMaxMatch();
private:
    bool findMatch(int u);       // �������㷨������·
private:
    int leftsize_, rightsize_;   // ���ҵ㼯����Ŀ
    int *adj[BGMAX];             // �ڽӱ�
    int adjsize_[BGMAX];         // �ڽӱ��size
    int pre_[BGMAX];             // �������㷨������·ʱ�� pre
    bool visit_[BGMAX];          // �������㷨������·ʱ�� visit
};

BipartiteGraph::BipartiteGraph() :
leftsize_(0), rightsize_(0)
{
    for (int i = 1; i < BGMAX; ++i) {
        adj[i] = new int[BGMAX];
    }
}

BipartiteGraph::~BipartiteGraph() {
    for (int i = 1; i < BGMAX; ++i) {
        delete[] adj[i];
        adj[i] = NULL;
    }
}

bool BipartiteGraph::findMatch(int u) {
    // u -> v
    for (int i = 0; i < adjsize_[u]; ++i) {
        int v = adj[u][i];
        if (!visit_[v]) {
            visit_[v] = true;
            int vpre = pre_[v];
            pre_[v] = u;
            if (vpre == -1 || findMatch(vpre)) {
                return true;
            }
            pre_[v] = vpre;
        }
    }
    return false;
}

void BipartiteGraph::initialize(int lefts, int rights) {
    leftsize_ = lefts;
    rightsize_ = rights;
    memset(pre_, -1, sizeof(pre_));
    memset(adjsize_, 0, sizeof(adjsize_));
}


void BipartiteGraph::addEdge(int u, int v) {
    adj[u][adjsize_[u]++] = v;
}

int BipartiteGraph::getMaxMatch() {
    int cnt = 0;
    for (int i = 1; i <= leftsize_; ++i) {
        memset(visit_, false, sizeof(visit_));
        if (findMatch(i)) {
            ++cnt;
        }
    }
    return cnt;
}
//****** ����ͼ���ƥ��ģ��(�ڽӱ�) ******