//                        .::::.
//                      .::::::::.
//                    :::::::::::
//                 ..:::::::::::'
//              '::::::::::::'
//                .::::::::::
//           '::::::::::::::..
//                ..::::::::::::.
//              ``::::::::::::::::
//               ::::``:::::::::'        .:::.
//              ::::'   ':::::'       .::::::::.
//            .::::'      ::::     .:::::::'::::.
//           .:::'       :::::  .:::::::::' ':::::.
//          .::'        :::::.:::::::::'      ':::::.
//         .::'         ::::::::::::::'         ``::::.
//     ...:::           ::::::::::::'              ``::.
//    ```` ':.          ':::::::::'                  ::::..
//                       '.:::::'                    ':'````..
//                    美女保佑 永无BUG
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define N 1000000
#define ll long long
ll x[N],a[N],m[N];

//冒泡排序
void bubblesort(ll a[]){
  ll tmp;
  for(ll i = 0;i < N - 1;i++){
    for(ll j = 0;j < N - i - 1;j++){
      if(a[j] > a[j + 1]){
        tmp = a[j];
        a[j] = a[j + 1];
        a[j + 1] = tmp;
      }
    }
  }
  return;
}

//选择排序
void selectsort(ll a[]){
    ll minI;
    for(ll i = 0;i < N - 1;i++){
      minI = i;
      for(ll j = i + 1;j < N;j++){
        if(a[minI] > a[j]){
          minI = j;
        }
        ll tmp = a[i];
        a[i] = a[minI];
        a[minI] = tmp;
      }
    }
    return;
}

//插入排序
void insertsort(ll a[]){
  for(ll i = 1;i < N;i++){
    ll x = a[i];
    ll j = i - 1;
    while(j >= 0 && x < a[j]){
      a[j + 1] = a[j];
      j--;
    }
    a[j + 1] = x;
  }
}

void merge(ll a[], ll start, ll mid, ll end) {
  ll k = 0;
	ll i = start;
	ll j = mid + 1;
	while (i <= mid && j <= end) {
		if (a[i] < a[j]){
			m[k++] = a[i++];
    }else{
			m[k++] = a[j++];
    }
	}
	if (i == mid + 1) {
		while(j <= end)
			m[k++] = a[j++];
	}
	if (j == end + 1) {
		while (i <= mid)
			m[k++] = a[i++];
	}
	for (j = 0, i = start ; j < k; i++, j++) {
		a[i] = m[j];
	}
}

void mergesort(ll arr[], ll start, ll end) {
	if (start >= end)
		return;
	ll mid = ( start + end ) / 2;
	mergesort(arr, start, mid);
	mergesort(arr, mid + 1, end);
	merge(arr, start, mid, end);
}

//快速排序
void quicksort(ll a[],ll low,ll high){
  if(low > high) return;
  ll s = a[low];
  ll i = low;
  ll j = high;
  while(i != j){
    while(a[j] >= s && j > i) j--;
      while(a[i] <= s && j > i) i++;
        if(j > i){
          ll tmp = a[i];
          a[i] = a[j];
          a[j] = tmp;
         }
     }
     ll tmp = a[low];
     a[low] = a[i];
     a[i] = tmp;
     quicksort(a, low, i-1);
     quicksort(a, i+1, high);

}

void copy(ll x[],ll a[],ll n){
  for(ll i = 0;i < n;i++){
    a[i] = x[i];
  }
  return;
}

void print(ll a[],ll n){
  for(ll i = 0;i < n;i++){
    printf("%ld ",a[i]);
  }
  printf("\n");
}

int main(){
  int i,start,end;
  srand((unsigned)time(NULL));
  for(i = 0;i < N;i++){
    x[i] = rand();
  }/*
  for(i = 0;i < N;i++){
    printf("%d ",x[i]);
  }
  printf("\n");*/
  printf("N = %d\n",N);
  copy(x,a,N);
  start = clock();
  bubblesort(a);
  end = clock();
  //print(a,N);
  printf("Sort method:Bubblesort,Time cost:%5d ms\n",end - start);
  copy(x,a,N);
  start = clock();
  selectsort(a);
  end = clock();
  //print(a,N);
  printf("Sort method:Selectsort,Time cost:%5d ms\n",end - start);
  copy(x,a,N);
  start = clock();
  insertsort(a);
  end = clock();
  //print(a,N);
  printf("Sort method:Insertsort,Time cost:%5d ms\n",end - start);
  copy(x,a,N);
  start = clock();
  mergesort(a,0,N-1);
  end = clock();
  //print(a,N);
  printf("Sort method:Mergesort,Time cost:%5d ms\n",end - start);
  copy(x,a,N);
  start = clock();
  quicksort(a,0,N - 1);
  end = clock();
  //print(a,N);
  printf("Sort method:Quicksort,Time cost:%5d ms\n",end - start);
  return 0;
}
