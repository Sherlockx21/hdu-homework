#include<bits/stdc++.h>
using namespace std;

deque<int> q;
vector<int> v;

bool isprime(int n){
  for(int i = 2;i < n / 2 + 1;i++){
    if(n % i == 0) return false;
  }
  return true;
}

int main(int argc, char const *argv[]) {
  int n,num;
  cin>>n;
  while(n--){
    cin>>num;
    q.push_front(num);
  }
  for(int i = 0;i < q.size();i++){
    if(isprime(q[i])) v.push_back(q[i]);
    cout<<q[i]<<" ";
  }
  cout<<endl;
  for(int i = 0;i < v.size();i++){
    cout<<v[i]<<" ";
  }
  return 0;
}
