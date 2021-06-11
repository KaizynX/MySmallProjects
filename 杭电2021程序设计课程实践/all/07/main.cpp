/*
 * @Author: Kaizyn
 * @Date: 2021-06-06 20:50:59
 * @LastEditTime: 2021-06-10 13:30:33
 */
#include <bits/stdc++.h>
// #define DEBUG
using namespace std;
const int K = 3;                          //簇的数目
const int dimNum = 4;                     //维数
const int Neuron = 4;                    //隐含层神经元个数
const int TrainC = 20000;                 //训练次数

class NeuralNetwork {
 public:
  // 初始化各层数量
  NeuralNetwork(int l1, int l2, int l3) {
    w[0] = vector<vector<double>>(l1+1, vector<double>(l2));
    w[1] = vector<vector<double>>(l2+1, vector<double>(l3));
    z[1] = s[1] = vector<double>(l2+1);
    z[2] = s[2] = o = vector<double>(l3);
    this->l1=l1;
    this->l2=l2;
    this->l3=l3;
    //cout << l1 << ' ' << l2 << ' ' << l3 << endl;
  }
  //使用随机值初始化神经网络的各权值
  void init() {
    srand(time(0));
    for (auto &i : w)
      for (auto &j : i)
        for (auto &k : j)
          k = rand() * 2.0 / RAND_MAX - 1;  //权重取[-1,1]之间
  }
  void softmax(vector<double> &lhs, vector<double> &rhs) {
    double sum = 0;
    for (auto &v : lhs)
      sum += exp(v);
    for (unsigned i = 0; i < rhs.size(); ++i)
      rhs[i] = exp(lhs[i])/sum;
  }
  double sigmod(double v) {
    return 1/(1+exp(-v));
  }
  // 计算损失函数
  double calc_loss(int y) {
    return -log(o[y]);
  }
  // 前向传播
  void forward_propagation(const vector<double> &x) {
    s[0] = x;
    s[0].emplace_back(1);
    s[1][z[1].size()-1] = 1;
    for (int i = 0; i < 2; ++i) {
      for (unsigned j = 0; j < w[i][0].size(); ++j) {
        z[i+1][j] = 0;
        for (unsigned k = 0; k < w[i].size(); ++k) {
          z[i+1][j] += w[i][k][j]*s[i][k];
        }
        s[i+1][j] = sigmod(z[i+1][j]);
      }
    }
    softmax(s[2], o);
  }
  // 反向传播
  void back_propagation(int &y) {
//    for (unsigned i = 0; i < w[0].size(); ++i) {
//      for (unsigned j = 0; j < w[0][i].size(); ++j) {
//        // w[0][i][j] -= alta[0]*-(1-o[y])*w[1][j][y]*z[0][i];
//        w[0][i][j] -= alta[0]*-(1-o[y])*s[2][y]*(1-s[2][y])*w[1][j][y]*s[1][j]*(1-s[1][j])*s[0][i];
//      }
//    }
//    for (unsigned i = 0; i < w[1].size(); ++i) {
//      // w[1][i][y] -= alta[1]*-(1-o[y])*z[1][i];
//      w[1][i][y] -= alta[1]*-(1-o[y])*s[2][y]*(1-s[2][y])*s[1][i];
//    }

    for(int i = 0;i < l3;i++){
        if(i==y) da2[i]=-(1-o[y]);
        else da2[i]=-1.0/o[y]*(-1.0*o[i]*o[y]);
        dz2[i]=da2[i]*s[2][i]*(1-s[2][i]);
        for(int j = 0;j < l2;j++){
            dw[1][j][i]=dz2[i]*s[1][j];
        }
    }
    for(int i = 0;i < l2;i++){
        da1[i]=0;
        for(int j = 0;j < l3;j++){
            da1[i]+=w[1][i][j]*da2[j];
        }
        dz1[i]=da1[i]*s[1][i]*(1-s[1][i]);
        for(int j = 0;j < l1;j++){
            dw[0][j][i]=dz1[i]*s[0][j];
        }
    }
    for(int i = 0;i < l1;i++){
        for(int j = 0;j < l2;j++){
            w[0][i][j]-=alta[0]*dw[0][i][j];
        }
    }
    for(int i = 0;i < l2;i++){
        for(int j = 0;j < l3;j++){
            w[1][i][j]-=alta[1]*dw[1][i][j];
        }
    }
  }
  // 训练
  void train(vector<vector<double>> &X, vector<int> &y) {
    int count = 0;
    double loss = 0;
    do {
      loss = 0;
      count++;
      for (unsigned i = 0; i < y.size(); ++i) {
#ifdef DEBUG
        // cout << i << ':';
#endif
        forward_propagation(X[i]);
        loss += calc_loss(y[i]);
        back_propagation(y[i]);
      }
      loss /= y.size();
      //每隔1000次训练，显示一次训练误差，以便观察
      if (count%1000 == 0) {
#ifdef DEBUG
        print();
#endif
        cout << "训练次数:" << count << "\t交叉熵损失:" << loss << endl;
      }
    } while (loss >= 0.5 && count < TrainC);
    cout << "训练结束嘿呀! 训练次数:" << count << "\t交叉熵损失:" << loss << endl;
  }
  // 预测
  int predict(vector<double> &x) {
    forward_propagation(x);
    return max_element(o.begin(), o.end())-o.begin();
  }
#ifdef DEBUG
  void print() {
    for (auto &i : w) {
      for (auto &j : i) {
        for (auto &k : j) {
          cout << k << ' ';
        }
        cout << endl;
      }
      cout << endl;
    }
  }
#endif
 private:
  vector<vector<double>> w[2];
  vector<double> z[3], s[3], o;
  // double alta[2] = {2e-3, 1e-3}; // 学习率
  double alta[2] = {2e-1, 1e-1}; // 学习率
  double da1[10],da2[10],dz1[10],dz2[10],dw[2][5][5];
  int l1,l2,l3;
};

