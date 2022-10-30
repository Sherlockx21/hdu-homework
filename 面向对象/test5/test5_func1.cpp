#include <iostream>
#include <vector>
#include <string>
using namespace std;

class CDate{
public:
    CDate();
    CDate (int year,int month,int day);
    CDate& operator ++();
    CDate operator ++(int);
    CDate operator+(long days) const; //若干天后的日期
    CDate operator-(long days) const; //若干天前的日期
    long operator -(const CDate& rhs) const;//相差天数
    int WeekDay() const;                //星期几，0表示星期日
    static int IsLeapYear(int year);    //该年是否闰年
    friend ostream& operator <<(ostream& out,const CDate& d);  // 输出日期
    friend istream& operator >>(istream& in, CDate& d);        // 输入日期
    int getmonthday();
    bool operator>(const CDate& d) const;
private:
    int m_year,m_month,m_day; //年、月、日
};

/* 请在这里填写答案 */
int GetMonthDay(int year,int month){
  int arr[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    if(month == 2 && ((year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0)))){
        ++arr[2];
    }
    return arr[month];
}

bool Valid(int year,int month,int day){
  return (year > 0 && month > 0 && month <= 12  && day > 0 && day <= GetMonthDay(year,month));
}

int CDate::IsLeapYear(int year){//判断闰年
  if((year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0))){
    return 1;
  }else{
    return 0;
  }
}

CDate::CDate(){
  m_year = 0;
  m_month = 0;
  m_day = 0;
}

CDate::CDate(int year,int month,int day){
  m_year = year;
  if(month >= 1 && month <= 12){
    m_month = month;
  }else{
    m_month = 0;
  }
  if(month == 2){
    if(IsLeapYear(year) && day > 29){
      m_day = 0;
    }else if(day > 28){
      m_day = 0;
    }else{
      m_day = day;
    }
  }else if(m_month == 4 || m_month == 6 || m_month == 9 || m_month == 11){
    if(day > 30){
      m_day = 0;
    }else{
      m_day = day;
    }
  }else{
    if(day > 31){
      m_day = 0;
    }else{
      m_day = day;
    }
  }
}

int CDate::getmonthday(){
  if(m_month == 2){
    if(IsLeapYear(m_year)){
      return 29;
    }else{
      return 28;
    }
  }else if(m_month == 4 || m_month == 6 || m_month == 9 || m_month == 11){
    return 30;
  }else{
    return 31;
  }
}

CDate& CDate::operator++(){
  m_day++;
  while(Valid(m_year,m_month,m_day) == false){
    int month_day = GetMonthDay(m_year,m_month);
    m_day -= month_day;
    ++m_month;
    if(m_month > 12){
       m_month = 1;
       ++m_year;
    }
  }
  return *this;
}

CDate CDate::operator ++(int){
  CDate tmp(*this);
  m_day++;
  while(Valid(m_year,m_month,m_day) == false){
    int month_day = GetMonthDay(m_year,m_month);
    m_day -= month_day;
    ++m_month;
    if(m_month > 12){
       m_month = 1;
       ++m_year;
    }
  }
  return tmp;
}

CDate CDate::operator+(long days) const{
  if(days < 0){
    return (*this) - (-m_day);
  }
  CDate d(*this);
  d.m_day += days;
  while(Valid(d.m_year,d.m_month,d.m_day) == false){
    int month_day = GetMonthDay(d.m_year,d.m_month);
    d.m_day -= month_day;
    ++d.m_month;
    if(d.m_month > 12){
       d.m_month = 1;
       ++d.m_year;
    }
  }
  return d;
}

CDate CDate::operator-(long days) const{
  if(days < 0){
     return (*this) + (-days);
  }
  CDate d(*this);
  d.m_day -= days;
  while(Valid(d.m_year,d.m_month,d.m_day) == false){
    --d.m_month;
    if(d.m_month == 0){
      --d.m_year;
      d.m_month = 12;
    }
    int pre_month_day = GetMonthDay(d.m_year,d.m_month);
        d.m_day += pre_month_day;
  }
  return d;
}

bool CDate::operator>(const CDate& d) const{
  if((m_year > d.m_year) || (m_year == d.m_year && m_month > d.m_month) || (m_year == d.m_year && m_month == d.m_month && m_day > d.m_day))
       return true;
   return false;
}

long CDate::operator -(const CDate& rhs) const{
  int flag = 1;
  CDate max = rhs;
  CDate min = (*this);
  if((*this) > rhs){
    max = (*this);
    min = rhs;
    flag = -1;
  }
  int count = 0;
  while(max.m_year != min.m_year && max.m_month != min.m_month && max.m_day != min.m_day){
    ++min;
    ++count;
  }
  return flag*count;
}

ostream& operator <<(ostream& out,const CDate& d){
  out<<d.m_year<<"-"<<d.m_month<<"-"<<d.m_day;
  return out;
}

istream& operator >>(istream& in, CDate& d){
  in>>d.m_year>>d.m_month>>d.m_day;
  return in;
}

int CDate::WeekDay() const{
  int C = 0;
  int month = 1;
  while(month < m_month){
    C += GetMonthDay(m_year,month);
    month++;
  }
  C += m_day;
  int S=(m_year-1)+(m_year-1)/4-(m_year-1)/100+(m_year-1)/400 + C;
  return S % 7;
}

int main(int argc, char** argv) {
    vector<string> w={"SUN","MON","TUE","WEN","THU","FRI","SAT"};
    CDate d1;
    int n;
    cin>>d1;
    cout<<d1<<endl;
    cout<<w[d1.WeekDay()]<<endl;
    cin>>n;
    CDate d2=d1+n;
    cout<<w[d2.WeekDay()]<<endl;
    ++d2;
    cout<<d2<<endl;
    d2++;
    cout<<d2<<endl;
    cout<<d2-d1<<endl;

//    cout<<d2-d1<<endl;

    return 0;
}
