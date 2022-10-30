#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> board = {
  {1,1,0,1,1,0,1,0,0},
  {0,1,0,0,1,0,0,0,0},
  {0,0,0,1,1,0,0,0,0},
  {0,0,0,0,0,0,0,0,0},
  {0,0,0,0,1,0,0,0,0},
  {1,0,0,0,0,0,1,0,1},
  {0,0,0,0,0,0,0,0,0},
  {0,0,0,0,1,0,0,0,0},
  {0,0,0,0,1,0,0,0,0},
  {0,0,0,0,1,1,1,0,0}
};

vector<vector<int>> dir = {{-2,2,-2,2},{-2,-2,2,2}};

 class Elephant{
 private:
   int x = 4;
   int y = 2;
   int newx;
   int newy;
 public:
   Elephant(){}
   void jump(){
     for(int i = 0;i < 4;i++){
       newx = x + dir[0][i];
       newy = y + dir[1][i];
       if(newx >=0 && newx <= 4 && newy >=0 && newy <= 8){
         cout<<"("<<newx<<", "<<newy<<") ";
       }
     }
   }
 };
int main(int argc, char const *argv[]) {
  Elephant elephant;
  elephant.jump();
  return 0;
}
