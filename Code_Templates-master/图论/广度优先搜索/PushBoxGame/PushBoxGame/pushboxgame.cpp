#include <iostream>
#include <cstring>
#include <algorithm>
#include <windows.h>

#include "pushboxstate.h"
#include "pushboxgame.h"

PushBoxGame::PushBoxGame() : row_(0), col_(0) {
}

PushBoxGame::~PushBoxGame() {
}

bool PushBoxGame::read(const char *filename) {
    char strtmp[1000];
    //printf("��������Ϸ�ߴ磨�к��У�:\n");

    freopen(filename, "r", stdin);

    scanf("%d %d", &row_, &col_);
    getchar();
    //printf("������ (%d�� X %d��) �ĵ�ͼ:\n", row_, col_);
    //printf("���յ�, ��ǽ, ������, ��Ŀ��λ��, ����\n");

    memset(blocks_, 0, sizeof(blocks_));
    for (int i = 0; i < row_; ++i) {
        gets(strtmp);
        if (strlen(strtmp) != 2 * col_) {
            puts(strtmp);
            break;
        }
        for (int j = 0; j < col_; ++j) {
            blocks_[i][j] = convertCharToBlockType(strtmp[2 * j], strtmp[2 * j + 1]);
        }
    }

    fclose(stdin);
    freopen("CON", "r", stdin);

    if (!isBlockValid()) {
        printf("�������ݴ������������������룬��֤�����������㣺\n");
        printf("    1. ��ͼ��С��� %d X %d\n", MAXN, MAXN);
        printf("    2. ���������� %d\n", MAXBOX);
        printf("    3. Ŀ��λ�ñ��� �� ������ƥ��\n");
        printf("    4. �����ϸ���һ�� 'С��'\n");
        puts("");
        return false;
    }
    return true;
}

bool PushBoxGame::search() {
    fakeProgress("·��������");
    return bfs();
}

void PushBoxGame::output() {
    for (int i = 0; i < row_; ++i) {
        for (int j = 0; j < col_; ++j) {
            printf("%s", BlockSign[blocks_[i][j]]);
        }
        puts("");
    }
}


void PushBoxGame::fakeProgress(const char *tips)
{
    printf("%s", tips);
    for (int i = 0; i < 7; ++i) {
        Sleep(150);
        printf(".");
    }
    puts("");
}

BlockType PushBoxGame::convertCharToBlockType(char chigh, char clow) {
    BlockType tp = BlockType::BT_EMPTY;
    for (int i = BlockType::BT_EMPTY; i < BlockType::BT_MAX; ++i) {
        if (BlockSign[i][0] == chigh && BlockSign[i][1] == clow) {
            tp = (BlockType)i;
            break;
        }
    }
    return tp;
}

bool PushBoxGame::isBlockValid() {
    // 1 ��ͼ��С��� MAXN X MAXN
    if (row_ > MAXN || col_ > MAXN) {
        return false;
    }

    int blockCnt[BT_MAX];
    memset(blockCnt, 0, sizeof(blockCnt));

    for (int i = 0; i < row_; ++i) {
        for (int j = 0; j < col_; ++j) {
            ++blockCnt[blocks_[i][j]];
        }
    }
    // 2 ���������� MAXBOX
    if (blockCnt[BlockType::BT_BOX] > MAXBOX) {
        return false;
    }

    // 3 Ŀ��λ�ñ��� �� ������ƥ��
    if (blockCnt[BlockType::BT_TARGET] != blockCnt[BlockType::BT_BOX]) {
        return false;
    }

    // 4 �����ϸ���һ�� 'С��'
    if (blockCnt[BlockType::BT_MAN] != 1) {
        return false;
    }

    return true;
}


bool PushBoxGame::isInBound(int r, int c) {
    // Խ����
    return r >= 0 && r < row_ && c >= 0 && c < col_;
}

bool PushBoxGame::isInWall(int r, int c) {
    // ǽ���ϰ����
    return blocks_[r][c] == BT_WALL;
}

