#include <iostream>
#include <string>
using namespace std;

class HDUPerson{
private:
    string name;   // 名字
    string gender;    // 性别
    string age;    // 年龄
public:
    HDUPerson(string _name,string _gender,string _age);
    virtual void IntroduceSelf();
    string GetGender() const;
    string GetName() const;
    string GetAge() const;
    void SetName(string _name);
    void SetGender(string _gender);
    void SetAge(string _age);
    virtual int GetCurrentNum() const=0;
};

class Student:public HDUPerson{
private:
    int course_num;    // 学的课程数
public:
    Student(string _name,string _gender,string _age,int _course_num);
     virtual int GetCurrentNum() const;
     void IntroduceSelf();
};

class Teacher:public HDUPerson{
private:
    int course_num;    // 教的课程数
public:
    Teacher(string _name,string _gender,string _age,int _course_num);
     virtual int GetCurrentNum() const;
     void IntroduceSelf();
};

/* 请在这里填写答案 */
HDUPerson::HDUPerson(string _name,string _gender,string _age){
  name = _name;
  gender = _gender;
  age = _age;
}

void HDUPerson::IntroduceSelf(){
  cout<<name<<" "<<gender<<" "<<age<<endl;
}

string HDUPerson::GetGender() const{
  return gender;
}

string HDUPerson::GetName() const{
  return name;
}

string HDUPerson::GetAge() const{
  return age;
}

void HDUPerson::SetName(string _name){
  name = _name;
}

void HDUPerson::SetGender(string _gender){
  gender = _gender;
}

void HDUPerson::SetAge(string _age){
  age = _age;
}

Student::Student(string _name,string _gender,string _age,int _course_num):HDUPerson(_name,_gender,_age){
  course_num = _course_num;
}

int Student::GetCurrentNum() const{
   return  course_num;
 }

void Student::IntroduceSelf(){
   cout<<"Student:";
   HDUPerson::IntroduceSelf();
 }

Teacher::Teacher(string _name,string _gender,string _age,int _course_num):HDUPerson(_name,_gender,_age){
  course_num = _course_num;
}

int Teacher::GetCurrentNum() const{
   return course_num;
}

void Teacher::IntroduceSelf(){
    cout<<"Teacher:";
    HDUPerson::IntroduceSelf();
}

int main(int argc, char** argv) {
    HDUPerson* p1=new Teacher("Mary","female","31",6);
    HDUPerson* p2=new Student("Tom","male","18",8);
    p1->IntroduceSelf();
    cout<<"Teaching courses:"<<p1->GetCurrentNum()<<endl;
    p2->IntroduceSelf();
    cout<<"Studying courses:"<<p2->GetCurrentNum()<<endl;
    return 0;
}
