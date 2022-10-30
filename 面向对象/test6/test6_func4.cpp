#include <iostream>
#include <vector>
using namespace std;

class shape{
public:
        virtual double GetArea() const=0;     // 获得面积
        virtual void Input() =0;              // 输入长/宽/高
        virtual void Show() =0;               // 显示长/宽/高和面积
};

class Rectangle:public shape{
private:
    double length,width;               // 分别表示长和宽
public:
  Rectangle(double _length=0,double _width=0);
  virtual double GetArea() const;    // 计算面积
  virtual void Input();
  virtual void Show();               // 显示长,宽和面积
  double GetLen() const;
  double GetWidth() const;
};

class Cube:public Rectangle{
private:
    double height;                     // 高
public:
    Cube(double _length=0,double _width=0,double _height=0);
    virtual double GetArea() const;
    virtual void Input();              // 输入 长,宽,高
    virtual void Show();               // 显示长/宽/高和表面积
    double GetHeight();
};

/* 请在这里填写答案 */
double shape::GetArea() const{
  double area = 0;
  return area;
}
void shape::Input(){}              // 输入长/宽/高
void shape::Show(){}               // 显示长/宽/高和面积

Rectangle::Rectangle(double _length,double _width){
  length = _length;
  width = _width;
}

double Rectangle::GetArea() const{
  double area;
  area = length * width;
  return area;
}

void Rectangle::Input(){
  cin>>length>>width;
}

void Rectangle::Show(){
  double area = GetArea();
  cout<<"["<<length<<","<<width<<"]:"<<area<<endl;
}

double Rectangle::GetLen() const{
  return length;
}

double Rectangle::GetWidth() const{
  return width;
}

Cube::Cube(double _length,double _width,double _height):Rectangle::Rectangle(_length,_width){
  height = _height;
}

double Cube::GetArea() const{
  double area;
  double len = Rectangle::GetLen();
  double wid = Rectangle::GetWidth();
  area = 2 * (len * wid + len * height + wid * height);
  return area;
}

void Cube::Input(){
  double len,wid,h;
  cin>>len>>wid>>h;
  *this = Cube(len,wid,h);
}

void Cube::Show(){
  double len = Rectangle::GetLen();
  double wid = Rectangle::GetWidth();
  double h = GetHeight();
  double area = GetArea();
  cout<<"["<<len<<","<<wid<<","<<h<<"]:"<<area<<endl;
}

double Cube::GetHeight(){
  return height;
}

int main(int argc, char** argv) {
    vector<shape*> shapes;
    double totalArea=0;
    const int N = 4;
    for(int i=0;i<N;i++){
        if(i<N/2){
            shape* sp1=new Rectangle();
            sp1->Input();
            shapes.push_back(sp1);
        }else{
            shape* sp2=new Cube();
            sp2->Input();
            shapes.push_back(sp2);
        }
    }
    for(auto it = shapes.begin(); it != shapes.end(); it++){
        (*it)->Show();
        totalArea += (*it)->GetArea();
    }
    cout << totalArea << endl;
    return 0;
}
