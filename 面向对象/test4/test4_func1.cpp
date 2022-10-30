
#include <iostream>
using namespace std;

class CSet{
public:
    CSet();
    ~CSet();
    bool Add(int x);
    void Display();
    CSet Union(const CSet& rhs) const;
    CSet Difference(const CSet& rhs) const;
    bool Remove(int x);
    CSet (const CSet& rhs);
    CSet& operator=(const CSet& rhs);
private:
    struct Node{
        int data;
        Node* next;
    } *m_pHead;
};

/* 请在这里填写答案 */

CSet::CSet(){
  m_pHead = new Node;
  m_pHead->next = NULL;
}

CSet::~CSet(){
  while(m_pHead){
    Node* p = m_pHead;
    m_pHead = p->next;
    //delete p;
  }
}

bool CSet::Add(int x){
  Node* p = m_pHead;
  while(p->next && (p->next->data < x)){
    p = p->next;
  }
  if(p->next && p->next->data == x){
    return false;
  }
  Node* q = new Node;
  q->data = x;
  q->next = p->next;
  p->next = q;
  return true;
}

void CSet::Display(){//显示集合

  Node* p = m_pHead->next;
  cout<<"{";
  while(p){
    cout<<p->data;
    p = p->next;
    if(p) cout<<",";
  }
  cout<<"}"<<endl;
  //return;
}

CSet CSet::Union(const CSet& rhs) const{
  CSet result;
  Node* last=result.m_pHead;
  Node* p = m_pHead->next;
  Node* q = rhs.m_pHead->next;
  while(p != NULL && q != NULL){
    if(p->data < q->data){
      Node* s = new Node;
      s->data = p->data;
      last->next = s;
      last = s;
      p = p->next;
    }else if(p->data > q->data){
      Node* s = new Node;
      s->data = q->data;
      last->next = s;
      last = s;
      q = q->next;
    }else if(p->data == q->data){
      Node* s = new Node;
      s->data = p->data;
      last->next = s;
      last = s;
      p = p->next;
      q = q->next;
    }
  }
  while(p != NULL){
    Node* s = new Node;
    s->data = p->data;
    last->next = s;
    last = s;
    p = p->next;
  }
  while(q != NULL){
    Node* s = new Node;
    s->data = q->data;
    last->next = s;
    last = s;
    q = q->next;
  }
  last->next = NULL;
  //result.Display();
  return result;
}
/*
  while(p && q){
    if(p->data == q->data){
      Node* s = new Node;
      s->data = p->data;
      last->next = s;
      last = s;
      p = p->next;
      q = q->next;
    }else if(p->data < q->data){
      p = p->next;
    }else{
      q = q->next;
    }
  }*/
CSet CSet::Difference(const CSet& rhs) const{//求集合差集
  CSet result;
  Node* last=result.m_pHead;
  Node* p = m_pHead->next;
  Node* q = rhs.m_pHead->next;
  while(p != NULL && q !=NULL){
    if(p->data < q->data){
      Node* s = new Node;
      s->data = p->data;
      last->next = s;
      last = s;
      p = p->next;
    }else if(p->data == q->data){
      p = p->next;
      q = q->next;
    }else if(p->data > q->data){
      q = q->next;
    }
  }
  while(p != NULL){
    Node* s = new Node;
    s->data = p->data;
    last->next = s;
    last = s;
    p = p->next;
  }
  last->next = NULL;
  //result.Display();
  /*  cout<<"{";
    result.m_pHead = result.m_pHead->next;
    while(result.m_pHead){
      cout<<result.m_pHead->data;
      result.m_pHead = result.m_pHead->next;
      if(result.m_pHead) cout<<",";
    }
    cout<<"}"<<endl;*/
  return result;
}

bool CSet::Remove(int x){
  Node* p = m_pHead;
  while(p->next && (p->next->data < x)){
    p = p->next;
  }
  if(p->next && p->next->data == x){
    p->next = p->next->next;
    return true;
  }
  return false;
}

CSet::CSet(const CSet &rhs){
  m_pHead = new Node;
  Node* last = m_pHead;
  Node* p = rhs.m_pHead->next;
  while(p){
    Node* q = new Node;
    q->data = p->data;
    last = q;
    p = p->next;
  }
  last->next = NULL;
}

CSet & CSet::operator = (const CSet& rhs){
  //
  //Node* t = rhs.m_pHead;
  m_pHead = rhs.m_pHead;
  
  return *this;
}

int main(int argc, char** argv){
    CSet A,B,S1,S2;
    int i,m,n,x;
    cin>>m>>n;
    for(i=0;i<m;i++){
        cin>>x;
        A.Add(x);
    }
    for(i=0;i<n;i++){
        cin>>x;
        B.Add(x);
    }
//    cout<<"A集合:";
//    A.Display();
//    cout<<endl<<"B集合:";
//    B.Display();
//    cout<<endl<<"删除元素3后,A集合:";
    A.Remove(3);
    A.Display();
//    cout<<endl<<"A,B并集:";
    S1=A.Union(B);
    S1.Display();
//    cout<<endl<<"A-B差集:";
    S2=A.Difference(B);
    S2.Display();
    return 0;
}
