#include<bits/stdc++.h>
using namespace std;

#define DataType int
#define maxn 100010

class myStack{
private:
    int data[maxn];
    int top;
public:
    myStack(){}

    void Clear(){
        top = 0;
    }

    void Push(int dt){
        data[top++] = dt;
    }

    void Pop(){
        top--;
    }

    int GetTop(){
        return data[top - 1];
    }

    int GetSize(){
        return top;
    }

    int Empty(){
        return !GetSize();
    }
};
int main() {

  myStack *ivec = new myStack();
  string s;
  while(cin>>s){
    if(s.length() > 1){
      if(s[0] == '-'){
         s.erase(0,1);
         ivec->Push(-stoi(s));
     }else ivec->Push(stoi(s));
   }else if(s >= "0" && s <= "99"){
      ivec->Push(stoi(s));
    }
  //  cout<<ivec.top()<<" ";


    if(s == "#"){
        if(ivec->GetSize() > 1){
          cout<<"Expression Error: "<<ivec->GetTop()<<endl;
          break;
        }
        cout<<ivec->GetTop()<<endl;
        break;
    }

    int cal1,cal2;


      if(s == "+"){
        if(ivec->GetSize() == 1){
          cout<<"Expression Error: "<<ivec->GetTop()<<endl;
          break;
        }
        cal1 = ivec->GetTop();
        ivec->Pop();
        cal2 = ivec->GetTop();
        ivec->Pop();
        ivec->Push(cal2 + cal1);
      }
      if(s == "-"){
        if(ivec->GetSize() == 1){
          cout<<"Expression Error: "<<ivec->GetTop()<<endl;
          break;
        }
        cal1 = ivec->GetTop();
        ivec->Pop();
        cal2 = ivec->GetTop();
        ivec->Pop();
        ivec->Push(cal2 - cal1);

      }

      if(s == "*"){
        if(ivec->GetSize() == 1){
          cout<<"Expression Error: "<<ivec->GetTop()<<endl;
          break;
        }
        cal1 = ivec->GetTop();
        ivec->Pop();
        cal2 = ivec->GetTop();
        ivec->Pop();
        ivec->Push(cal2 * cal1);
      }

      if(s == "/"){
        if(ivec->GetSize() == 1){
          cout<<"Expression Error: "<<ivec->GetTop()<<endl;
          break;
        }

        cal1 = ivec->GetTop();
        ivec->Pop();
        cal2 = ivec->GetTop();
        ivec->Pop();
        if(cal1 == 0){
          cout<<"ERROR: "<<cal2<<"/"<<cal1<<endl;
          break;
        }
        //cout<<endl<<cal1<<cal2;
        ivec->Push(cal2 / cal1);
      }
  }
  return 0;
}
