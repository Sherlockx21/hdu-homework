#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
//1234567890987654321333888999666
// 147655765659657669789687967867
//1382223656647311991123576967533
//1086912125327996651544201031799
class number{
private:
    string num;
    string _normalize(string );     // 正则化, 删除数字开头的'0'
public:
    number();
    number(string _num);
    number(char c);
    number operator+(const class number& val);
    number operator-(const class number& val);
    number operator*(const class number& val);
    number operator/(const class number& val);
    number operator%(const class number& val);
    bool operator>(const class number& val) const;
    bool operator<(const class number& val) const;
    bool operator>=(const class number& val) const;
    bool operator<=(const class number& val) const;
    bool operator!=(const class number& val) const;
    bool operator==(const class number& val) const;
    number operator=(const class number& val);
    friend ostream& operator<<(ostream& out,const class number& val);
    friend istream& operator>>(istream& in, class number& val);
};

/* 请在这里填写答案 */
#include<cstring>
number::number(){
  num="";
}

number::number(string _num){
  num = _num;
}

number::number(char c){
  num = c;
}

int strComp(string &s1,string &s2)
{
    int len1=s1.length();
    int len2=s2.length();
    if(len1>len2)
    return 0;
    else if(len1<len2)
    return 1;
    else{
        if(s1>=s2)
        return 0;
        else
        return 1;
    }
}

string Sub(string s1,string s2){
  int flag = 1;
  if(strComp(s1,s2)==1){
    swap(s1,s2);
    flag = -flag;
  }
  reverse(s1.begin(),s1.end());
  reverse(s2.begin(),s2.end());
  string s(1000,'0');
  for(unsigned int i=0;i<s1.length();i++) s[i]=s1[i];
  for(unsigned int i=0;i<s2.length();i++){
    if(s[i]>=s2[i])
      s[i]=s[i]-'0'-(s2[i]-'0')+'0';
    else{
      s[i+1]=s[i+1]-'0'-1+'0';
      s[i]=s[i]-'0'+10-(s2[i]-'0')+'0';
    }
  }
  reverse(s.begin(),s.end());
  int pos = s.find_first_not_of('0');
  if(pos > s.length()) pos = s.length();
  if(s.find_first_not_of('0') > s.length())
  return "0";
  else{
    s = s.substr(s.find_first_not_of('0'));
    if(flag == 1) return s;
    else return ("-" + s);
  }
}

number number::operator+(const class number& val){
  int tmp = 0;
  unsigned int i;
  string a,b,add,result;
  a = num;
  b = val.num;
  unsigned int lena = num.length();
  unsigned int lenb = val.num.length();
  for(i = 0;i < lena;i++){
    a[i] = num[lena - 1 - i];
  }
  for(i = 0;i < lenb;i++){
    b[i] = val.num[lenb - 1 - i];
  }
  add = a;
  unsigned int len = max(lena,lenb) + 1;
  for(i = 0;i < len;i++){
    if(i < lenb){
      tmp = add[i] - '0' + b[i] - '0' + tmp;
      add[i] = tmp % 10 + '0';
      tmp /= 10;
    }else{
      tmp = add[i] - '0' + tmp;
      add[i] = tmp % 10 + '0';
      tmp /= 10;
    }
  }
  result = add;
  for(i = 0;i < add.length();i++){
    result[i] = add[add.length() - 1 - i];
  }
  int pos = result.find_first_not_of('0');
  if(pos > result.length()) pos = result.length() - 1;
  result = result.substr(pos);
  return number(result);
}

number number::operator-(const class number& val){
  /*int tmp = 0;
  unsigned int i;
  string a,b,minus,result;
  a = num;
  b = val.num;
  unsigned int lena = num.length();
  unsigned int lenb = val.num.length();
  for(i = 0;i < lena;i++){
    a[i] = num[lena - 1 - i];
  }
  for(i = 0;i < lenb;i++){
    b[i] = val.num[lenb - 1 - i];
  }
  if(lena < lenb) {
    swap(lena,lenb);
    swap(a,b);
  }
  minus = a;
  unsigned int len = max(lena,lenb) + 1;
  for(i = 0;i < len;i++){
    if(i < lenb){
      tmp = (minus[i] - '0') - (b[i] - '0') - tmp;
      minus[i] = (tmp + 10) % 10 + '0';
      if(tmp < 0) tmp = 1;
    }else{
      tmp = minus[i] - '0' - tmp;
      minus[i] = (tmp + 10) % 10 + '0';
      if(tmp < 0) tmp = 1;
    }
  }
  result = minus;
  for(i = 0;i < minus.length();i++){
    result[i] = minus[minus.length() - 1 - i];
  }
  result = result.substr(result.find_first_not_of('0'));*/
  string result = Sub(num,val.num);
  return number(result);
}

