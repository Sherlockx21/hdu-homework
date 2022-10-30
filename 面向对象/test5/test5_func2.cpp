#include <iostream>
#include <cstring>
#include <utility>
#include <vector>

using namespace std;

// 书
class Book
{
public:
    Book(const char *name, const char *isbn = "", float price=0.0, const char *text="");            // 构造函数
    Book(const Book &copy);                  // 复制构造函数
    Book(Book &&copy) noexcept;              // 移动构造函数
    Book & operator=(const Book &copy);           // 重载赋值运算符
    Book & operator=(Book && copy) noexcept;   // 移动赋值
    void setText (const char *text);               // 修改书的描述
    ~Book() { delete [] strText; }                   // 析构函数
    void Show() const;                          // 显示书本：名称（isbn, 价格）: 书的描述
    friend ostream& operator<<(ostream& out,const class Book& lib);
private:
    char name[128];             // 书名
    char ISBN[32];              // ISBN号
    float price;                // 价格
    char *strText;                    // 书的描述
};

// 图书馆
class Library
{
    public:
        Library(const char *name, int size=100);      // 默认构造函数
        Library(const Library & copy);                   // 拷贝构造
        Library(Library && copy) noexcept;                 // 移动构造
        Library & operator= (const Library &copy);          // 赋值
        Library & operator= (Library &&copy) noexcept;         // 移动赋值
        void Show();                  // 显示名称和藏书数量
        void addBook(const Book &book);     // 增加一本书的收藏
        vector<Book> & getBooks();     // 获取图书
        friend ostream& operator<<(ostream& out,const class Library& lib);
    private:
        char name[128];                 // 图书馆的名字
        vector<Book> books;             // 收藏的书

};

/* 请在这里填写答案 */

Book::Book(const char *name,const char *isbn,float price,const char *text){
  strcpy(this->name,name);
  strcpy(ISBN,isbn);
  this->price = price;
  int len = strlen(text);
  strText = new char[len + 1];
  strcpy(strText,text);
}

Book::Book(const Book &copy){//复制构造函数
  strcpy(name,copy.name);
  strcpy(ISBN,copy.ISBN);
  price = copy.price;
  int len = strlen(copy.strText);
  strText = new char[len + 1];
  strcpy(strText,copy.strText);
}

Book::Book(Book &&copy) noexcept{//移动构造
  strcpy(name,copy.name);
  for(int i = 0;i < 128;i++){
    copy.name[i] = '\0';
  }
  strcpy(ISBN,copy.ISBN);
  for(int i = 0;i < 32;i++){
    copy.ISBN[i] = '\0';
  }
  price = copy.price;
  int len = strlen(copy.strText);
  strText = new char[len + 1];
  strcpy(strText,copy.strText);
  copy.strText = nullptr;
}

Book& Book::operator=(const Book &copy){
  strcpy(name,copy.name);
  strcpy(ISBN,copy.ISBN);
  price = copy.price;
  int len = strlen(copy.strText);
  strText = new char[len + 1];
  strcpy(strText,copy.strText);
  return *this;
}

Book& Book::operator=(Book && copy) noexcept{
  strcpy(name,copy.name);
  for(int i = 0;i < 128;i++){
    copy.name[i] = '\0';
  }
  strcpy(ISBN,copy.ISBN);
  for(int i = 0;i < 32;i++){
    copy.ISBN[i] = '\0';
  }
  price = copy.price;
  int len = strlen(copy.strText);
  strText = new char[len + 1];
  strcpy(strText,copy.strText);
  copy.strText = nullptr;
  return *this;
}

void Book::setText (const char *text){ // 修改书的描述
  int len = strlen(text);
  strText = new char[len + 1];
  for (int i = 0; i < len + 1; ++i)
      this->strText[i] = text[i];
}

void Book::Show() const{// 显示书本：名称（isbn, 价格）: 书的描述
  cout<<name<<"("<<ISBN<<","<<price<<"):"<<strText<<endl;
}

Library::Library(const char *name, int size){
  strcpy(this->name,name);
  books.reserve(size);
}

Library::Library(const Library & copy){
  strcpy(name,copy.name);
  for(unsigned int i = 0;i < copy.books.size();i++){
    books.push_back(copy.books[i]);
  }
}

Library::Library(Library && copy) noexcept{
  strcpy(name,copy.name);/*
  for(int i = 0;i < 128;i++){
    copy.name[i] = '\0';
  }*/
  for(unsigned int i = 0;i < copy.books.size();i++){
    books.push_back(copy.books[i]);
  }
  copy.books.clear();
}

Library& Library::operator= (const Library &copy){
  books.clear();
  strcpy(name,copy.name);
  for(unsigned int i = 0;i < copy.books.size();i++){
    books.push_back(copy.books[i]);
  }
  return *this;
}

Library& Library::operator= (Library &&copy) noexcept{
  if(!name) strcpy(name,copy.name);
  if(name) swap(name,copy.name);
  /*for(int i = 0;i < 128;i++){
    copy.name[i] = '\0';
  }*/
  //books.clear();
  unsigned int num = min(books.size(),copy.books.size());
  for(unsigned int i = 0;i < num;i++){
    swap(books[i],copy.books[i]);
  }
  if(books.size() < copy.books.size()){
    for(unsigned int i = num;i < copy.books.size();i++){
      books.push_back(copy.books[i]);
    }
    for(unsigned int i = num;i <= copy.books.size();i++){
      copy.books.pop_back();
    }
  }else{
    for(unsigned int i = num;i < books.size();i++){
      copy.books.push_back(books[i]);
    }
    for(unsigned int i = num;i <= books.size();i++){
      books.pop_back();
    }
  }
  //copy.books.clear();
  return *this;
}

void Library::Show(){
  cout<<name<<":"<<books.size()<<endl;
}

void Library::addBook(const Book &book){
  books.push_back(book);
}

//vector<Book> & getBooks();

ostream& operator<<(ostream& out,const class Library& lib){
  cout<<lib.name<<":"<<lib.books.size()<<endl;
  for(unsigned int i = 0;i < lib.books.size();i++){
    lib.books[i].Show();
  }
  return out;
}

// 主函数main()
int main()
{
    char txt1[] = "C++ Programming";
    Book b1("BK0011", "ISBN-0011", 35.0, txt1);
    char txt2[] = "Operating System";
    Book b2("BK0022", "ISBN-0022", 40.0, txt2);
    Library lib1("HangZhou Library");  // 创建图书馆并增加2本书
    lib1.addBook(b1);
    lib1.addBook(b2);
    // lib1.Show();
    cout << lib1 << endl;

    Library lib2(lib1);     // 拷贝构造并增加1本书
    lib2.addBook(Book("BK1031", "ISBN-1031", 100, "Economy Theory"));
    // lib2.Show();
    cout << lib2 << endl;

    Library lib3 = std::move(lib1); // 移动构造
//    lib3.Show();
//    lib1.Show();
    cout << lib3 << endl;
    cout << lib1 << endl;

    Library lib4("NanJing");
    lib4.addBook(Book("BK2109", "ISBN-2109", 200, "The Law Principles"));
    lib4 = std::move(lib2);     // 移动赋值
//    lib4.Show();
//    lib2.Show();
    cout << lib4 << endl;
    cout << lib2 << endl;
}
