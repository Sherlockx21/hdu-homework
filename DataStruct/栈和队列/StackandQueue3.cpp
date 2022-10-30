#include<bits/stdc++.h>
using namespace std;

#define DataType int
#define maxn 100010

struct Stack {
    DataType data[maxn];
    int top;
};

void StackClear(struct Stack* stk) {
    stk->top = 0;
}
void StackPushStack(struct Stack *stk, DataType dt) {
    stk->data[ stk->top++ ] = dt;
}
void StackPopStack(struct Stack* stk) {
    --stk->top;
}
DataType StackGetTop(struct Stack* stk) {
    return stk->data[ stk->top - 1 ];
}
int StackGetSize(struct Stack* stk) {
    return stk->top;
}
int StackIsEmpty(struct Stack* stk) {
    return !StackGetSize(stk);
}

int main() {
  stack<int> ivec;
	string s;
  while(cin>>s){
    if(s.length() > 1){
      if(s[0] == '-'){
         s.erase(0,1);
         ivec.push(-stoi(s));
       }else ivec.push(stoi(s));
   }else if(s >= "0" && s <= "99"){
      ivec.push(stoi(s));
    }
  //  cout<<ivec.top()<<" ";


    if(s == "#"){
        if(ivec.size() > 1){
          cout<<"Expression Error: "<<ivec.top()<<endl;
          break;
        }
        cout<<ivec.top()<<endl;
        break;
    }

    int cal1,cal2;


      if(s == "+"){
        if(ivec.size() == 1){
          cout<<"Expression Error: "<<ivec.top()<<endl;
          break;
        }
        cal1 = ivec.top();
        ivec.pop();
        cal2 = ivec.top();
        ivec.pop();
        ivec.push(cal2 + cal1);
      }
      if(s == "-"){
        if(ivec.size() == 1){
          cout<<"Expression Error: "<<ivec.top()<<endl;
          break;
        }
        cal1 = ivec.top();
        ivec.pop();
        cal2 = ivec.top();
        ivec.pop();
        ivec.push(cal2 - cal1);

      }

      if(s == "*"){
        if(ivec.size() == 1){
          cout<<"Expression Error: "<<ivec.top()<<endl;
          break;
        }
        cal1 = ivec.top();
        ivec.pop();
        cal2 = ivec.top();
        ivec.pop();
        ivec.push(cal2 * cal1);
      }

      if(s == "/"){
        if(ivec.size() == 1){
          cout<<"Expression Error: "<<ivec.top()<<endl;
          break;
        }

        cal1 = ivec.top();
        ivec.pop();
        cal2 = ivec.top();
        ivec.pop();
        if(cal1 == 0){
          cout<<"ERROR: "<<cal2<<"/"<<cal1<<endl;
          break;
        }
        //cout<<endl<<cal1<<cal2;
        ivec.push(cal2 / cal1);
      }
  }
  return 0;
}