// �ۺ��ϰ����
bool PushBoxGame::isObstacle(int r, int c) {
    return !isInBound(r, c) || isInWall(r, c);
}

void PushBoxGame::genId_dfs(int r, int c) {
    // 1. �ϰ����
    if (isObstacle(r, c)) {
        return;
    }
    // 2. �ظ����ʼ��
    if (id_[r][c] == VisitType::VT_VISITED) {
        return;
    }
    // 3. ��ǵ�ǰ�����ѷ���
    id_[r][c] = VisitType::VT_VISITED;

    // 4. �ݹ鴦�������ĸ�����
    for (int i = 0; i < 4; ++i) {
        genId_dfs(r + dir[i][0], c + dir[i][1]);
    }
}

void PushBoxGame::genId_floodfill() {
    // 1.��ʼ�����и���Ϊδ����
    memset(id_, VisitType::VT_UNVISITED, sizeof(id_));
    // 2.�ҵ� BT_MAN �ĸ��ӽ������ѣ���Ƿ��ʵ��ĸ���
    for (int i = 0; i < row_; ++i) {
        for (int j = 0; j < col_; ++j) {
            if (blocks_[i][j] == BT_MAN) {
                genId_dfs(i, j);
            }
        }
    }
}

void PushBoxGame::genId_genTerr() {
    fakeProgress("��������������");
    // 1. ���մ������ң��������µ�˳���������ѷ��ʸ���
    int idCount = 1;
    for (int i = 0; i < row_; ++i) {
        for (int j = 0; j < col_; ++j) {
            if (id_[i][j] == VisitType::VT_VISITED) {
                // ��� id ����ӳ��
                id_[i][j] = idCount++;

                // ��� id ����ӳ��
                idrow_[id_[i][j]] = i;
                idcol_[id_[i][j]] = j;
            }
        }
    }
    PushBoxState::setBase(idCount);
}

void PushBoxGame::genId() {
    genId_floodfill();
    genId_genTerr();
}

StateType PushBoxGame::getInitState() {
    int manValue, boxCnt = 0, boxValue[MAXBOX];
    PushBoxState pbs;

    for (int i = 0; i < row_; ++i) {
        for (int j = 0; j < col_; ++j) {
            // 1. �ҳ��˵�λ��
            if (blocks_[i][j] == BlockType::BT_MAN) {
                manValue = id_[i][j];
            }
            // 2. �ҳ��������ӵ�λ��
            else if (blocks_[i][j] == BlockType::BT_BOX) {
                boxValue[boxCnt++] = id_[i][j];
            }
        }
    }
    // 3. ��ϳ����Ӻ��˵ĳ�ʼ״̬
    return pbs.Serialize(manValue, boxCnt, boxValue);
}

StateType PushBoxGame::getFinalBoxState() {
    int manValue, boxCnt = 0, boxValue[MAXBOX];
    PushBoxState pbs;

    for (int i = 0; i < row_; ++i) {
        for (int j = 0; j < col_; ++j) {
            // 1. �ҳ����ӵ����չ�λλ��
            if (blocks_[i][j] == BlockType::BT_TARGET) {
                boxValue[boxCnt++] = id_[i][j];
            }
        }
    }
    // 2. ��ϳ����ӵ�����״̬
    pbs.Serialize(0, boxCnt, boxValue);
    return pbs.getBoxState();
}

void PushBoxGame::bfs_initialize() {
    path_.initialize();
    hash_.initialize();
}



void PushBoxGame::bfs_checkAndExtendState(queue<int>& Q, int preState, PushBoxState& pbs) {
    StateType state = pbs.getState();
    if (hash_.hasKey(state)) {
        return;
    }
    // 1. ��ϣ���
    int nowState = hash_.getKey(state);
    // 2. ����ǰ��������·������
    path_.add(nowState, preState);
    // 3. ������У�����״̬��չ
    Q.push(nowState);
}

