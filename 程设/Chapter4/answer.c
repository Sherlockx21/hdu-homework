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
#include<math.h>
#include<limits.h>
#define bool int
#define false 0
#define true 1

struct Data{
  double area;
  double price;
};

struct Data data[50];

int dataNum;
double a,b;
double sumXY;//x*y总和
double sumX;//x总和
double sumY;//y总和
double sumXX;//x*x总和

bool Inputs(){
  char fname[256];
  printf("Input filename:\n");
  scanf("%s",fname);
  printf("Sample amount:\n");
  scanf("%d",&dataNum);
  FILE* fp = fopen(fname,"rb");
  if(fp == NULL){
    printf("Can't open the file!\n");
    return false;
  }
  for(int i = 0;i < dataNum;i++){
    fscanf(fp,"%lf,%lf",&data[i].area,&data[i].price);
  }
  fclose(fp);
  return true;
}

void Init(){
  a = b = sumXY = sumX = sumY = sumXX = 0;
}

void LineReg(){
  for(int i = 0;i < dataNum;i++){
    sumXY += data[i].area * data[i].price;
    sumX += data[i].area;
    sumY += data[i].price;
    sumXX += data[i].area * data[i].area;
  }
  b = (sumXY * dataNum - sumX * sumY) / (sumXX * dataNum - sumX * sumX);
  a = sumY / dataNum - b * sumX / dataNum;
  printf("Y = %.2lfX + %.2lf\n",b,a);
}

double Outputs(double x){
  double y;
  y = a + b * x;
  return y;
}

double calcprice[50];

void MAD(){//平均绝对误差
  double sum = 0;
  for(int i = 0;i < dataNum;i++){
    calcprice[i] = Outputs(data[i].area);
    double error = (calcprice[i] - data[i].price);
    if(error < 0) error = -error;
    sum += error;
  }
  printf("MAD:%.2lf\n",sum / dataNum);
}

void LAD(){//最小绝对误差
  double min = INT_MAX;
  for(int i = 0;i < dataNum;i++){
    calcprice[i] = Outputs(data[i].area);
    double error = (calcprice[i] - data[i].price);
    if(error < 0) error = -error;
    if(min > error) min = error;
  }
  printf("LAD:%.2lf\n",min);
}

void HAD(){//最大绝对误差
  double max = INT_MIN;
  for(int i = 0;i < dataNum;i++){
    calcprice[i] = Outputs(data[i].area);
    double error = (calcprice[i] - data[i].price);
    if(error < 0) error = -error;
    if(max < error) max = error;
  }
  printf("HAD:%.2lf\n",max);
}

void MRE(){//平均相对误差
  double sum = 0;
  for(int i = 0;i < dataNum;i++){
    calcprice[i] = Outputs(data[i].area);
    double error = (calcprice[i] - data[i].price) / data[i].price;
    if(error < 0) error = -error;
    sum += error;
  }
  printf("MRE:%.2lf%%\n",sum / dataNum * 100);
}

int main(){
  if(Inputs() == false){
    return 0;
  }
  Init();
  LineReg();
  MAD();
  LAD();
  HAD();
  MRE();
  return 0;
}
