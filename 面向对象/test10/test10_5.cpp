#include<bits/stdc++.h>
using namespace std;

set<string> s;
vector<string> v;

int main(int argc, char const *argv[]) {
  int n;
  string word;
  cin>>n;
  while(n--){
    cin>>word;
    s.insert(word);
    if(word[0] >= 'A' && word[0] <= 'Z' || word[0] >='a' && word[0] <= 'z') v.push_back(word);
  }
  for(int i = 0;i < v.size();i++){
    cout<<v[i]<<" ";
  }
  return 0;
}
