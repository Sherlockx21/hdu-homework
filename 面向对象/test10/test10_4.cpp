#include<bits/stdc++.h>
using namespace std;

list<int> l;

bool isprime(int a){
  if(a == 0) return false;
  for(int i = 2;i < a / 2 + 1;i++){
    if(a % i == 0) return false;
  }
  return true;
}

int main(int argc, char const *argv[]) {
  int n,num,zeronum,primenum = 0;
  cin>>n;
  while(n--){
    cin>>num;
    l.push_back(num);
    if(isprime(num)) primenum++;
  }
  zeronum = count(l.begin(),l.end(),0);
  cout<<zeronum<<endl<<primenum;
  return 0;
}
