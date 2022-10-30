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
#include<string.h>
#include<math.h>

#define bool int
#define false 0
#define true 1
#define K 3
#define dimNum 4
#define MAX_ROUNDS 100

struct Iris{
  double sepalLength;
  double sepalWidth;
  double petalLength;
  double petalWidth;
  char irisname[20];
  int clusterID;
};

int isContinue;
struct Iris iris[150];//鸢尾花数据
struct Iris clusterCenter[K];//质心
struct Iris centerCalc[K];//新质心
int dataNum;
int clusterCenterInitIndex[K];
double distanceFromCenter[K];//到质心距离
int dataSizePerCluster[K];//每种花的个数

bool Compname(char a[],char b[]){//比较花名
  for(int i = 0;i < 20;i++){
    if(a[i] != b[i]) return false;
  }
  return true;
}

bool Inputs(){
  char fname[256];
  printf("Input filename:\n");
  scanf("%s",fname);
  printf("dataNum:\n");
  scanf("%d",&dataNum);
  FILE* fp = fopen(fname,"rb");
  if(fp == NULL){
    printf("can't open the file!\n");
    return false;
  }
  for(int i = 0;i < dataNum;i++){
    fscanf(fp,"%lf,%lf,%lf,%lf,%s",&iris[i].sepalLength,&iris[i].sepalWidth,&iris[i].petalLength,&iris[i].petalWidth,iris[i].irisname);
    iris[i].clusterID = -1;
  }
  fclose(fp);
  return true;
}

void InitialCluster(){//随机选取质心
  int random;
  for(int i = 0;i < K;i++){
    clusterCenterInitIndex[i] = -1;
  }
  for(int i = 0;i < K;i++){
    random = rand() % (dataNum -1);
    int j = 0;
    while(j < i){
      if(random == clusterCenterInitIndex[j]){
        random = rand() % (dataNum - 1);
        j = 0;
      }else{
        j++;
      }
    }
    clusterCenterInitIndex[i] = random;
  }
  for(int i = 0;i < K;i++){
    clusterCenter[i].sepalLength = iris[clusterCenterInitIndex[i]].sepalLength;
    clusterCenter[i].sepalWidth = iris[clusterCenterInitIndex[i]].sepalWidth;
    clusterCenter[i].petalLength = iris[clusterCenterInitIndex[i]].petalLength;
    clusterCenter[i].petalWidth = iris[clusterCenterInitIndex[i]].petalWidth;
    strcpy(clusterCenter[i].irisname,iris[clusterCenterInitIndex[i]].irisname);
    clusterCenter[i].clusterID = i;
    iris[clusterCenterInitIndex[i]].clusterID = i;
  }
}

void CalDistance2OneCenters(int pointID,int centerID){
  double x1 = pow((iris[pointID].sepalLength - clusterCenter[centerID].sepalLength),2.0);
  double x2 = pow((iris[pointID].sepalWidth - clusterCenter[centerID].sepalWidth),2.0);
  double x3 = pow((iris[pointID].petalLength - clusterCenter[centerID].petalLength),2.0);
  double x4 = pow((iris[pointID].petalWidth - clusterCenter[centerID].petalWidth),2.0);
  distanceFromCenter[centerID] = sqrt(x1 + x2 + x3 + x4);
}

void CalDistance2AllCenters(int pointID){
  for(int i = 0;i < K;i++){
    CalDistance2OneCenters(pointID,i);
  }
}

void Partition4OnePoint(int pointID){
  int minIndex = 0;
  double minValue = distanceFromCenter[0];
  for(int i = 0;i < K;i++){
    if(distanceFromCenter[i]<minValue){
      minValue = distanceFromCenter[i];
      minIndex = i;
    }
  }
  iris[pointID].clusterID = clusterCenter[minIndex].clusterID;
}

void Partition4ALLPointOneCluster(){
  for(int i = 0;i < dataNum;i++){
    if(iris[i].clusterID != -1){
      continue;
    }else{
      CalDistance2AllCenters(i);
      Partition4OnePoint(i);
    }
  }
}

void CompareNewOldClusterCenter(){
  isContinue = 0;
  for(int i = 0;i < K;i++){
    if(centerCalc[i].sepalLength != clusterCenter[i].sepalLength || centerCalc[i].sepalWidth != clusterCenter[i].sepalWidth || centerCalc[i].petalLength != clusterCenter[i].petalLength || centerCalc[i].petalWidth != clusterCenter[i].petalWidth){
      isContinue = 1;
      break;
    }
  }
}