bool PushBoxGame::bfs() {
    queue <int> Q;
    PushBoxState pbs;

    bfs_initialize();
    // ��ǰ�������ֹ״̬
    StateType finalBoxState = getFinalBoxState();
    
    // ����ʼ״̬ѹ�����
    int startState = hash_.getKey(getInitState());
    Q.push(startState);

    while (!Q.empty()) {
        int nowState = Q.front();
        Q.pop();

        // ������������ �����л� �� pbs
        pbs.DeSerialize(hash_.getValue(nowState));

        // �ҵ��⣬������״̬�־û�
        if (pbs.getBoxState() == finalBoxState) {
            finalState_ = nowState;
            return true;
        }

        // �����ĸ�������һ�񣬶���ÿ�����򣬶���3�������
        // 1. ǰ��û·����������޷���չ״̬��
        // 2. ǰ��û�����ӣ�ֱ����ǰ�ߣ���չ״̬��
        // 3. ǰ���и����ӣ��ַ����������
        //   3.1 ����ǰ���޷����ã���������޷���չ״̬��
        //   3.2 ����ǰ����Է��ã��˺�����ͬʱ���������ǰ��һ����չ״̬;
        
        int man = pbs.getManCode();

        for (int i = 0; i < 4; ++i) {
            
            int manr = idrow_[man] + dir[i][0];
            int manc = idcol_[man] + dir[i][1];

            if (isObstacle(manr, manc)) {
                // ���1
                continue;
            }

            int nextman = id_[manr][manc];

            // ģ�����ߵ������λ��
            pbs.setManCode(nextman);

            int boxIndex = pbs.getMatchBoxIndex(nextman);
            if (boxIndex == -1) {
                // ���2
                bfs_checkAndExtendState(Q, nowState, pbs);
            }
            else {
                // ���3 ���ӱ�����ǰ�ƽ�һ��
                int boxr = idrow_[nextman] + dir[i][0];
                int boxc = idcol_[nextman] + dir[i][1];

                if (isObstacle(boxr, boxc) || pbs.getMatchBoxIndex(id_[boxr][boxc]) != -1) {
                    // ���3.1
                    continue;
                }
                // ���3.2
                // ģ��������ǰ����һ��
                pbs.setBoxCode(boxIndex, id_[boxr][boxc]);
                bfs_checkAndExtendState(Q, nowState, pbs);
                // ��������
                pbs.setBoxCode(boxIndex, nextman);
            }
        }
    }
    return false;
}


void PushBoxGame::render() {
    // 1. ��������״̬����·������
    vector <int> path;
    path_.getPath(finalState_, path);

    // 2.��Ϊ�˺����ӵ�״̬�洢��״̬�ϣ�����ԭͼ�ϵ�������Ԫ�ؿ������
    for (int i = 0; i < row_; ++i) {
        for (int j = 0; j < col_; ++j) {
            if (blocks_[i][j] == BlockType::BT_BOX || blocks_[i][j] == BlockType::BT_MAN) {
                blocks_[i][j] = BlockType::BT_EMPTY;
            }
        }
    }
    PushBoxState pbs;
    BlockType blockCache[MAXN][MAXN];

    for (int i = 0; i < path.size(); ++i) {
        Sleep(120);
        system("cls");
        pbs.DeSerialize(hash_.getValue(path[i]));

        // 3.����ǰ״̬ �� �� ���� ��״̬��������
        memcpy(blockCache, blocks_, MAXN * MAXN * sizeof(BlockType));

        // 4.����ǰ״̬ �� �� ���� ������ȥ
        blocks_[idrow_[pbs.getManCode()]][idcol_[pbs.getManCode()]] = BlockType::BT_MAN;
        for (int j = 0; j < pbs.getBoxCount(); ++j) {
            int b = pbs.getBoxCode(j);
            blocks_[idrow_[b]][idcol_[b]] = BlockType::BT_BOX;
        }
        output();

        // 5.�ָ��� �� �� ���� ������ȥ ֮ǰ�����
        memcpy(blocks_, blockCache, MAXN * MAXN * sizeof(BlockType));

        if (i == 0) {
            // ��һ�ζ�ͣ��500���
            Sleep(500);
        }
    }
}
