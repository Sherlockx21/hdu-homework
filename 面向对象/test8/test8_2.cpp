#include<bits/stdc++.h>
using namespace std;

class Apple{
public:
  string area;
  int weight;
  int level;
public:
  Apple(){}
  Apple(string _area,int _weight,int _level){
    area = _area;
    weight = _weight;
    level = _level;
  }
  bool operator!=(const class Apple& val) const{
    if(this->area == val.area && this->weight == val.weight && this->level == val.level) return false;
    else return true;
  }
  friend istream& operator>>(istream& in,Apple val){
    in>>val.area>>val.weight>>val.level;
    return in;
  }
  friend ostream& operator<<(ostream& out,const class Apple& val){
    out<<val.area<<" "<<val.weight<<" "<<val.level;
    return out;
  }
};

template <typename T>
class Array{
private:
  T elem[100];
  int size;
public:
  int pos = 0;
  Array(int sz):size(sz){
  }
  ~Array(){
    //delete [] elem;
  }
  T& operator[](int i){
    if(i < 0 || i > size){
      throw "Invalid Index!";
    }
    return elem[i];
  }
  bool operator==(const class Array& val) const{
    if(this->size != val.size) return false;
    else{
      for(int i = 0;i < val.size;i++){
        if(this->elem[i] != val.elem[i]) return false;
      }
    }
    return true;
  }
  friend istream& operator>>(istream& in,Array val){
    for(int i = 0;i < val.size;i++){
      in>>val.elem[i];
    }
    return in;
  }
  friend ostream& operator<<(ostream& out,const class Array& val){
    for(int i = 0;i < val.size;i++){
      out<<val.elem[i]<<endl;
    }
    return out;
  }
  Array(const Array& copy){
    this->size = copy.size;
    for(int i = 0;i < copy.size;i++){
      this->elem[i] = copy.elem[i];
    }
  }
};


/* 请在这里填写答案 */
int main(int argc, char** argv)
{
    int n;
    cin >> n;
    Array<Apple> box1(n);

    // 输入n个苹果信息
    for(int i=0;i<n;i++){
        cin>>box1;
    }
      //  cout << box1;
    cin >> box1;   // 继续增加1个 ,Array<T>空间能自动增加

    Array<Apple> box2(box1);
    cout << box2;
    if(box1 == box2){
        cout << "YES" << endl;
    }
    else{
        cout << "NO" << endl;
    }
    Apple a1("HK", 100, 10);
    box2[0] = a1;
    cout << box2;

    return 0;
}
