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
#include<time.h>
#include<stdlib.h>

#define data 380 //训练样本数目
#define testdata 126 //预测样本数目
#define innum 13 //输入层神经元个数
#define outnum 1 //输出层神经元个数
#define neuronnum 10 // 隐含层神经元个数
#define traintime 40000// 训练次数
#define Wlearn 0.12
#define Vlearn 0.5

double data_in[data][innum];
double data_out[data][outnum];
double test_in[testdata][innum];
double test_out[testdata][outnum];
double real[testdata][outnum]; //存储样本实际输出
double v[neuronnum][innum]; //存储输入层到隐含层的权值
double y[neuronnum]; // 存储隐含层的输出
double w[outnum][neuronnum]; // 存储隐含层到输出层的权值
double max_in[innum],min_in[innum];
double max_out[outnum],min_out[outnum];
double output_data[outnum]; // 存储输出
double dw[outnum][neuronnum],dv[neuronnum][innum];
double mse;
double rmse;

void ReadData(){
  FILE* fp1,* fp2;
  char ch;
  if((fp1 = fopen("in.txt","rb")) == NULL){
    printf("Can't open in.txt!\n");
    exit(0);
  }

  for(int i = 0;i < data;i++){
    for(int j = 0;j < innum;j++){
      if(j != 0){
        fscanf(fp1,"%c",&ch);
      }
      fscanf(fp1,"%lf",&data_in[i][j]);
    }
  }
  fclose(fp1);
  if((fp2 = fopen("out.txt","rb")) == NULL){
    printf("Can't open out.txt!\n");
    exit(0);
  }

  for(int i = 0;i < data;i++){
    for(int j = 0;j < outnum;j++){
      fscanf(fp2,"%lf",&data_out[i][j]);
    }
  }
  fclose(fp2);
}

void Initial(){
  srand((int)time(0));

  for(int i = 0;i < innum;i++){
    min_in[i] = max_in[i] = data_in[0][i];
    for(int j = 0;j < data;j++){
      if(max_in[i] < data_in[j][i]) max_in[i] = data_in[j][i];
      if(min_in[i] > data_in[j][i]) min_in[i] = data_in[j][i];
    }
  }
  for(int i = 0;i < outnum;i++){
    min_out[i] = max_out[i] = data_out[0][i];
    for(int j = 0;j < data;j++){
      if(max_out[i] < data_out[j][i]) max_out[i] = data_out[j][i];
      if(min_out[i] > data_out[j][i]) min_out[i] = data_out[j][i];
    }
  }
  //归一化处理
  for(int i = 0;i < innum;i++){
    for(int j = 0;j < data;j++){
      data_in[j][i] = (data_in[j][i] - min_in[i]) / (max_in[i] - min_in[i]);
    }
  }

  for(int i = 0;i < outnum;i++){
    for(int j = 0;j < data;j++){
      data_out[j][i] = (data_out[j][i] - min_out[i]) / (max_out[i] - min_out[i]);
    }
  }

  for(int i = 0;i < neuronnum;i++){
    for(int j = 0;j < innum;j++){
      v[i][j] = rand() * 2.0 / RAND_MAX - 1;
      dv[i][j] = 0;
    }
  }

  for(int i = 0;i < outnum;i++){
    for(int j = 0;j < neuronnum;j++){
      w[i][j] = rand() * 2.0 / RAND_MAX - 1;
      dw[i][j] = 0;
    }
  }
}

double sigmoid(double z) {
	return 1 / (1 + exp(-z));
}

void Compute_output(int var){
  double sum;
  for(int i = 0;i < neuronnum;i++){
    sum = 0;
    for(int j = 0;j < innum;j++){
      sum += v[i][j] * data_in[var][j];
    }
    y[i] = sigmoid(sum);
  }

  for(int i = 0;i < outnum;i++){
    sum = 0;
    for(int j = 0;j < neuronnum;j++){
      sum += w[i][j] * y[j];
    }
    output_data[i] = sigmoid(sum);
  }
}

void BackUpdate(int var){
  double t;
  for(int i = 0;i < neuronnum;i++){
    t = 0;
    for(int  j = 0;j < outnum;j++){
      dw[j][i] = Wlearn * (data_out[var][j] - output_data[j]) * output_data[j] * (1 - output_data[j]) * y[j];
      w[j][i] += dw[j][i];
      t += (data_out[var][j] - output_data[j]) * output_data[j] * (1 - output_data[j]) * w[j][i];
    }

    for(int j = 0;j < innum;j++){
      dv[i][j] = Vlearn * t * y[i] * (1 - y[i]) * data_in[var][j];
      v[i][j] += dv[i][j];
    }
  }
}

void TrainNetwork(){
  int count = 1;
  do{
    mse = 0;
    for(int i = 0;i < data;i++){
      Compute_output(i);
      BackUpdate(i);

      for(int j = 0;j < outnum;j++){
        double tmp1 = output_data[j] * (max_out[0] - min_out[0]) + min_out[0];
        double tmp2 = data_out[i][j] * (max_out[0] - min_out[0]) + min_out[0];
        mse += (tmp1 - tmp2) * (tmp1 - tmp2);
      }
    }
    mse = mse / data * outnum;

    if(count % 1000 == 0){
      printf("%d %lf\n",count,mse);
    }
    count++;
  }while(count <= traintime && mse >= 1);
  printf("Train Complete!\n");
}

void TestNetwork(){
  FILE* fp;
  char ch;
  if((fp = fopen("test.txt","rb")) == NULL){
    printf("Can't open the file!\n");
    exit(0);
  }

  for(int i = 0;i < testdata;i++){
    for(int j = 0;j < innum + outnum;j++){
      if(j != 0){
        fscanf(fp,"%c",&ch);
      }
      if(j < innum){
        fscanf(fp,"%lf",&test_in[i][j]);
      }else{
        fscanf(fp,"%lf",&test_out[i][j - innum]);
      }
    }
  }
  fclose(fp);

  double sum;
  for(int i = 0;i < innum;i++){
    for(int j = 0;j < testdata;j++){
      test_in[j][i] = (test_in[j][i] - min_in[i]) / (max_in[i] - min_in[i]);
    }
  }

  for(int k = 0;k < testdata;k++){
    for(int i = 0;i < neuronnum;i++){
      sum = 0;
      for(int j = 0;j < innum;j++){
        sum += v[i][j] * test_in[k][j];
      }
      y[i] = 1 / (1 + exp(-1 * sum));
    }

    sum = 0;
    for(int j = 0;j < neuronnum;j++){
      sum += w[0][j] * y[j];
    }
    real[k][0] = 1 / (1 + exp(-1 * sum)) * (max_out[0] - min_out[0]) + min_out[0];
    printf("No:%d Predicted Value:%.2lf Real Value:%.2lf\n",k + 1,real[k][0],test_out[k][0]);
  }

  rmse = 0.0;
  for(int k = 0;k < testdata;k++){
    rmse += (real[k][0] - test_out[k][0]) * (real[k][0] - test_out[k][0]);
  }
  rmse = sqrt(rmse / testdata);
  printf("rmse:%.4lf\n",rmse);
}

int main(int argc, char const *argv[]) {
  ReadData();
  Initial();
  TrainNetwork();
  TestNetwork();
  return 0;
}
