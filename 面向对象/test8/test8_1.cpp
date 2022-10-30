#include<bits/stdc++.h>
using namespace std;

class Apple{
public:
  string name;
  int weight;
  int level;
  Apple();
  Apple(string _name,int _weight,int _level){
    name = _name;
    weight = _weight;
    level = _level;
  }
  bool operator>(const class Apple& val) const{
    if(this->level > val.level) return true;
    else if(this->level == val.level){
      return (this->weight > val.weight);
    }
    return false;
  }
  friend ostream& operator<<(ostream& out,const class Apple& val){
    out<<val.name<<" "<<val.weight<<" "<<val.level;
    return out;
  }
};

template<typename T>
void TSort(T a[],int n){
  for(int i = 0;i < n;i++){
    for(int j = i + 1;j < n;j++){
      if(a[i] > a[j])
        swap(a[i],a[j]);
    }
  }
}

template<typename T>
void TShow(T a[],int n){
  for(int i = 0;i < n;i++){
    cout<<a[i]<<endl;
  }
}

int main(){
    int arr1[10] = {10, 22, 29, 18, 27, 12, 21, 23, 82, 93};
    string arr2[10] = {"hello", "world", "nice", "book", "to", "see", "you", "very", "good", "excel"};

    // 排序整数数组
    TSort(arr1, 10);
    TShow(arr1, 10);
    cout << endl;

    // 排序字符串数组
    TSort(arr2, 10);
    TShow(arr2, 10);

    // Apple苹果类有三个属性:产地, 重量, 品质等级
    Apple arr3[10] = {
            {"HZ", 50, 1},
            {"GZ", 60, 2},
            {"HZ", 58, 1},
            {"FJ", 61, 2},
            {"XJ", 70, 3},
            {"NJ", 57, 1},
            {"SX", 48, 1},
            {"NT", 63, 2},
            {"JN", 66, 2},
            {"TZ", 52, 1}
    };

    // 排序苹果数组
    TSort(arr3, 10);    // 按重量排序
    TShow(arr3, 10);    // 一行输出一个苹果信息
}
