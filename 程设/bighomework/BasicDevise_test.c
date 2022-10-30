#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>

#include "BasicDivise.h"

int main(){
  char a[10001]，b[10001],ans[10001];
  scanf("%s%s",a,b);
  strcpy(ans,devise(a,b));
  prinf("ans = %s\n",ans);
  return 0;
}