void CalClusterCenter(){
  memset(centerCalc,0,sizeof(centerCalc));
  memset(dataSizePerCluster,0,sizeof(dataSizePerCluster));
  for(int i = 0;i < dataNum;i++){
    centerCalc[iris[i].clusterID].sepalLength += iris[i].sepalLength;
    centerCalc[iris[i].clusterID].sepalWidth += iris[i].sepalWidth;
    centerCalc[iris[i].clusterID].petalLength += iris[i].petalLength;
    centerCalc[iris[i].clusterID].petalWidth += iris[i].petalWidth;
    //strcpy(centerCalc[iris[i].clusterID].irisname,iris[i].irisname);
    dataSizePerCluster[iris[i].clusterID]++;
  }
  for(int i = 0;i < K;i++){
    strcpy(centerCalc[i].irisname,clusterCenter[i].irisname);
    if(dataSizePerCluster[i] != 0){
      centerCalc[i].sepalLength = centerCalc[i].sepalLength / (double)dataSizePerCluster[i];
      centerCalc[i].sepalWidth = centerCalc[i].sepalWidth / (double)dataSizePerCluster[i];
      centerCalc[i].petalLength = centerCalc[i].petalLength / (double)dataSizePerCluster[i];
      centerCalc[i].petalWidth = centerCalc[i].petalWidth / (double)dataSizePerCluster[i];
      printf("cluster %d point cnt: %d\n",i,dataSizePerCluster[i]);
      printf("cluster %d center: sepalLength:%.2lf,sepalWidth:%.2lf,petalLength:%.2lf,petalWidth:%.2lf,irisname:%s\n",i,centerCalc[i].sepalLength,centerCalc[i].sepalWidth,centerCalc[i].petalLength,centerCalc[i].petalWidth,centerCalc[i].irisname);
      /*for(int j = 0;j < dataNum;j++){
        if(iris[j].clusterID == i)
        printf("sepalLength:%.2lf,sepalWidth:%.2lf,petalLength:%.2lf,petalWidth:%.2lf,irisname:%s\n",iris[j].sepalLength,iris[j].sepalWidth,iris[j].petalLength,iris[j].petalWidth,iris[j].irisname);
      }*/
    }else{
      printf("cluster %d count is zero!\n",i);
    }
  }

  CompareNewOldClusterCenter();

  for(int i = 0;i < K;i++){
    clusterCenter[i].sepalLength = centerCalc[i].sepalLength;
    clusterCenter[i].sepalWidth = centerCalc[i].sepalWidth;
    clusterCenter[i].petalLength = centerCalc[i].petalLength;
    clusterCenter[i].petalWidth = centerCalc[i].petalWidth;
    clusterCenter[i].clusterID = i;
    //strcpy(clusterCenter[i].irisname,centerCalc[i].irisname);
  }

  if(isContinue == 1){
    for(int i = 0;i < dataNum;i++){
     iris[i].clusterID = -1;
    }
  }
}

void KMeans(){
  int rounds;
  for(rounds = 0;rounds < MAX_ROUNDS;rounds++){
    printf("Rounds:%d\n",rounds++);
    Partition4ALLPointOneCluster();
    CalClusterCenter();
    if(isContinue == 0){
      printf("Complete!\n");
      break;
    }
  }
}

double accurate(int pointID){
  int sum = 0;
  for(int i = 0;i < dataNum;i++){
    if(Compname(iris[i].irisname,clusterCenter[pointID].irisname) && iris[i].clusterID == pointID){
      sum++;
    }
  }
  printf("\n");
  double accuracy = (double)sum / dataSizePerCluster[pointID];
  printf("cluster %d accuracy:%.2lf%%\n",pointID,accuracy * 100);
  return accuracy;
}

int main(){
  if(Inputs() == false){
    return 0;
  }
  InitialCluster();
  printf("InitialCluster:\n");
  for(int i = 0;i < K;i++){
    printf("%.2lf,%.2lf,%.2lf,%.2lf,%s\n",clusterCenter[i].sepalLength,clusterCenter[i].sepalWidth,clusterCenter[i].petalLength,clusterCenter[i].petalWidth,clusterCenter[i].irisname);
  }
  KMeans();
  for(int i = 0;i < K;i++){
    for(int j = 0;j < dataNum;j++){
      if(iris[j].clusterID == i)
        printf("No%d:sepalLength:%.2lf,sepalWidth:%.2lf,petalLength:%.2lf,petalWidth:%.2lf,irisname:%s,ID:%d\n",j,iris[j].sepalLength,iris[j].sepalWidth,iris[j].petalLength,iris[j].petalWidth,iris[j].irisname,iris[j].clusterID);
    }
  }
  double aveacu = (accurate(0) * dataSizePerCluster[0] + accurate(1) * dataSizePerCluster[1] + accurate(2) * dataSizePerCluster[2]) / dataNum;
  printf("Total accuracy:%.2lf%%",aveacu * 100);
  return 0;
}
