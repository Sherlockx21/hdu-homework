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
  }/*
  bool operator<(const Apple &val) const{
    return this->weight < val.weight;
  }*/
};

int main(int argc, char const *argv[]) {
  int n;
  cin>>n;
  vector<Apple> box(n),box_fitbrand,box_fitquality;
  for(int i = 0;i < n;i++){
    cin>>box[i];
  }
  string _brand;
  float _weight,_sweet;
  cin>>_brand>>_weight>>_sweet;
  copy_if(box.begin(),box.end(),inserter(box_fitbrand,box_fitbrand.begin()),[=](Apple val){
    return (val.Getbrand() == _brand);
  });
  cout<<_brand<<":"<<endl;
  for(int i = 0;i < box_fitbrand.size();i++){
    cout<<box_fitbrand[i]<<endl;
  }
  copy_if(box.begin(),box.end(),inserter(box_fitquality,box_fitquality.begin()),[=](Apple val){
    return (val.Getsweet() > _sweet && val.Getweight() > _weight);
  });
  cout<<"High quality:"<<endl;
  for(int i = 0;i < box_fitquality.size();i++){
    cout<<box_fitquality[i]<<endl;
  }
  return 0;
}
