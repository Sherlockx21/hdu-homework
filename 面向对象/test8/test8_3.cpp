#include<bits/stdc++.h>
using namespace std;

template <typename T>
class DVector{
private:
  vector<T> v;
public:
  DVector(int len){
    v = vector<T> (len);
  }
  DVector(int len,T arr[]){
    for(int i = 0;i < len;i++){
      v.push_back(arr[i]);
    }
  }
  DVector operator+(const class DVector& val){
    DVector<T> vsum(val.v.size());
    for(int i = 0;i < val.v.size();i++){
      vsum.v[i] = (this->v[i] + val.v[i]);
    }
    return vsum;
  }
  T operator*(const class DVector& val){
    T mul;
    for(int i = 0;i < val.v.size();i++){
      mul += (this->v[i] * val.v[i]);
    }
    return mul*100/100;
  }
  friend ostream& operator<<(ostream& out,const class DVector& val){
    out<<"{";
    for(int i = 0;i < val.v.size();i++){
      out<<val.v[i];
      if(i != val.v.size() - 1) out<<",";
    }
    out<<"}";
    return out;
  }
};

/* 请在这里填写答案 */

int main(int argc, char** argv) {
    // 整数
    int a[6]={1,2,3,4,5,6};
    int b[6]={3,4,5,6,7,8};
    DVector<int> vecA(6,a),vecB(6,b),vecC(6);
    vecC=vecA+vecB;
    cout << vecA << "+" << vecB << "=" << vecC << endl;
    int r1=vecA*vecB;
    cout << vecA << "*" <<vecB << "=" << r1 << endl;

    // 小数
    float v1[6]={1.1,2.2,3.3,4.4,5.5,6.6};
    float v2[6]={3.3,4.4,5.5,6.6,7.7,8.8};
    DVector<float> vec1(6,v1), vec2(6,v2);
    DVector<float> vec3 = vec1 + vec2;
    cout << vec1 << "+" << vec2 << "=" << vec3 << endl;
    float r2=vec1*vec2;
    cout << vec1 << "*" << vec2 << "=" << r2 <<endl;

    return 0;
}
