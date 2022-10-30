#include<bits/stdc++.h>
using namespace std;
#define pi 3.14
#define ll long long

int main(){
	int n;
	cin>>n;
	vector<int> A(n*n,0);//分配相应内存空间

	//定义方向
	int iRow,iCol;
	enum DIRECTION{DOWN = 0,LEFT,UP,RIGHT};
	DIRECTION dir = DOWN;
	iRow = 0; iCol = 0;//起始位置

	//填充数据
	for(int k=1;k<=n*n;++k){
		A[iRow*n+iCol] = k;
		switch(dir){
			case DOWN:
			     if(iRow < n-1 && A[(iRow+1)*n+iCol] == 0){
						 ++iRow;
					 }else{
						 dir = RIGHT;
						 ++iCol;
					 }
					 break;

			case LEFT:
			     if(iCol > 0 && A[iRow*n+iCol-1] == 0){
						 --iCol;
					 }else{
						 dir = DOWN;
						 ++iRow;
					 }
					 break;

			case UP:
			     if(iRow > 0 && A[(iRow-1)*n+iCol]==0){
						 --iRow;
					 }else{
						 dir=LEFT;
						 --iCol;
					 }
					 break;

			case RIGHT:
			     if(iCol < n-1 && A[iRow*n+iCol+1] == 0){
						 ++iCol;
					 }else{
						 dir=UP;
						 --iRow;
					 }
					 break;
		}
	}

	//显示矩阵
	for(iRow=0;iRow<n;iRow++){
		for(iCol=0;iCol<n;iCol++){
			cout<<A[iRow*n+iCol]<<" ";
		}
		cout<<endl;
	}
}
