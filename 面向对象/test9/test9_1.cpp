#include<bits/stdc++.h>
using namespace std;

class MyException:public exception{
  string m_errMsg;
public:
  MyException(){
    m_errMsg = "EXCEPTION";
  }
  MyException(string errMsg):m_errMsg(errMsg){
  }
  const char* what() const noexcept{
    return m_errMsg.c_str();
  }
};

class Student{
private:
  string number;
  string name;
  int age;
public:
  Student(){}
  Student(string _number,string _name,int _age){
    number = _number;
    name = _name;
    age = _age;
  }
  void Writenumber(string _number,Student val){
    val.number = _number;
  }
  void Writename(string _name,Student val){
    val.name = _name;
  }
  void Writeage(int _age,Student val){
    val.age = _age;
  }
  friend istream& operator>>(istream& in,Student& val){
    in>>val.number>>val.name>>val.age;
    return in;
  }
  void numberadd(string type){
    number = number + type;
  }
  friend ostream& operator<<(ostream& out,const class Student& val){
    out<<val.number<<" "<<val.name<<" "<<val.age;
    return out;
  }
  string Showname(){
    return this->name;
  }
  string Shownumber(){
    return this->number;
  }
  int Showage(){
    return this->age;
  }
  Student operator= (const shared_ptr<Student>& val) const{
    Student stu;
    stu.number = (*val).number;
    stu.name = (*val).name;
    stu.age = (*val).age;
    return stu;
  }
};

class Class{
private:
  string name;
  vector<shared_ptr<Student>> cv;
public:
  Class(string _name){
    name = _name;
  }
  void add(Student s){
    auto _s = make_shared<Student>(s);
    cv.push_back(_s);
  }
  shared_ptr<Student>& operator[](int i){
    if(i >= cv.size()) throw MyException();
    return cv[i];
  }
  friend ostream& operator<<(ostream& out,const class Class& val){
    out<<val.name<<":"<<endl;
    for(unsigned int i = 0;i < val.cv.size();i++){
      out<<val.cv[i]->Shownumber()<<" "<<val.cv[i]->Showname()<<" "<<val.cv[i]->Showage()<<endl;
    }
    return out;
  }
};

class Group{
private:
  string glabel;
  vector<shared_ptr<Student>> gv;
public:
  Group(string _label){
    glabel  = _label;
  }
  void join(shared_ptr<Student> s){
    gv.push_back(s);
  }
  void label(string _label){
    for(unsigned int i = 0;i < gv.size();i++){
      (*gv[i]).numberadd(_label);
    }
  }
  friend ostream& operator<<(ostream& out,const class Group& val){
    out<<val.glabel<<":"<<endl;
    for(unsigned int i = 0;i < val.gv.size();i++){
      out<<val.gv[i]->Shownumber()<<" "<<val.gv[i]->Showname()<<" "<<val.gv[i]->Showage()<<endl;
    }
    return out;
  }
};

/* 请在这里填写答案 */
int main(int argc, char** argv)
{
    int n;
    cin >> n;
    Class C1("210901");    // 班级
    Group A1("ACM");    // ACM
    Group M1("MTH");    // 数学建模

    for(int i = 0; i < n; i++){
        Student s1;
        cin >> s1;
        C1.add(s1);    // 学生加入班级; 班级对学生对象进行托管
    }

    try
    {
        // 学生1:加入ACM
        auto a1 = C1[0];    // 获得第一个学生的共享智能指针
        A1.join(a1);        // 加入到ACM1

        // 学生2:加入ACM和数据建模
        auto a2 = C1[1];
        A1.join(a2);
        M1.join(a2);

        // 学生3:加入ACM和数据建模
        auto a3 = C1[2];
        A1.join(a3);
        M1.join(a3);
    }
    catch(MyException ex){
        cout << ex.what() << endl;
    }
    catch(...){
        cout << "error" << endl;
    }

    // 在学生学号后加上其参加的集训队标记
    A1.label("A");
    M1.label("M");


    // 输出学生信息
    cout << C1 << endl;
    cout << A1 << endl;
    cout << M1 << endl;

    return 0;
}
