#include<bits/stdc++.h>
using namespace std;

int main() {
  int num;
  list<int> nums;
  while(cin>>num){
    if(num==0) break;
    if(num<0){
      nums.push_front(num);
    }else{
      nums.push_back(num);
    }
  }

  list<int>::iterator it;
  for(it=nums.begin();it!=nums.end();it++){
    cout<<*it<<" ";
  }
  cout<<endl;
}
