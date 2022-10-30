#include<bits/stdc++.h>
using namespace std;

int main(){
  deque<string> sentence;
  string word;
  while(cin>>word){
    if(word=="###") break;
    if(word.length()<5){
      sentence.push_front(word);
    }else{
      sentence.push_back(word);
    }
  }

  deque<string>::iterator it;
  for(it=sentence.begin();it!=sentence.end();it++){
    cout<<*it<<" ";
  }
  cout<<endl;

  size_t i;
  for(i=0;i<sentence.size();i++){
    cout<<sentence[i]<<" ";
  }
  cout<<endl;
}
