
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
/*
设计并实现一个具有构造、+、-、*、/、%、>、<、>=、<=、！=、==、<<等功能的无符号大数类。提示：为便于运算，无符号
大数内部存放连续十进制位时采用低位在前、高位在后的方式，去掉高位多余的0.无符号大数类应支持赋值和复制。

功能测试:



v1=1234567890987654321333888999666
v2=147655765659657669789687967867
v1+v2=1382223656647311991123576967533
v1-v2=1086912125327996651544201031799
v1*v2=182291067202610882538196767087546887313635167500388981732422
v1/v2=8
v1%v2=53321765710392963016385256730
T?F:1 
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class number{
private:
	string num;
	string _normalize(string );     // 正则化, 删除数字开头的'0' 
public:
	number();
	number(string _num);
	number(char c);
	number operator+(const class number& val);
	number operator-(const class number& val);
	number operator*(const class number& val);
	number operator/(const class number& val);
	number operator%(const class number& val);
	bool operator>(const class number& val) const;
	bool operator<(const class number& val) const;
	bool operator>=(const class number& val) const;
	bool operator<=(const class number& val) const;
	bool operator!=(const class number& val) const;
	bool operator==(const class number& val) const;
	number operator=(const class number& val);
	friend ostream& operator<<(ostream& out,const class number& val);
	friend istream& operator>>(istream& in, class number& val);
};

number::number():num(""){

}
number::number(string _num):num(_num){
	
}
number::number(char c):num(""){
	num+=c;
}

string number::_normalize(string str)
{
    string::iterator it;     //指向string类的迭代器。你可以理解为指针
	for (it = str.begin(); it != str.end(); it++)
	{
		if (*it == '0')
		{
			str.erase(it);   // 删除数字开头的 '0' 
		}
		else{
		    break;
        }
	}
	return str;
}

number number::operator+(const class number& val){
	   int n1=num.size()-1;
	   int n2=val.num.size()-1;
	   int carry=0;
	   string res;
	   int n,m;
	   n=m=0;
	   while(n1>=0||n2>=0||carry!=0){
	   		if(n1>=0&&n2>=0){
	   			n=(num[n1--]-'0')+(val.num[n2--]-'0')+carry;
		   		m=n%10;
		   		carry=n/10;
		   		res.push_back(m+'0');
			}else if(n1>=0&&n2<0){
				n=(num[n1--]-'0')+carry;
				m=n%10;
		   		carry=n/10;
		   		res.push_back(m+'0');
			}else if(n2>=0&&n1<0){
				n=(val.num[n2--]-'0')+carry;
				m=n%10;
		   		carry=n/10;
		   		res.push_back(m+'0');
			}else{
				res.push_back(carry+'0');
				carry=0;
			}
	   }
	   reverse(res.begin(),res.end());
	   return number(res);
}

number number::operator-(const class number& val){
	   if(*this==val) return number("0");
	   int na,nb,c,n;
	   string a,b,res;
	   int flag=1;
	   if(*this>val){
	   	   a=this->num;
	   	   na=num.size()-1;
	   	   b=val.num;
	   	   nb=val.num.size()-1;
	   }else{
	   	   flag=-1;
	   	   a=val.num;
	   	   na=val.num.size()-1;
	   	   b=this->num;
	   	   nb=num.size()-1;
	   }
	   n=c=0;
	   while(na>=0||nb>=0){
	   		if(na>=0&&nb>=0){
	   		   if((a[na]-'0'-c)>=(b[nb]-'0')){
		   	   		n=((a[na]-'0'-c)-(b[nb]-'0'));	
		   	   		if(!(n==0&&na==nb&&na==0)) res+=(n+'0');
		   	   		c=0 ;
			   }else{
			   		n=10-(b[nb]-'0')+(a[na]-'0')-c;
			   		c=1;
			   		res+=(n+'0');
			   }
			   na--;
			   nb--;
			}else{
				n=a[na]-'0'-c;
				c=0; 
				if(!(n==0&&na==0)) res+=(n+'0');
				na--;
			}
	   }
	   if(flag==-1) res+='-';
	   reverse(res.begin(),res.end());
	   return number(_normalize(res));
	   // return number(res)._normalize();
}

number number::operator/(const class number& val){
	   if(*this==val) return number("1");
	   else if(*this<val) return number("0");
	   int n=num.size();
	   class number divisor(val.num);
	   class number diviser;
	   string res;
	   int count=0;
	   class number zero("0");
	   for(int i=0;i<n;){
	   		while(diviser<divisor&&i<n){
	   			diviser.num+=num[i++];
				if(diviser<divisor) res+="0";	
			}
			while(!(diviser<divisor)){
				class number tmp=diviser-divisor;
				diviser=tmp;
				count++;
			}
			if((i!=n)||(i==n&&count!=0)) res+=(count+'0');
			if(diviser.num=="0") diviser.num="";
			count=0;
	   } 
	   int i;
	   for(i=0;i<res.size();i++){
	   		if(res[i]!='0') break;
	   }
	   res=res.assign(res.begin()+i,res.end());
	   return number(res);
}

number number::operator=(const class number& val){
		this->num=val.num;
		return true;
}

number number::operator*(const class number& val){
	   vector<number> v1;
	   int n1=num.size()-1;
	   int n2=val.num.size()-1;
	   int carry,n,m;
	   carry=n=m=0;
	   string zero="";
	   string tmp,res;
	   for(int i=n2;i>=0;i--){
	   		char c=val.num[i];
	   		while(carry!=0||n1>=0){
	   			if(n1>=0)	n=(num[n1--]-'0')*(c-'0')+carry;
	   			else {
	   				n=carry;
	   				carry=0;
				}
				m=n%10;
				carry=n/10;
				res.push_back(m+'0');
			}
			n1=num.size()-1;
			reverse(res.begin(),res.end());
	   		res+=zero;
	   		v1.push_back(number(res));
	   		res.clear();
	   		zero+="0";
	   }
	   for(int i=1;i<v1.size();i++){
	   	     v1[0]=v1[0]+v1[i];    
	   }
	   return v1[0];
}

number number::operator%(const class number& val){
	   class number t1=*this/val;
	   class number t2=t1*val;
	   return (*this-t2);
}

bool number::operator>(const class number& val) const{
		if(num.size()>val.num.size()) return true;
		else if(num.size()==val.num.size()){
			int n1=num.size();
			for(int i=0;i<n1;i++){
				int v1=num[i]-'0';
				int v2=val.num[i]-'0';
				//cout<<v1<<" "<<v2<<endl;
				if(v1==v2) continue;
				else if(v1>v2) return true;
				else return false;
			} 
			return false;
		}else return false;
} 

bool number::operator==(const class number& val) const{
		if(num.size()!=val.num.size()) return false;
		else{
			int n1=num.size()-1;
			while(n1>=0&&num[n1]==val.num[n1]){
				n1--;
			}
			if(n1<0) return true;
			else return false;
		}
}
bool number::operator<(const class number& val) const{
		return !(*this>val)&&!(*this==val);
} 

bool number::operator!=(const class number& val) const{
		return !(*this==val);
}

bool number::operator>=(const class number& val) const{
		return !(*this<val);
}

bool number::operator<=(const class number& val) const{
		return !(*this>val);
}

ostream& operator<<(ostream& out,const class number& val){
	 out<<val.num;
	 return out;
}

istream& operator>>(istream& in, class number& val){
	 string s1;
     in >> s1;
     val.num = s1;
     return in;
}

int main(int argc, char** argv) {
	number v1, v2;
    cin >> v1 >> v2;
	cout<<"v1="<<v1<< endl;
    cout<<"v2="<<v2<<endl;
	cout<<"v1+v2="<<v1+v2<<endl;
	cout<<"v1-v2="<<v1-v2<<endl;
	cout<<"v1*v2="<<v1*v2<<endl;
	number v3=v1/v2;
	number v4=v1%v2;
	cout<<"v1/v2="<<v3<<endl;
	cout<<"v1%v2="<<v4<<endl;
//	number v3("53321765710392963016385256730");
//	number v4("8");
	cout << "T?F:" << ((v3*v2+v4)==v1) << endl;    // 检查计算是否正确 
	return 0;
}
