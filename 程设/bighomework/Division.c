#include<stdio.h>
#include<string.h>

#define bool int
#define true 1
#define false 0
char dividend[1000],divisor[1000];
int quotient[1000];

void int_test(int a){
  printf("%d\n",a);
}
void char_test(char a){
  printf("%c\n",a);
}
void char_array_test(char a[],int size){
  for(int i = 0;i < size;i++){
    printf("%c ",a[i]);
  }
  printf("\n");
}
void int_array_test(int a[],int size){
  for(int i = 0;i < size;i++){
    printf("%d ",a[i]);
  }
  printf("\n");
}
/*此为减法函数，用于将当前被除数所截取部分与除数相减
*dividend为被除数,divisor为除数,len为除数长度
*/
void Sub(int begin,int len){
  for(int i = begin;i < begin + len;i++){
    dividend[i] = dividend[i] - divisor[i] + '0';
  }
  for(int i = begin + len - 1;i > begin;i--){
    if(dividend[i] < '0'){
      dividend[i] += 10;
      dividend[i - 1]--;
    }
  }
}

/*
*高精度除法
*dividend为被除数，divisor为除数，quotient为商
*/
char* Divise(char a[],char b[]){
	strcpy(dividend,a);
	strcpy(divisor,b);
  int len1=strlen(dividend);
  int len2=strlen(divisor);
	if(len2 == 1 && divisor[0] == '0'){ //除数为0
		//printf("除数不能为0！\n");
		char *c;
		c = "除数不能为0！\n";
		return c;
	}
  if(len1 < len2 || (len1 == len2 && strcmp(dividend,divisor) < 0)){ //被除数小于除数
    char *c;
		c = "0\n";
		return c;
	}
  int index = 0;//记录当前商的位置
  while(1){
		quotient[index] = 0;
		while(strncmp(dividend,divisor,len2) >= 0){//被除数大于等于除数
      Sub(index,len2);
			quotient[index]++;
      char_array_test(dividend,len1);
		}
	  index++;//得到当前位的商，计算下一位
    for(int i = index + len2 - 1;i >= index;i--){
        divisor[i + 1] = divisor[i];
    }
    divisor[index]='0';
    divisor[index + len2]='\0';
    char_array_test(divisor,len2);
  }

	char ans[index];
  for(int i = 0;i < index;i++){
		ans[i] = quotient[i] + '0';
		printf("%d",quotient[i]);
  }
  char* c = ans;
	return c;
}

int main(){
	char a[500],b[500],*c;
	scanf("%s",a);
	scanf("%s",b);
  char_array_test(dividend,strlen(dividend));
  char_array_test(divisor,strlen(divisor));

	//c = Divise(a,b);
	//printf("%s",c);
}
