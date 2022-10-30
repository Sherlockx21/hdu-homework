#include<bits/stdc++.h>
using namespace std;
int main() {
	string a;
	while(cin>>a) {
		stack<char> s;
		deque<char> q;
		int t=0;
		for(int i=0; i<a.length(); i++) {
			if(a[i]=='(') {
				s.push(a[i]);
				q.push_back(a[i]);
			} else if(a[i]==')') {
				if(!s.empty()&&s.top()=='(') {

					s.pop();
					q.push_back(a[i]);
				} else {
					q.push_front('(');
					q.push_back(a[i]);
					t++;
				}
			}
		}
		while(!s.empty()) {
			s.pop();
			q.push_back(')');
			t++;
		}
		if(t==0) {
			cout<<"Match\n";
		} else {
			cout<<t<<endl;
			while(!q.empty()) {
				cout<<q.front();
				q.pop_front();
			}
			cout<<endl;
		}
	}


	return 0;
}
