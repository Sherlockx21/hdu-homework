#include<bits/stdc++.h>
using namespace std;

class CUIControl{
private:
  string name;
public:
  CUIControl();
  CUIControl(string _name){
    name = _name;
  }
  string GetName(){
    return name;
  }
  virtual void Clicked() = 0;
};

class CMenu:public CUIControl{
public:
  CMenu(string _name);
  void Clicked();
};

class CButton:public CUIControl{
public:
  CButton(string _name);
  void Clicked();
};

CMenu::CMenu(string _name):CUIControl::CUIControl(_name){}

void CMenu::Clicked(){
  cout<<"menu-"<<GetName()<<" "<<"clicked"<<endl;
}

CButton::CButton(string _name):CUIControl::CUIControl(_name){}

void CButton::Clicked(){
  cout<<"button-"<<GetName()<<" "<<"clicked"<<endl;
}

/* 请在这里填写答案 */

int main(int argc, char** argv) {
    int n;
    string n1,n2;
    cin>>n;
    vector<CUIControl*> vc;
    for(int i=0;i<n;i++){
        cin>>n1>>n2;
        if(n1=="menu"){
            CMenu* CM=new CMenu(n2);
            vc.push_back(CM);
        }else if(n1=="button"){
            CButton* CB=new CButton(n2);
            vc.push_back(CB);
        }
    }
    while((cin>>n1>>n)){
        vc[n-1]->Clicked();
    }
    system("pause");
    return 0;
}
