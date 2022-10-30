#include<bits/stdc++.h>
using namespace std;
#define pi 3.14
#define ll long long

struct Node{
	int data;
	Node *next;
};

//插入元素
void Insert(Node *la,int x){
	//申请节点
	Node *q=new Node;
	q->data=x;
	//查找位置
	Node *p=la;
	while(p->next&&x>p->next->data){
		p=p->next;
	}
	q->next=p->next;
	p->next=q;
}

//销毁链表
void Destroy(Node *la){
	while(la){
		Node *q=la->next;
		delete la;
		la=q;
	}
}

//打印链表
void Print(Node *la){
	la=la->next;
	if(la){
		cout<<la->data;
		la=la->next;
	}else{
		return;
	}
	while(la){
		cout<<" "<<la->data;
		la=la->next;
	}
	cout<<" ";
}

int main(){
	Node *la0=new Node;
	Node *la1=new Node;
	la0->next=NULL;
	la1->next=NULL;
	int x;
	while(cin>>x){
    if(x<0){
			Insert(la0,x);
		}else if(x>0){
			Insert(la1,x);
		}else{
			break;
		}
	}
	Print(la1);
	cout<<endl;
	Print(la0);
	cout<<endl;
	Print(la0);
	Print(la1);
	Destroy(la0);
	Destroy(la1);
	return 0;
}
