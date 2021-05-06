#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#define Data 380                     //训练样本数目
#define TestData 126                 //预测样本数目
#define In 13                        //输入层神经元个数
#define Out 1                        //输出层神经元个数
#define Neuron 40                    //隐含层神经元个数
#define TrainC 40000                 //训练次数
#define WAlta 0.1                    //权值w的学习率
#define VAlta 0.2                    //权值v的学习率  
double d_in[Data][In];               //存储Data个样本，每个样本的In个输入，Out个输出
double d_out[Data][Out];
double t_in[TestData][In];           //存储TestData个样本，每个样本的In个输入，Out个输出
double t_out[TestData][Out];
double pre[TestData][Out];           //存储预测样本的实际输出
double v[Neuron][In];                //存储输入层到隐含层的权值
double y[Neuron];                    //存储隐含层的输出
double w[Out][Neuron];                  //存储隐含层到输出层的权值
double Maxin[In], Minin[In];            //存储样本输入的最大和最小值
double Maxout[Out], Minout[Out];        //存储样本输出的最大和最小值
double OutputData[Out];                 //存储神经网络的输出
double dw[Out][Neuron], dv[Neuron][In]; //存储权值w和v的修正量
double mse;                             //存储均方误差
double rmse;                            //存储均方根误差

//训练样本数据读入
void ReadData() {
	FILE *fp1, *fp2;
	char ch;       //每个数据之间有'，'相隔，用一个字符变量来存储'，'
	if ((fp1 = fopen("in.txt", "rb")) == NULL) {
		printf("不能打开in.txt文件\n");
		exit(0);
	}
	//读取训练样本集，并存放在数组中
		for (int i = 0; i < Data; i++) {
			for (int j = 0; j < In; j++) {
				if (j != 0) {
					fscanf(fp1, "%c", &ch);
			}
			fscanf(fp1, "%lf", &d_in[i][j]);
		}
	}
	fclose(fp1);
	if ((fp2 = fopen("out.txt", "rb")) == NULL) {
		printf("不能打开out.txt文件\n");
		exit(0);
	}
	for (int i = 0; i < Data; i++) {
		for (int j = 0; j < Out; j++) {
			fscanf(fp2, "%lf", &d_out[i][j]);
		}
	}
	fclose(fp2);
}

/*数据归一化处理，初始化神经网络*/
void InitBPNetwork() {
	//以当前时间对应的int值为随机序列起点
	srand((int)time(0));
	//找到每一维度数据的最大值和最小值
	for (int i = 0; i < In; i++) {
		Minin[i] = Maxin[i] = d_in[0][i];
		for (int j = 0; j < Data; j++) {
			Maxin[i] = Maxin[i] > d_in[j][i] ? Maxin[i] : d_in[j][i];
			Minin[i] = Minin[i] < d_in[j][i] ? Minin[i] : d_in[j][i];
		}
	}
	//找到输出数据房价的最大值和最小值
	for (int i = 0; i < Out; i++) {
		Minout[i] = Maxout[i] = d_out[0][i];
		for (int j = 0; j < Data; j++) {
			Maxout[i] = Maxout[i] > d_out[j][i] ? Maxout[i] : d_out[j][i];
			Minout[i] = Minout[i] < d_out[j][i] ? Minout[i] : d_out[j][i];
		}
	}
	//使用最大最小归一化输入数据
	for (int i = 0; i < In; i++) {
		for (int j = 0; j < Data; j++) {
			d_in[j][i] = (d_in[j][i] - Minin[i]) / (Maxin[i] - Minin[i]);
		}
	}
	//使用最大最小归一化输出数据
	for (int i = 0; i < Out; i++) {
		for (int j = 0; j < Data; j++) {
			d_out[j][i] = (d_out[j][i] - Minout[i]) / (Maxout[i] - Minout[i]);
		}
	}
	//使用随机值初始化神经网络的各权值（输入层到隐含层的权重）
	for (int i = 0; i < Neuron; i++) {
		for (int j = 0; j < In; j++) {
			v[i][j] = rand() * 2.0 / RAND_MAX - 1;  //权重取[-1,1]之间
			dv[i][j] = 0;
		}
	}
	//使用随机值初始化神经网络的各权值（隐含层到输出层的权重）
	for (int i = 0; i < Out; i++) {
		for (int j = 0; j < Neuron; j++) {
			w[i][j] = rand() * 2.0 / RAND_MAX - 1;  //权重取[-1,1]之间
			dw[j][i] = 0;
		}
	}
}