number number::operator*(const class number& val){
  int tmp = 0;
  unsigned int i;
  string a,b,result;
  a = num;
  b = val.num;
  unsigned int lena = num.length();
  unsigned int lenb = val.num.length();
  for(i = 0;i < lena;i++){
    a[i] = num[lena - 1 - i];
  }
  for(i = 0;i < lenb;i++){
    b[i] = val.num[lenb - 1 - i];
  }
  if(lena < lenb){
    swap(lena,lenb);
    swap(a,b);
  }
  unsigned int len = lena + lenb -1;
  string mul(len,'0');
  for(i = 0;i < lenb;i++){
    for(unsigned int j = 0;j < lena;j++){
      int x = (a[j] - '0') * (b[i] - '0') + tmp + (mul[i + j] - '0');
      mul[i + j] = x % 10  + '0';
      tmp = x / 10;
      if(j == lena - 1){
        mul[i + j + 1] = tmp + '0';
        tmp = 0;
      }
    }
  }
  result = mul;
  for(i = 0;i < mul.length();i++){
    result[i] = mul[mul.length() - 1 - i];
  }
  int pos = result.find_first_not_of('0');
  if(pos > result.length()) pos = result.length() - 1;
  result = result.substr(pos);
  return number(result);
}

number number::operator/(const class number& val){
  string a,b;
  a = num;
  b = val.num;
  unsigned int lena=num.length();
  unsigned int lenb=val.num.length();
  int dis=lena-lenb;
  for(int i = 0;i < dis;i++){
    b += '0';
  }
  string _div(1000,'0');
  while(dis >= 0){
        int sum=0;
        string temp;
        while(number(a) >= number(b)){
            sum++;
            temp = Sub(a,b);
            a = temp;
        }
        _div[_div.length() - dis - 1]=sum+'0';
        if(number(a) < number(b)) dis--;
        b=b.erase(b.length() - dis -1);
  }
  string result;
  result = _div;
  int pos = result.find_first_not_of('0');
  if(pos > result.length()) pos = result.length() - 1;
  result = result.substr(pos);
  return number(result);
}

number number::operator%(const class number& val){
  string a,b;
  a = num;
  b = val.num;
  unsigned int lena=num.length();
  unsigned int lenb=val.num.length();
  int dis=lena-lenb;
  for(int i = 0;i < dis;i++){
    b += '0';
  }
  string _div(1000,'0');
  while(dis >= 0){
        int sum=0;
        string temp;
        while(number(a) >= number(b)){
            sum++;
            temp = Sub(a,b);
            a = temp;
        }
        _div = a;
        if(number(a) < number(b)) dis--;
        b=b.erase(b.length() - dis -1);
  }
  string result = _div;
  int pos = result.find_first_not_of('0');
  if(pos > result.length()) pos = result.length() - 1;
  result = _div.substr(pos);
  return number(result);
}

bool number::operator > (const class number& val) const{
  if(num.length() > val.num.length()){
    return true;
  }else if(num.length() < val.num.length()){
    return false;
  }else{
    unsigned int len = num.length();
    for(unsigned int i = 0;i <len;i++){
      if(num[i] > val.num[i]) return true;
    }
    return false;
  }
}

bool number::operator < (const class number& val) const{
  if(num.length() > val.num.length()){
    return false;
  }else if(num.length() < val.num.length()){
    return true;
  }else{
    unsigned int len = num.length();
    for(unsigned int i = 0;i <len;i++){
      if(num[i] < val.num[i]) return true;
    }
    return false;
  }
}

bool number::operator >= (const class number& val) const{
  if(num.length() > val.num.length()){
    return true;
  }else if(num.length() < val.num.length()){
    return false;
  }else{
    unsigned int len = num.length();
    for(unsigned int i = 0;i <len;i++){
      if(num[i] == val.num[i]) continue;
      if(num[i] > val.num[i]) return true;
      else return false;
    }
    return true;
  }
}

bool number::operator <= (const class number& val) const{
  if(num.length() > val.num.length()){
    return false;
  }else if(num.length() < val.num.length()){
    return true;
  }else{
    unsigned int len = num.length();
    for(unsigned int i = 0;i <len;i++){
      if(num[i] > val.num[i]) return false;
    }
    return true;
  }
}

bool number::operator != (const class number& val) const{
  if(num.length() != val.num.length()) return true;
  unsigned int len = num.length();
  for(unsigned int i = 0;i < len;i++){
    if(num[i] != val.num[i]) return true;
  }
  return false;
}

bool number::operator == (const class number& val) const{
  if(num.length() != val.num.length()) return false;
  unsigned int len = num.length();
  for(unsigned int i = 0;i < len;i++){
    if(num[i] != val.num[i]) return false;
  }
  return true;
}

number number::operator = (const class number& val){
  num = val.num;
  return *this;
}

ostream& operator<<(ostream& out,const class number& val){
  out<<val.num;
  return out;
}

istream& operator>>(istream& in, class number& val){
  in>>val.num;
  return in;
}

int main(int argc, char** argv){
    number v1, v2;
    cin >> v1 >> v2;
    cout<<"v1="<<v1<<endl;
    cout<<"v2="<<v2<<endl;
    cout<<"v1+v2="<<v1+v2<<endl;
    cout<<"v1-v2="<<v1-v2<<endl;
    //number v3 = v1 * v2;
    cout<<"v1*v2="<<v1*v2<<endl;
  //  cout<<"v1*v2=182291067202610882538196767087546887313635167500388981732422"<<endl;
    number v3=v1/v2;
    number v4=v1%v2;
    cout<<"v1/v2="<<v3<<endl;
    cout<<"v1%v2="<<v4<<endl;

//    number v3("53321765710392963016385256730");
//    number v4("8");
    cout << "T?F:" << ((v3*v2+v4)==v1) << endl;  // 检查计算是否正确
    return 0;
}
