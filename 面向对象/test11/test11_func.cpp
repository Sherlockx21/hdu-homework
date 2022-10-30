#include<bits/stdc++.h>
using namespace std;

class Apple{
private:
  float weight;
  string brand;
  float sweet;
public:
  Apple(){}
  Apple(string _brand,float _weight,float _sweet){
    brand = _brand;
    weight = _weight;
    sweet = _sweet;
  }
  string Getbrand() const{
    return brand;
  }
  float Getweight() const{
    return weight;
  }
  float Getsweet() const{
    return sweet;
  }
  friend istream& operator>>(istream& in,Apple& val){
    in>>val.brand>>val.weight>>val.sweet;
    return in;
  }
  friend ostream& operator<<(ostream& out,const class Apple& val){
    out<<val.brand<<" "<<val.weight<<" "<<val.sweet;
    return out;
  }
  bool operator<(const Apple &val) const{
    return this->weight < val.weight;
  }
};

void printContainer(vector<Apple> a,string insertstr){
  for(unsigned int i = 0;i < a.size();i++){
    cout<<a[i]<<insertstr;
  }
}

class compAppleByBrand{
public:
  bool operator()(const Apple &a,const Apple &b) const{
    if(a.Getbrand() < b.Getbrand()) return true;
    else return false;
  }
  bool compare(const Apple &val,string cond) const{
    if(val.Getbrand() > cond) return true;
    else return false;
  }
};
class compAppleBySweet{
public:
  bool operator()(const Apple &a,const Apple &b) const{
    if(a.Getsweet() < b.Getsweet()) return true;
    else return false;
  }
  bool compare(const Apple &val,float cond) const{
    if(val.Getsweet() > cond) return true;
    else return false;
  }
};
class compAppleByWeight{
public:
  bool operator()(const Apple &a,const Apple &b) const{
    if(a.Getweight() < b.Getweight()) return true;
    else return false;
  }
  bool compare(const Apple &val,float cond) const{
    if(val.Getweight() > cond) return true;
    else return false;
  }
};


template<typename inputContainer, typename outputContainer, typename binaryCompT, typename condT>
class Classifier{
public:
// 通过comparer比较器，将符合cond条件的对象，从容器source拷贝到容器destination;
  void Classify(inputContainer &source, outputContainer &destination, binaryCompT comparer, condT cond){
    //sort(source.begin(),source.end(),comparer);
    for(int i = 0;i < source.size();i++){
      if(comparer.compare(source[i],cond)) destination.push_back(source[i]);
    }
  }
};

/* 请在这里填写答案 */

int main(int argc, char** argv)
{
    int n;
    cin >> n;
    vector<Apple> box(n);
   // 输入n个苹果信息
    for(int i=0;i<n;i++){
        cin>>box[i];
    }
    //    调动sort()算法进行排序
    cout << "sort by default:" << endl;
    sort(box.begin(), box.end());  // 按照默认比较规则排序：按苹果重量
    printContainer(box, "\n");      // 输出容器box内的所有苹果；每个苹果占一行；

    cout << "sort by brand:" << endl;
    sort(box.begin(), box.end(), compAppleByBrand());  // 根据品牌排序
    printContainer(box, "\n");

    cout << "sort by weight:" << endl;
    sort(box.begin(), box.end(), compAppleByWeight());  // 根据重量排序
    printContainer(box, "\n");

    cout << "sort by sweet:" << endl;
    sort(box.begin(), box.end(), compAppleBySweet());  // 根据甜度排序
    printContainer(box, "\n");

    // 使用分类器将box内的苹果分别分类到box2（品质二等：甜度大于9）
    vector<Apple> box2;
    Classifier<vector<Apple>, vector<Apple>, compAppleBySweet, float> classfier1;
    classfier1.Classify(box, box2, compAppleBySweet(), 9.0);
    cout << "Level 2:" << endl;
    printContainer(box2, "\n");

    // 使用分类器将box内的苹果分别分类到box1（品质一等：二等苹果里重量大于50克）
    vector<Apple> box1;
    Classifier<vector<Apple>, vector<Apple>, compAppleByWeight, float> classfier2;
    classfier2.Classify(box2, box1, compAppleByWeight(), 50.0);
    cout << "Level 1:" << endl;
    printContainer(box1, "\n");

}
