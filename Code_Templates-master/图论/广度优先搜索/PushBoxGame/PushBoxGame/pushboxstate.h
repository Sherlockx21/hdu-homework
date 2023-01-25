#ifndef PUSHBOXSTATE_H
#define PUSHBOXSTATE_H

#include "commondef.h"

// ע�⣺״̬�����ʱ��Ϊ���ý����ʱ���ܹ�׼ȷ����ж��ٸ����ӣ�����λ Ϊ������ 0
class PushBoxState {
public:
    static void setBase(int b);
    static int getBase();

    PushBoxState();
    virtual ~PushBoxState();

    // ���ݴ���� �˺�����λ�ã�����һ������
    StateType Serialize(int man, int boxcnt, int box[MAXBOX]);

    // ���ݴ�������������Ƴ� �˺�����λ��
    void DeSerialize(StateType state);

    // ��˽�г�Ա���ʵķ�װ
    StateType getBoxState();
    StateType getState();
    void setManCode(int val);
    int getManCode();
    void setBoxCode(int idx, int val);
    int getBoxCode(int idx);
    int getBoxCount();

    // ��ȡ�Ƿ���һ��������id��
    // �еĻ������������±꣬���򷵻� -1
    int getMatchBoxIndex(int id);

private:
    void calcState(bool bReCalcBox);
    void calcManCode();
    void calcBoxCode();


private:
    int man_;
    int boxcnt_;
    int box_[MAXBOX];

    StateType boxstate_;
    StateType state_;

    static int base_;
};

#endif // !PUSHBOXSTATE_H
