
#include<bits/stdc++.h>

using namespace std;

stack<int> S1;
stack<string> S2;

int main(){
    int N,num,sum;
    int cal1,cal2;
    string op;
    cin>>N;
    for(int i = 0;i < N;i++){
        cin>>num;
        S1.push(num);
    }
    for(int i = 0;i < N - 1;i++){
        cin>>op;
        S2.push(op);
    }
    while(S1.size() != 1){
        cal1 = S1.top();
        S1.pop();
        cal2 = S1.top();
        S1.pop();
        op = S2.top();
        S2.pop();
        if(op == "+"){
            sum = cal2 + cal1;
            S1.push(sum);
        }
        if(op == "-"){
            sum = cal2 - cal1;
            S1.push(sum);
        }
        if(op == "*"){
            sum = cal2 * cal1;
            S1.push(sum);
        }
        if(op == "/"){
            if(cal1 == 0){
                cout<<"ERROR: "<<cal2<<"/"<<cal1<<endl;
                return 0;
            }
            sum = cal2 / cal1;
            S1.push(sum);
       }
    }
    cout<<S1.top()<<endl;
    return 0;
}
