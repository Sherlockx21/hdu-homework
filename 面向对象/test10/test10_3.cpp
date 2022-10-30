#include<bits/stdc++.h>
using namespace std;

vector<int> v;
deque<int> q;

int main(int argc, char const *argv[]) {
  int n,num;
  cin>>n;
  while(n--){
    cin>>num;
    v.push_back(num);
    auto prime = [](int a){
      for(int i = 2;i < a / 2 + 1;i++){
        if(a % i == 0) return false;
      }
      return true;
    };
    if(prime(num)) q.push_back(num);
    cout<<num<<" ";
  }
  cout<<endl;
  for(int i = 0;i < q.size();i++){
    cout<<q[i]<<" ";
  }
  return 0;
}