//前向传播
void ComputO(int var) {
	double sum;   //存放累加和
	//计算隐含层每个神经元的输出
	for (int i = 0; i < Neuron; i++) {
		sum = 0;
		for (int j = 0; j < In; j++) {
			sum += v[i][j] * d_in[var][j];
		}
		y[i] = 1 / (1 + exp(-1 * sum));
	}
	//计算输出层每个神经元的输出
	for (int i = 0; i < Out; i++) {
		sum = 0;
		for (int j = 0; j < Neuron; j++) {
			sum += w[i][j] * y[j];
		}
		OutputData[i] = 1 / (1 + exp(-1 * sum));
	}
}

//反向传播修正权值
void BackUpdate(int var) {
	double t;
	//遍历隐含层的每个神经元
	for (int i = 0; i < Neuron; i++) {
		t = 0;
		//修正隐含层与输出层之间的各权值
		for (int j = 0; j < Out; j++) {
			dw[j][i] = WAlta * (d_out[var][j] - OutputData[j]) * OutputData[j] * (1 - OutputData[j]) * y[i];
			w[j][i] += dw[j][i];
			t += (d_out[var][j] - OutputData[j]) * OutputData[j] * (1 - OutputData[j]) * w[j][i];
		}
		//修正隐含层与输入层之间的各权值
		for (int j = 0; j < In; j++) {
			dv[i][j] = VAlta * t * y[i] * (1 - y[i]) * d_in[var][j];
			v[i][j] += dv[i][j];
		}
	}
}

//训练神经网络
void TrainNetwork() {
	int count = 1;					      //记录训练次数
	do {
		mse = 0;					      //均方误差值设置为0
		//完成所有训练样本的一轮训练
		for (int i = 0; i < Data; i++) {
			ComputO(i);				      //前向传播
			BackUpdate(i);			      //反向传播，调整各连接权值
			//计算单个样本的误差
			for (int j = 0; j < Out; j++) {
				double tmp1 = OutputData[j] * (Maxout[0] - Minout[0]) + Minout[0];
				double tmp2 = d_out[i][j] * (Maxout[0] - Minout[0]) + Minout[0];
				mse += (tmp1 - tmp2) * (tmp1 - tmp2);  //累计平方误差
			}
		}
		mse = mse / Data * Out;		          //计算机均方误差
		//每隔1000次训练，显示一次训练误差，以便观察
		if (count % 1000 == 0) {
			printf("%d  %lf\n", count, mse);
		}
		count++;					          //累计训练次数
	} while (count <= TrainC && mse >= 1);  //超出训练次数或精度达到要求，则结束训练
	printf("训练结束\n");
}

//神经网络模型评估
void TestNetwork() {
	FILE *fp;
	char ch;
	//打开保存测试数据集的文件
		if ((fp = fopen("test.txt", "rb")) == NULL) {
			printf("不能打开test.txt文件\n");
			exit(0);
	}
	//输入测试数据集
	for (int i = 0; i < TestData; i++) {
		for (int j = 0; j < In + Out; j++) {
			if (j != 0) {
				fscanf(fp, "%c", &ch);
			}
			if (j < In) {
				fscanf(fp, "%lf", &t_in[i][j]);
			}
			else {
				fscanf(fp, "%lf", &t_out[i][j - In]);
			}
		}
	}
	fclose(fp);	//关闭文件
	double sum;
	//测试数据归一化处理
	for (int i = 0; i < In; i++) {
		for (int j = 0; j < TestData; j++) {
			t_in[j][i] = (t_in[j][i] - Minin[i]) / (Maxin[i] - Minin[i]);
		}
	}
	//计算每一个测试样本的预测结果
	for (int k = 0; k < TestData; k++) {
		//计算隐含层输出
		for (int i = 0; i < Neuron; i++) {
			sum = 0;
			for (int j = 0; j < In; j++) {
				sum += v[i][j] * t_in[k][j];
			}
			y[i] = 1 / (1 + exp(-1 * sum));
		}
		//计算输出层的预测结果
		sum = 0;
		for (int j = 0; j < Neuron; j++) {
			sum += w[0][j] * y[j];
		}
		//预测结果反归一化还原
		pre[k][0] = 1 / (1 + exp(-1 * sum)) * (Maxout[0] - Minout[0]) + Minout[0];
		//输出预测值和实际值
		printf("编号：%d 预测值：%.2lf 实际值：%.2lf\n", k + 1, pre[k][0], t_out[k][0]);
	}
	//计算均方根误差
	rmse = 0.0;
	for (int k = 0; k < TestData; k++) {
		rmse += (pre[k][0] - t_out[k][0]) * (pre[k][0] - t_out[k][0]);
	}
	rmse = sqrt(rmse / TestData);
	//输出均分根误差，查看测试精度
	printf("rmse：%.4lf\n", rmse);
}

int main(int argc, char const *argw[]) {
	ReadData();       	//输入训练数据集
	InitBPNetwork();  	//数据归一化处理，神经网络各连接权值的初始化
	TrainNetwork();   	//训练神经网络
	TestNetwork();	//神经网络模型评估
	return 0;
}