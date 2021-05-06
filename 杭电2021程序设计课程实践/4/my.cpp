/*
 * @Author: Kaizyn
 * @Date: 2021-05-06 19:33:47
 * @LastEditTime: 2021-05-06 20:51:45
 */
#include <bits/stdc++.h>
using namespace std;
const int N = 1e2+7;

int dataNum;               //样本数目
double attri[13][N], price[N], min_in[13], max_in[13], min_out, max_out, r[13];
double w[14]; // w = (X'X)^(-1)X'y
int choose[13];
string Attribute_name[14];
// "CRIM", "ZN", "INDUS", "CHAS", "NOX", "RM", "AGE", "DIS", "RAD", "TAX", "PTRATIO", "B", "LSTAT", "MEDV"

//数据读入
bool Inputs() {
  string fname = "housing.txt";                         //存储文件名
  cout << "请输入存放数据的文件名：";
  cin >> fname;
  ifstream fp(fname);
  if (!fp.is_open()) return cout << "不能打开输入的文件\n", false;
  for (int i = 0; i < 14; ++i) fp >> Attribute_name[i];
  for (int i = 0; !fp.eof(); ++i, ++dataNum) {
    for (int j = 0; j < 13; ++j) fp >> attri[j][i];
    fp >> price[i];
  }
  fp.close();
  return true;
}

//使用最大最小归一化数据
void Normalization(double x[], double &min_val, double &max_val) {
  min_val = max_val = x[0];
  for (int i = 1; i < dataNum; ++i) {
    min_val = min(min_val, x[i]);
    max_val = max(max_val, x[i]);
  }
  for (int i = 0; i < dataNum; ++i) {
    x[i] = (x[i]-min_val)/(max_val-min_val);
  }
}

// 计算相关系数
double Correlation_coefficient(double x[], double y[]) {
  double ave_x = 0, ave_y = 0, var_x = 0, var_y = 0, cov = 0;
  for (int i = 0; i < dataNum; ++i) {
    ave_x += x[i];
    ave_y += y[i];
  }
  ave_x /= dataNum;
  ave_y /= dataNum;
  for (int i = 0; i < dataNum; ++i) {
    cov += (x[i]-ave_x)*(y[i]-ave_y);
    var_x += (x[i]-ave_x)*(x[i]-ave_x);
    var_y += (y[i]-ave_y)*(y[i]-ave_y);
  }
  return cov/sqrt(var_x*var_y);
}

//线性回归
void LineReg() {
  ;
}

double Predict(double x[13]) {
  return x[0]+x[1];
}

//输出
void Outputs() {
  static double x[4], y;
  for (int i = 0; i < 4; ++i) {
    cout << "请输入房屋的" << Attribute_name[choose[i]] << "属性值:";
    cin >> x[i];
  }
  y = Predict(x);
  cout << "预计房价为：" << y << "元\n";
}

int main() {
  if (!Inputs()) return 0;    //判断数据样本读入是否成功
  // 归一化
  for (int i = 0; i < 13; ++i) Normalization(attri[i], min_in[i], max_in[i]);
  Normalization(price, min_out, max_out);
  // 相关系数
  for (int i = 0; i < 13; ++i) r[i] = Correlation_coefficient(attri[i], price);
  // 挑选四个最相关的维度
  iota(choose, choose+13, 0);
  sort(choose, choose+13, [&](int x, int y) {
    return r[i] > r[y];
  });
  // 多元线性回归
  LineReg();
  Outputs();
  system("pause");
  return 0;
}