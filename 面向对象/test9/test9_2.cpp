#include<bits/stdc++.h>
using namespace std;

class Song{
private:
  string name;
public:
  Song(string _name){
    name = _name;
  }
  ~Song(){
    cout<<"Song Destructor called"<<endl;
  }
  void Play(){
    cout<<"Play song "<<name<<endl;
  }
};

template <typename T>
class Unique_Ptr{
private:
  T* _p;
public:
  Unique_Ptr(T* p = nullptr){
    _p = p;
  }
  ~Unique_Ptr(){
    cout<<"Song Destructor called"<<endl;
  }
  T& operator* () const{
    return *_p;
  }
  T* operator-> () const{
    return _p;
  }
  void reset(T* p){
    _p = p;
  }
  T* get(){
    return _p;
  }
  T* release(){
    return _p;
  }
};
/* 请在这里填写答案 */

int main(int argc, char** argv) {
    Unique_Ptr<Song> up1;
    up1.reset(new Song("wake"));
    (*up1).Play();
    Song* s=up1.release();
    (*s).Play();
    up1.reset(new Song("you are beautiful"));
    s=up1.get();
    (*s).Play();
    return 0;
}
