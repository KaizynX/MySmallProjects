/*
 * @Author: Kaizyn
 * @Date: 2021-05-13 15:53:46
 * @LastEditTime: 2021-05-24 16:44:24
 */
#include <bits/stdc++.h>
using namespace std;
const int  K = 3;                        	//簇的数目
const int dimNum = 4;                   	//维数
const int MAX_ROUNDS = 100;                         //最大允许的迭代次数

//存储鸢尾花数据的结构体
struct Iris {
	double sepalLength;             	//花萼长度
	double sepalWidth;              	//花萼宽度
	double petalLength;             	//花瓣长度
	double petalWidth;              	//花瓣宽度
	int clusterID;                  	//用于存放该点所属的簇群编号
};

int isContinue;                                 //判断是否继续聚类
Iris iris[150];                         //记录鸢尾花的数据
Iris clusterCenter[K];     	//存储质心
Iris centerCalc[K];      	//计算新质心
int dataNum;                                     //数据集中的数据记录总数
int clusterCenterInitIndex[K];    	//记录每个质心最初使用的数据点的编号
double distanceFromCenter[K];    	//记录点到质心的距离
int dataSizePerCluster[K];        	//每个簇群点的个数

//数据读入
bool Inputs() {
  string fname;//文件名
	string name; //存储鸢尾花的名字
	cout << "请输入存放数据的文件名：";
	cin >> fname;
	cout << "\n样本数目dataNum：\n";
	cin >> dataNum;
	ifstream fp(fname);
	if (!fp.is_open()) return cout << ("不能打开输入的文件\n"), false;
	for (int i = 0; i < dataNum; i++) {
		fp >> iris[i].sepalLength >> iris[i].sepalWidth >> iris[i].petalLength >> iris[i].petalWidth >> name;
		iris[i].clusterID = -1; //cluster id 初值为-1
	}
	fp.close();
	return true;
}

//初始化簇群
void InitialCluster() {
	int random; //存放随机数的变量
	//将K个质心的编号初始化为-1
		for (int i = 0; i < K; i++) {
			clusterCenterInitIndex[i] = -1;
	}
	//随机产生K个质心编号（不能重复）
	for (int i = 0; i < K; i++) {
		random = rand() % (dataNum - 1);  //随机产生0到dataNum -1之间的随机整数
		int j = 0;
		//与前i个中心编号进行比对，判断是否有重复
		while (j < i) {
			if (random == clusterCenterInitIndex[j]) {
				random = rand() % (dataNum - 1);
				j = 0;
			}
			else {
				j++;
			}
		}
		clusterCenterInitIndex[i] = random;   //设置第i个质心的编号
	}
	//确定K个质心编号后，将样本数组iris中对应编号的数据赋值给质心结构体数组clusterCenter
	for (int i = 0; i < K; i++) {
		clusterCenter[i].sepalLength = iris[clusterCenterInitIndex[i]].sepalLength;
		clusterCenter[i].sepalWidth = iris[clusterCenterInitIndex[i]].sepalWidth;
		clusterCenter[i].petalLength = iris[clusterCenterInitIndex[i]].petalLength;
		clusterCenter[i].petalWidth = iris[clusterCenterInitIndex[i]].petalWidth;
		clusterCenter[i].clusterID = i;    //将该类的编号设置为i
		//将iris中该质心的类编号设置为i
		iris[clusterCenterInitIndex[i]].clusterID = i;
	}
}

//计算一个点到一个质心的距离
void CalDistance2OneCenters(int pointID, int centerID) {
	double x1 = pow((iris[pointID].sepalLength - clusterCenter[centerID].sepalLength), 2.0);
	double x2 = pow((iris[pointID].sepalWidth - clusterCenter[centerID].sepalWidth), 2.0);
	double x3 = pow((iris[pointID].petalLength - clusterCenter[centerID].petalLength), 2.0);
	double x4 = pow((iris[pointID].petalWidth - clusterCenter[centerID].petalWidth), 2.0);
	distanceFromCenter[centerID] = sqrt(x1 + x2 + x3 + x4);
}

//计算一个点到所有质心的距离
void CalDistance2AllCenters(int pointID) {
	for (int i = 0; i < K; i++) {
		CalDistance2OneCenters(pointID, i);   //计算一个点到一个质心的距离
	}
}

//将一个点划分到距离最近的簇群
void Partition4OnePoint(int pointID) {
	int minIndex = 0;//记录距离最近的质心编号
	//求解最短距离，并更新距离最近的质心编号
	double minValue = distanceFromCenter[0];
	for (int i = 0; i < K; i++) {
		if (distanceFromCenter[i] < minValue) {
			minValue = distanceFromCenter[i];
			 minIndex = i;
		}
	}
	//将点的类标号设置为最近质心所在的类标号
	iris[pointID].clusterID = clusterCenter[minIndex].clusterID;
}

