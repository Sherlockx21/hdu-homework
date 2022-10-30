#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Int_Stack {
private:
    struct ListNode* dummynode;
    int _size;
public:
    Int_Stack();
    ~Int_Stack();
    Int_Stack(const Int_Stack& s1);
    Int_Stack(Int_Stack&& s1) noexcept;
    Int_Stack& operator=(const Int_Stack& is);
    Int_Stack& operator=(Int_Stack&& is) noexcept;
    bool empty() const;
    int size() const;
    int top() const;
    void pop();
    void push(int val);
};

/* ����������д���� */
Int_Stack::Int_Stack()
{
    this->dummynode = new ListNode;
    this->_size = 0;
}

Int_Stack::~Int_Stack()
{
    ListNode* t = this->dummynode;
    while (t)
    {
        ListNode* e = t;
        t = t->next;
        delete e;
        e = NULL;
    }
    this->_size = 0;
    this->dummynode = NULL;
}

Int_Stack::Int_Stack(const Int_Stack& s1)
{
    this->_size = s1._size;
    ListNode* t = s1.dummynode;
    while (t)
    {
        ListNode* e = this->dummynode;
        while (e->next)
            e = e->next;
        ListNode* m = new ListNode;
        m->val = t->val;
        m->next = NULL;
        e->next = m;
        t = t->next;
    }
}

Int_Stack::Int_Stack(Int_Stack&& s1) noexcept
{
    this->dummynode = s1.dummynode;
    this->_size = s1._size;
    s1.dummynode = NULL;
    s1._size = 0;
}

Int_Stack& Int_Stack::operator=(const Int_Stack& is)
{
    this->_size = is._size;
    ListNode* t = this->dummynode;
    while (t)
    {
        ListNode* e = t;
        t = t->next;
        delete e;
        e = NULL;
    }
    this->dummynode = new ListNode;
    t = is.dummynode;
    while (t)
    {
        ListNode* e = this->dummynode;
        while (e->next)
            e = e->next;
        ListNode* m = new ListNode;
        m->val = t->val;
        m->next = NULL;
        e->next = m;
        t = t->next;
    }
    return *this;
}

Int_Stack& Int_Stack::operator=(Int_Stack&& is) noexcept
{
    this->_size = is._size;
    ListNode* t = this->dummynode;
    while (t)
    {
        ListNode* e = t;
        t = t->next;
        delete e;
        e = NULL;
    }
    this->dummynode = NULL;
    this->dummynode = is.dummynode;
    is.dummynode = NULL;
    is._size = 0;
    return *this;
}

bool Int_Stack::empty() const
{
    if (!this->_size)
        return true;
    return false;
}

int Int_Stack::size() const
{
    return this->_size;
}

int Int_Stack::top() const
{
    ListNode* t = this->dummynode;
    while (t->next)
        t = t->next;
    return t->val;
}

void Int_Stack::pop()
{
    ListNode* t = this->dummynode;
    ListNode* e = this->dummynode;
    while (t->next)
        t = t->next;
    while (e->next != t)
        e = e->next;
    e->next = NULL;
    delete t;
    t = NULL;
    --this->_size;
}

void Int_Stack::push(int val)
{
    ListNode* t = this->dummynode;
    while (t->next)
        t = t->next;
    ListNode* e = new ListNode;
    e->val = val;
    e->next = NULL;
    t->next = e;
    ++this->_size;
}


int main(int argc, char** argv) {
    Int_Stack A, B;
    int m, n, num;
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> num;
        A.push(num);
    }
    cout << A.size() << ":" << A.top() << endl;
    A.pop();
    cout << A.size() << ":" << A.top() << endl;
    B = A;
    cout << B.size() << ":" << B.top() << endl;
    B.pop();
    cout << B.size() << ":" << B.top() << endl;
    return 0;
}
