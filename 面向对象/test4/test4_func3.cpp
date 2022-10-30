#include <iostream>
#include <cstring>
#include <utility>

using namespace std;

class String{
private:
    char* strValue;
public:
    String(const char* s = "");
    String(const String& copy);
    String(String&& copy) noexcept;
    String& operator=(const String& copy);
    String& operator=(String&& copy) noexcept;
    String  Reverse() const;
    ~String() { delete[]strValue; }
    void Show() const;
};

class Word{
public:
    Word();
    Word(const char* s);
    void Show() const;
private:
    String s1;

};



String::String(const char* s){
    this->strValue = new char[strlen(s) + 1];
    strcpy(this->strValue, s);
}

String::String(const String& copy){
    this->strValue = new char[strlen(copy.strValue) + 1];
    for (int i = 0; i < strlen(copy.strValue) + 1; ++i)
        this->strValue[i] = copy.strValue[i];
}

String::String(String&& copy) noexcept{
    this->strValue = copy.strValue;
    copy.strValue = new char[2];
    strcpy(copy.strValue, "\0");
}

String& String::operator=(const String& copy){
    delete[] this->strValue;
    this->strValue = new char[strlen(copy.strValue) + 1];
    for (int i = 0; i < strlen(copy.strValue) + 1; ++i)
        this->strValue[i] = copy.strValue[i];
    return *this;
}

String& String::operator=(String&& copy) noexcept{
    if(this->strValue == nullptr){
      this->strValue = copy.strValue;
      copy.strValue = new char[2];
      strcpy(copy.strValue, "\0");
    }else{
      swap(this->strValue,copy.strValue);
    }
    return *this;
}


String String::Reverse() const{
    char* t = new char[strlen(this->strValue) + 1];
    strcpy(t, this->strValue);
    for (int i = 0, j = strlen(t)-1; i <= j; ++i, --j)
    {
        char e = t[i];
        t[i] = t[j];
        t[j] = e;
    }
    return String(t);
}

void String::Show() const{
    cout << this->strValue << endl;
}

Word::Word(){
    this->s1 = "";
}

Word::Word(const char* s){
    this->s1 = s;
}

void Word::Show() const{
    this->s1.Show();
}


int main()
{
    char t1[32];
    cin >> t1;
    String s1(t1), s2, s3;
    s2 = s1;
    s3 = s1.Reverse();
    s1.Show();
    s2.Show();
    s3.Show();
    String s4(std::move(s1));
    s1.Show();
    s4.Show();

    char t2[32];
    cin >> t2;
    Word w1(t2);
    Word w2 = w1;
    w2.Show();
    Word w3;
    w3 = w2;
    w3.Show();
    Word w4 = std::move(w2);
    w2.Show();
    w4.Show();

    char t3[32];
    cin >> t3;
    Word w5(t3);
    w5 = std::move(w4);
    w4.Show();
    w5.Show();
}
