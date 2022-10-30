#include <iostream>
#include <string>
using namespace std;

class Vehicle{
private:
    string type;       // 类型
    string brand;      // 品牌
    string birth;      // 生产日期
    string fuel;       // 邮箱容量
public:
    Vehicle(string _type,string _brand,string _birth,string _fuel);
    void SetFuel(string _fuel);
    string GetFuel() const;
    string GetBrand() const;
    string GetBirth() const;
    string GetType() const;
    virtual void Introduce() const =0;
};

class Truck:public Vehicle{
private:
    double ton;        // 货物载重量
public:
    Truck(double _ton,string _type,string _brand,string _birth,string _fuel);
    double GetTon() const;
    virtual void Introduce() const;
};

class Bus:public Vehicle{
private:
    int passengers;    // 额定乘客数量
public:
    Bus(int _passengers,string _type,string _brand,string _birth,string _fuel);
    double GetPassenger() const;
    virtual void Introduce() const;
};

/* 请在这里填写答案 */
Vehicle::Vehicle(string _type,string _brand,string _birth,string _fuel){
  type = _type;
  brand = _brand;
  birth = _birth;
  fuel = _fuel;
}

void Vehicle::SetFuel(string _fuel){
  fuel = _fuel;
}

string Vehicle::GetFuel() const{
  return fuel;
}

string Vehicle::GetBrand() const{
  return brand;
}

string Vehicle::GetBirth() const{
  return birth;
}

string Vehicle::GetType() const{
  return type;
}

void Vehicle::Introduce() const{
  cout<<type<<" "<<brand<<" "<<birth<<" ";
}

Truck::Truck(double _ton,string _type,string _brand,string _birth,string _fuel):Vehicle::Vehicle(_type,_brand,_birth,_fuel){
  ton = _ton;
}

double Truck::GetTon() const{
  return ton;
}

void Truck::Introduce() const{
  cout<<"Truck:";
  Vehicle::Introduce();
  cout<<ton<<endl;
}

Bus::Bus(int _passengers,string _type,string _brand,string _birth,string _fuel):Vehicle::Vehicle(_type,_brand,_birth,_fuel){
  passengers = _passengers;
}

double Bus::GetPassenger() const{
  return passengers;
}

void Bus::Introduce() const{
  cout<<"Bus:";
  Vehicle::Introduce();
  cout<<passengers<<endl;
}

int main(int argc, char** argv) {
    Truck t1(25,"LargeTruck","JieFang","1992-11-20","12");
    Bus b1(40,"LargeBus","YuTong","1993-12-10","30");
    Vehicle &v1=t1;
    Vehicle &v2=b1;
    v1.Introduce();
    // cout<<endl;
    v2.Introduce();
    return 0;
}
