
#include <iostream>
#include <string>
using namespace std;

// 人员
class Person{
private:
    string number;         // 工号
    string name;           // 姓名
    double salary;         // 工资
protected:
    void SetSalary(double _salary=0);         // 设置工资
    virtual double CalSalary() = 0;         // 计算工资

public:
    Person(string _number,string _name);
    string GetNumber() const;
    string GetName() const;
    double GetSalary() const;
    void show() const;
};

// 经理类
class Manager:virtual public Person{
public:
      Manager(string _number,string _name);
protected:
      virtual double CalSalary();
};

// 技术临时工
class Technician:virtual public Person{
private:
    int worktime;
public:
    Technician(string _number,string _name,int _worktime);
    virtual double CalSalary();
};

// 销售人员
class Salesman:virtual public Person{
private:
        int sale_all;
public:
        Salesman(string _number,string _name,int _sale_all);
        int getSales();
        virtual double CalSalary();
};

// 销售经理
class Salesmanager:public Salesman, public Manager{
private:
        // int sale_all;
public:
        Salesmanager(string _number,string _name,int _sale_all);
        virtual double CalSalary();
};

// 请在这里填写答案
Person::Person(string _number,string _name){
  number = _number;
  name = _name;
}

string Person::GetNumber() const{
  return number;
}

string Person::GetName() const{
  return name;
}

double Person::GetSalary() const{
  return salary;
}

void Person::show() const{
  cout<<name<<":"<<number<<" "<<salary<<endl;
}

void Person::SetSalary(double _salary){
  salary = _salary;
}

double Person::CalSalary(){
  salary = 0;
  return salary;
}

Manager::Manager(string _number,string _name):Person::Person(_number,_name){
  SetSalary(CalSalary());
}

double Manager::CalSalary(){
  return 8000;
}

Technician::Technician(string _number,string _name,int _worktime):Person::Person(_number,_name){
  worktime = _worktime;
  SetSalary(CalSalary());
}

double Technician::CalSalary(){
  return (worktime * 100);
}

Salesman::Salesman(string _number,string _name,int _sale_all):Person::Person(_number,_name){
  sale_all = _sale_all;
  SetSalary(CalSalary());
}

int Salesman::getSales(){
  return sale_all;
}

double Salesman::CalSalary(){
  return (getSales() * 0.04);
}

Salesmanager::Salesmanager(string _number,string _name,int _sale_all):Person::Person(_number,_name),Salesman::Salesman(_number,_name,_sale_all),Manager::Manager(_number,_name){
  SetSalary(CalSalary());
}

double Salesmanager::CalSalary(){
  return (5000 + getSales() * 0.005);
}


int main(int argc, char** argv) {
    Manager manager("0001","Ming");
    Technician technician("0002","Hong",100);
    Salesman salesman("0003","Zhan",200000);
    Salesmanager salesmanager("0004","Song",2000000);
    Person *p=&manager;
    p->GetSalary();
    p->show();
    p=&technician;
    p->show();
    p=&salesman;
    p->show();
    p=&salesmanager;
    p->show();
    return 0;
}
