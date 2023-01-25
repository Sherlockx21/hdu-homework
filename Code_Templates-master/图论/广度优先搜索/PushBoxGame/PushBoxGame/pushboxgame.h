#include "commondef.h"
#include "hash.h"
#include "path.h"
#include "pushboxstate.h"

// ��������Ϸ
// �޶���
//  1. ��ͼ��С������ MAXN X MAXN
//  2. ���������� MAXBOX
//  3. Ŀ��λ�ñ��� �� ������ƥ��
//  4. �����ϸ���1��"С��"

class PushBoxGame {

public:
    PushBoxGame();
    virtual ~PushBoxGame();
    bool read(const char *filename);
    void output();
    void genId();
    bool search();
    void render();
    
private:
    
    void fakeProgress(const char *tips);
    BlockType convertCharToBlockType(char chigh, char clow);
    bool isBlockValid();
    bool isInBound(int r, int c);
    bool isInWall(int r, int c);
    bool isObstacle(int r, int c);

    void genId_dfs(int r, int c);
    void genId_floodfill();
    void genId_genTerr();
    
    StateType getInitState();
    StateType getFinalBoxState();


    void bfs_initialize();
    void bfs_checkAndExtendState(queue<int>& Q, int preState, PushBoxState& pbs);
    bool bfs();

private:
    // �ؿ����
    int row_, col_;                   // ��Ϸ�ؿ��к���
    BlockType blocks_[MAXN][MAXN];    // ��Ϸ�ؿ���ͼ

    // �������
    int id_[MAXN][MAXN];              // �ؿ����ӱ�ţ�idCount_Ϊ�����ᵽ�� K
    int idrow_[MAXN*MAXN];            // id �з���
    int idcol_[MAXN*MAXN];            // id �з���

    // �������
    Path path_;                       // ·��������
    Hash hash_;                       // ���״̬��hash��
    int finalState_;                   // ����������״̬
};