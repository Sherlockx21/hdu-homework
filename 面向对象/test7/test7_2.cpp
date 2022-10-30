#include<bits/stdc++.h>
using namespace std;

class CPoint{
private:
  double x;
  double y;
public:
  CPoint(){};
  CPoint(double _x,double _y){
    x = _x;
    y = _y;
  }
  double Getx() const{
    return x;
  }
  double Gety() const{
    return y;
  }
};

class CShape{
private:
  string name;
  CPoint pos;
public:
  CShape(CPoint _pos){
    pos = _pos;
  }
  CPoint Getpos() const{
    return pos;
  }
  string GetName(){
    return name;
  }
  virtual bool HitIn(const CPoint &_pos) const = 0;
};

class CCircle:public CShape{
private:
  double r;
public:
  CCircle(CPoint _pos,double _r);
  ~CCircle(){};
  virtual bool HitIn(const CPoint &_pos) const;
};
CCircle::CCircle(CPoint _pos,double _r):CShape::CShape(_pos){
  r = _r;
}
bool CCircle::HitIn(const CPoint &_pos) const{
  CPoint pos = Getpos();
  double disx = abs(pos.Getx() - _pos.Getx());
  double disy = abs(pos.Gety() - _pos.Gety());
  return ((disx*disx + disy*disy) <= r*r);
}

class CRectangle:public CShape{
private:
  double w;
  double h;
public:
  CRectangle(CPoint _pos,double _w,double _h);
  virtual bool HitIn(const CPoint &_pos) const;
};
CRectangle::CRectangle(CPoint _pos,double _w,double _h):CShape::CShape(_pos){
  w = _w;
  h = _h;
}
bool CRectangle::HitIn(const CPoint &_pos) const{
  CPoint pos = Getpos();
  double disx = _pos.Getx() - pos.Getx();
  double disy = _pos.Gety() - pos.Gety();
  return (disx >= 0 && disx <= w && disy >= 0 && disy <= h);
}


class CUIControl{
private:
  string name;
  CShape *pShape;
public:
  CUIControl();
  CUIControl(string _name){
    name = _name;
  }
  ~CUIControl(){};
  void SetShape(CShape *s){
    pShape = s;
  }
  CShape* GetShape() const{
    return pShape;
  }
  string GetName() const{
    return name;
  }
  virtual bool HitTest(const CPoint &pos) const = 0;
  virtual void clicked() = 0;
};

class CMenu:public CUIControl{
public:
  CMenu(string _name);
  virtual bool HitTest(const CPoint &pos) const;
  void clicked();
};
CMenu::CMenu(string _name):CUIControl::CUIControl(_name){}
bool CMenu::HitTest(const CPoint &pos) const{
  CPoint _pos = pos;
  CShape *sh = GetShape();
  return sh->HitIn(_pos);
}
void CMenu::clicked(){
  cout<<"menu-"<<GetName()<<" "<<"Clicked"<<endl;
}

class CButton:public CUIControl{
public:
  CButton(string _name);
  virtual bool HitTest(const CPoint &pos) const;
  void clicked();
};
CButton::CButton(string _name):CUIControl::CUIControl(_name){}
bool CButton::HitTest(const CPoint &pos) const{
  CShape *sh = GetShape();
  CPoint _pos = pos;
  return sh->HitIn(_pos);
}
void CButton::clicked(){
  cout<<"button-"<<GetName()<<" "<<"Clicked"<<endl;
}


/* 请在这里填写答案 */

int main(int argc, char** argv) {
    double r;
    int n,x,y,w,h;
    string type,name,shape;
    cin>>n;
    CShape* s;
    vector<CUIControl*> vc;
    for(int i=0;i<5;i++){
        cin>>type>>name>>shape>>x>>y;
        CPoint pos(x,y);
        if(shape=="rectangle"){
            cin>>w>>h;
            CRectangle* rectangle=new CRectangle(pos,w,h);
            s=rectangle;
        }
        else{
            cin>>r;
            CCircle* circle=new CCircle(pos,r);
            s=circle;
        }
        if(type=="menu"){
            CMenu* CM=new CMenu(name);
            CM->SetShape(s);
            vc.push_back(CM);
        }else{
            CButton* CB=new CButton(name);
            CB->SetShape(s);
            vc.push_back(CB);
        }
    }
    string clk;
    int i;
    while(cin>>clk>>x>>y){
        CPoint pos(x,y);
        for(i=0;i<vc.size();i++){
            if(vc[i]->HitTest(pos)){
                vc[i]->clicked();
                break;
            }
        }
        if(i==vc.size()) cout<<"none hit"<<endl;
    }
    return 0;
}