//每一轮聚类，需要将所有点都划分到距离最近的簇群中
void Partition4AllPointOneCluster() {
	for (int i = 0; i < dataNum; i++) {
		if (iris[i].clusterID != -1) {
			continue; //这个点就是质心，不需要划分簇群
		}
		else {
			CalDistance2AllCenters(i);    //计算第i个点到所有质心的距离
			Partition4OnePoint(i);         //将第i个点划分到距离最近的簇群
		}
	}
}

//比较新旧质心值的差别。如果是相等的，则停止迭代聚类
void CompareNewOldClusterCenter() {
	isContinue = 0;       //初始化标记变量isContinue的值为0; 0表示停止聚类，1表示继续聚类
	for (int i = 0; i < K; i++) {
		if (centerCalc[i].sepalLength != clusterCenter[i].sepalLength || centerCalc[i].sepalWidth != clusterCenter[i].sepalWidth || centerCalc[i].petalLength != clusterCenter[i].petalLength || centerCalc[i].petalWidth != clusterCenter[i].petalWidth) {
			isContinue = 1;//如果有一个质心值不同，就将isContinue 的值设置为1，表示需要继续聚类
			break;          //跳出循环
		}
	}
}

//重新计算新的质心
void CalClusterCenter() {
	//初始化所需的数组，让数组中各元素值为0
	memset(centerCalc, 0, sizeof(centerCalc));
	memset(dataSizePerCluster, 0, sizeof(dataSizePerCluster));
	//分别对每个簇群内的每个点的四个特征求和，并计算每个簇群内点的个数
	for (int i = 0; i < dataNum; i++) {
		centerCalc[iris[i].clusterID].sepalLength += iris[i].sepalLength;
		centerCalc[iris[i].clusterID].sepalWidth += iris[i].sepalWidth;
		centerCalc[iris[i].clusterID].petalLength += iris[i].petalLength;
		centerCalc[iris[i].clusterID].petalWidth += iris[i].petalWidth;
		dataSizePerCluster[iris[i].clusterID]++;
	}
	//计算每个簇群内点的四个特征值的均值作为新的质心
	for (int i = 0; i < K; i++) {
		if (dataSizePerCluster[i] != 0) {
			centerCalc[i].sepalLength = centerCalc[i].sepalLength / (double)dataSizePerCluster[i];
			centerCalc[i].sepalWidth = centerCalc[i].sepalWidth / (double)dataSizePerCluster[i];
			centerCalc[i].petalLength = centerCalc[i].petalLength / (double)dataSizePerCluster[i];
			centerCalc[i].petalWidth = centerCalc[i].petalWidth / (double)dataSizePerCluster[i];
			printf("cluster %d point cnt:%d\n", i, dataSizePerCluster[i]);//输出每个簇群的总数
			printf("cluster %d center：sepalLength:%.2lf, sepalwidth:%.2lf, petalLength:%.2lf, petalWidth:%.2lf\n", i, centerCalc[i].sepalLength, centerCalc[i].sepalWidth, centerCalc[i].petalLength, centerCalc[i].petalWidth);
		}
		else {
			printf(" cluster %d count is zero\n", i);
		}
	}

	//比较新旧质心值的差别。如果是相等，则停止迭代聚类
	CompareNewOldClusterCenter();

	//将新的质心的值放入质心结构体中
	for (int i = 0; i < K; i++) {
		clusterCenter[i].sepalLength = centerCalc[i].sepalLength;
		clusterCenter[i].sepalWidth = centerCalc[i].sepalWidth;
		clusterCenter[i].petalLength = centerCalc[i].petalLength;
		clusterCenter[i].petalWidth = centerCalc[i].petalWidth;
		clusterCenter[i].clusterID = i;
	}

	//重新计算新的质心后，要重新为每一个点进行聚类，所以数据集中所有点的clusterID都要重置为-1
	for (int i = 0; i < dataNum; i++) {
		iris[i].clusterID = -1;
	}
}

//KMeans算法核心代码
void KMeans() {
	int rounds;
	for (rounds = 0; rounds < MAX_ROUNDS; rounds++) {
		printf("\nRounds：%d            \n", rounds + 1);//显示聚类次数
		Partition4AllPointOneCluster();     //将每个点划分到距离最近的簇群
		CalClusterCenter();                 //重新计算新的质心
		if (isContinue == 0) {              //判断是否继续聚类
			printf("\n经过 %d 次聚类, 聚类完成！\n", rounds + 1);
			break;   //结束聚类
		}
	}
}

// 数据预处理，例如数据集打乱、种类维度的数据变换。
void RandomData() {
	;
}


int main() {
	if (Inputs() == false) {     //判断数据样本读入是否成功
		return 0;
	}
  // 数据预处理，例如数据集打乱、种类维度的数据变换。
	RandomData();
	InitialCluster();
	KMeans();
	system("pause");
	return 0;
}