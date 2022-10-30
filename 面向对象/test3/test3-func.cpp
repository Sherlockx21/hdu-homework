
#include <iostream>
using namespace std;
class Int_Queue{
private:
    int _back; //back是队尾元素对应的下标
    int _front; //front是对头元素对应下标加1
    int _size;    //_size表示当前队列中有几个元素
    int *nums;  //nums用于存储元素
    int nums_size; //nums_size表示nums数组的长度
public:
    Int_Queue():_back(0),_front(0),_size(0),nums(NULL),nums_size(0){

    }
    ~Int_Queue(){
        delete[] nums;
    }
    bool empty() const;
    int size() const;
    int front() const;
    int back() const;
    void push(int val);
    void pop();
};

#include<queue>
deque<int> que;
/* 请在这里填写答案 */
bool Int_Queue::empty() const{
  return que.empty();
}

int Int_Queue::size() const{
  return que.size();
}

int Int_Queue::front() const{
  return que.front();
}

int Int_Queue::back() const{
  return que.back();
}

void Int_Queue::push(int val){
  que.push_front(val);
}

void Int_Queue::pop(){
  que.pop_front();
}

int main(int argc, char** argv) {
    Int_Queue q;
    if(q.empty()) cout<<"empty"<<endl;
    else cout<<q.size()<<endl;
    // cout<<"插入元素1后队列的状态:"<<endl;
    q.push(1);
    cout<< q.front()<<" "<<q.back()<<endl;

    /////////////////////////
    // cout<<"插入元素2,3,4,5后队列的状态:"<<endl;
    for(int i=2;i<=5;i++){
        q.push(i);
    }
    if(q.empty()) cout<<"empty"<<endl;
    else cout<<q.size()<<endl;
    cout<<q.front()<<" "<<q.back()<<endl;

    //////////////////////////
    // cout<<"调用2次pop函数后队列的状态:"<<endl;
    for(int i=1;i<=2;i++){
        q.pop();
    }
    if(q.empty()) cout<<"empty"<<endl;
    else cout<<q.size()<<endl;
    cout<<q.front()<<" "<<q.back()<<endl;
    return 0;
}
