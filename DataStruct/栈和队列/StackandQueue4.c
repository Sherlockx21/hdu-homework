#include <stdio.h>
#include <stdlib.h>

int main(){
	int N,count = 0,num;
	scanf("%d",&N);
	int rear[N];
	while(N--){
		scanf("%d",&num);
		if(count == 0 || rear[count - 1] < num) rear[count++] = num;
		else{
			int h = count - 1,l = 0,mid;
			while(l < h){
				mid = (l + h) / 2;
				if(rear[mid] > num) h = mid - 1;
				else l = mid + 1;
			}
			rear[l] = num;
		}
	}
  printf("%d",count);
}
