#include<bits/stdc++.h>
using namespace std;

class MyException:public exception{
  string m_errMsg;
public:
  MyException(string errMsg,int len1,int len2):m_errMsg(errMsg){
    stringstream stream1;
    stream1<<len1;
    string str1;
    stream1>>str1;
    m_errMsg += "[" + str1 + "]-";
    stringstream stream2;
    stream2<<len2;
    string str2;
    stream2>>str2;
    m_errMsg += "[" + str2 + "]";
  }
  const char* what() const noexcept{
    return m_errMsg.c_str();
  }
};

template <typename T>
class DVector{
private:
  vector<T> v;
  int len;
public:
  DVector(int _len,T _v[]){
    len = _len;
    for(int i = 0;i < _len;i++){
      v.push_back(_v[i]);
    }
  }
  DVector(int _len){
    len = _len;
    v = vector<int>(len);
  }
  DVector operator+ (const class DVector& val) const{
    DVector ans = *this;
    if (this->len != val.len) throw MyException("NOT same length: ",this->len,val.len);
    for(int i = 0;i < val.len;i++){
      ans.v[i] = this->v[i] + val.v[i];
    }
    ans.len = val.len;
    return ans;
  }
  double operator* (const class DVector& val) const{
    if (this->len != val.len) throw MyException("NOT same length: ",this->len,val.len);
    double ans;
    ans = 0;
    for(int i = 0;i < val.len;i++){
      ans = double(this->v[i] * val.v[i]) + ans;
    }
    return ans;
  }
  friend ostream& operator<<(ostream& out,const class DVector& val){
    out<<"{";
    for(int i = 0;i < val.len;i++){
      out<<val.v[i];
      if(i != val.len - 1) out<<",";
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

    try{
        float e1[]={2.2,3.3,4.4,5.5,6.6};
        float e2[]={3.3,4.4,5.5,6.6,7.7,8.8};
        DVector<float> dv1(5,v1), dv2(6,v2);
        DVector<float> dv3 = dv1 + dv2;
    }
    catch(MyException &ex){
        cout << ex.what() << endl;
    }

    return 0;
}