int dataNum;                                     //数据集中的数据记录总数
int train_num, test_num;
vector<vector<double>> data_x, train_data_x, test_data_x;
vector<int> data_y, train_data_y, test_data_y;
NeuralNetwork nn(dimNum, Neuron, K);

//数据读入
bool Inputs() {
  map<string, int> mp;
  string fname = "data.txt";//文件名
  string name; //存储鸢尾花的名字
  cout << "请输入存放数据的文件名：";
  cin >> fname;
  ifstream fp(fname);
  if (!fp.is_open()) return cout << ("不能打开输入的文件\n"), false;
  dataNum = 0;
  for (int i = 0, j = 0; !fp.eof(); i++, dataNum++) {
    char ch;
    data_x.emplace_back(vector<double>(dimNum));
    fp >> data_x[i][0] >> ch
       >> data_x[i][1] >> ch
       >> data_x[i][2] >> ch
       >> data_x[i][3] >> ch
       >> name;
    if (mp.count(name)) data_y.emplace_back(mp[name]);
    else data_y.emplace_back(mp[name] = j++);
  }
  fp.close();
  return true;
}

// 数据预处理，例如数据集打乱、种类维度的数据变换。
void RandomData() {
  srand(time(0));
  for (int i = 1; i < dataNum; ++i) {
    int j = rand()%i;
    swap(data_x[i], data_x[j]);
    swap(data_y[i], data_y[j]);
  }
}

// min max归一化
void Normalize() {
  double min_val, max_val;
  for (int i = 0; i < dimNum; ++i) {
    min_val = max_val = data_x[0][i];
    for (int j = 0; j < dataNum; ++j) {
      min_val = min(min_val, data_x[j][i]);
      max_val = max(max_val, data_x[j][i]);
    }
    // assert(max_val > min_val);
    for (int j = 0; j < dataNum; ++j) {
      data_x[j][i] = (data_x[j][i]-min_val)/(max_val-min_val);
    }
  }
}

// 数据集切分
void DivideData(double k = 0.7) {
  train_num = dataNum*k;
  test_num = dataNum-train_num;
  train_data_x.assign(data_x.begin(), data_x.begin()+train_num);
  train_data_y.assign(data_y.begin(), data_y.begin()+train_num);
  test_data_x.assign(data_x.begin()+train_num, data_x.end());
  test_data_y.assign(data_y.begin()+train_num, data_y.end());
}

// 预测准确度评估
double Accuracy() {
  double acc = 0;
  for (int i = 0; i < test_num; ++i) {
    acc += nn.predict(test_data_x[i]) == test_data_y[i];
  }
  return acc/test_num;
}

int main() {
  // 数据读入
  if (Inputs() == false) {     //判断数据样本读入是否成功
    return 0;
  }
  // 数据预处理，例如数据集打乱、种类维度的数据变换。
  RandomData();
  // 归一化
  Normalize();
  // 数据集切分
  DivideData();
  // 神经网络初始化
  nn.init();
  // 神经网络训练
  nn.train(train_data_x, train_data_y);
  // 预测准确度评估
  double acc = Accuracy();
  cout << "准确率:" << acc << '\n';
  system("pause");
  return 0;
}
/*
data.txt
150
*/
