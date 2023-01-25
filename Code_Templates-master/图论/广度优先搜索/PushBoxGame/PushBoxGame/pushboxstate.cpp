#include "pushboxstate.h"



int PushBoxState::base_ = 0;

void PushBoxState::setBase(int b)
{
    PushBoxState::base_ = b;
}

int PushBoxState::getBase()
{
    return base_;
}

PushBoxState::PushBoxState()
{

}

PushBoxState::~PushBoxState()
{

}

// ���ݴ���λ�ã�����״̬
StateType PushBoxState::Serialize(int man, int boxcnt, int box[MAXBOX])
{
    setManCode(man);
    boxcnt_ = boxcnt;
    for (int i = 0; i < boxcnt_; ++i) {
        box_[i] = box[i];
    }
    calcState(true);
    return state_;
}

// ����״̬������λ��
void PushBoxState::DeSerialize(StateType state)
{
    state_ = state;
    boxstate_ = state_ / getBase();

    calcManCode();
    calcBoxCode();
}


StateType PushBoxState::getBoxState()
{
    return boxstate_;
}

StateType PushBoxState::getState()
{
    return state_;
}

void PushBoxState::setManCode(int val)
{
    man_ = val;
    calcState(false);
}

int PushBoxState::getManCode()
{
    return man_;
}

void PushBoxState::setBoxCode(int idx, int val)
{
    box_[idx] = val;
    calcState(true);
}

int PushBoxState::getBoxCode(int idx)
{
    return box_[idx];
}

int PushBoxState::getBoxCount()
{
    return boxcnt_;
}

int PushBoxState::getMatchBoxIndex(int id)
{
    // ��� id ������һ�������ϣ��򷵻ؾ����±꣬���򷵻� -1
    for (int i = 0; i < boxcnt_; ++i) {
        if (id == box_[i]) {
            return i;
        }
    }
    return -1;
}

// ��Ҫͨ�� box_[] �� man_
// ����� boxstate_ �� state_
void PushBoxState::calcState(bool bReCalcBox)
{
    if (bReCalcBox)
    {
        // ��Ϊ�漰����������ֻ�ܿ���һ�ݳ������������������˵���޸Ĵ��ε�ֵ
        int boxcopy[MAXBOX];
        for (int i = 0; i < boxcnt_; ++i) {
            boxcopy[i] = box_[i];
        }

        boxstate_ = 0;
        // ��С������
        sort(boxcopy, boxcopy + boxcnt_);
        for (int i = 0; i < boxcnt_; ++i) {
            boxstate_ = boxstate_ * (StateType)getBase() + (StateType)boxcopy[i];
        }
    }
    state_ = boxstate_ * (StateType)getBase() + man_;
}

// ���� man �� state �ж�Ӧλ��ֵ
void PushBoxState::calcManCode()
{
    man_ = state_ % getBase();
}

// ���� box[] �� state �ж�Ӧλ��ֵ
void PushBoxState::calcBoxCode()
{
    boxcnt_ = 0;
    int bs = boxstate_;
    while (bs) {
        box_[boxcnt_++] = bs % getBase();
        bs /= getBase();
    }
}
