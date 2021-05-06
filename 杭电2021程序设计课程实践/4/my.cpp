/*
 * @Author: Kaizyn
 * @Date: 2021-05-06 19:33:47
 * @LastEditTime: 2021-05-06 22:41:12
 */
#include <bits/stdc++.h>
using namespace std;
const int N = 1e2+7;

template <typename U>
class Martix {
 public:
  Martix() {}
  Martix(const int &_n, const int &_m = 1) : n(_n), m(_m) {
    a = vector<vector<U>>(n, vector<U>(m, 0));
  }
  bool empty() const { return n == 0 || m == 0; }
  vector<U>& operator [] (const int &i) { return a[i]; }
  void I(const int &_n) {
    n = m = _n;
    a = vector<vector<U>>(n, vector<U>(n, 0));
    for (int i = 0; i < n; ++i) a[i][i] = 1;
  }
  Martix T() const {
    Martix t(m, n);
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j)
        t[j][i] = a[i][j];
    return t;
  }
  Martix& operator *=(const Martix &mx) { return *this = *this*mx; }
  friend Martix operator *(const Martix &m1, const Martix &m2) {
    assert(m1.m == m2.n);
    Martix res(m1.n, m2.m);
    for (int i = 0; i < res.n; ++i)
      for (int j = 0; j < res.m; ++j)
        for (int k = 0; k < m1.m; ++k)
          res[i][j] += m1.a[i][k]*m2.a[k][j]; // MOD
    return res;
  }
  template <typename TT>
  Martix pow(const TT &p) const {
    assert(n == m);
    Martix res(n, m), a = *this;
    res.I(n);
    for (TT i = p; i; i >>= 1, a *= a) if (i&1) res *= a;
    return res;
  }
  friend Martix inv(const Martix &m) { return m.inv(); }
  Martix inv() const {
    assert(n == m);
    Martix res = *this;
    vector<int> is(n, -1), js(n, -1);
    for (int k = 0; k < n; ++k) {
      for (int i = k; i < n; ++i)
        for (int j = k; j < n; ++j) if (res[i][j]) {
          is[k] = i; js[k] = j; break;
        }
      if (is[k] == -1) return Martix(0);
      swap(res[k], res[is[k]]);
      // for (int i = 0; i < n; ++i) swap(res[k][i], res[is[k]][i]);
      for (int i = 0; i < n; ++i) swap(res[i][k], res[i][js[k]]);
      // res[k][k] = mul_inverse(res[k][k]); // get inv of number
      res[k][k] = 1.0/res[k][k];
      for (int j = 0; j < n; ++j) if (j != k)
        res[k][j] = res[k][j]*res[k][k];
      for (int i = 0; i < n; ++i) if (i != k)
        for (int j = 0; j < n; ++j) if (j != k)
          res[i][j] -= res[i][k]*res[k][j];
      for (int i = 0; i < n; ++i) if (i != k)
        res[i][k] = -res[i][k]*res[k][k];
    }
    for (int k = n-1; k >= 0; --k) {
      swap(res[k], res[js[k]]);
      // for (int i = 0; i < n; ++i) swap(res[js[k]][i], res[k][i]);
      for (int i = 0; i < n; ++i) swap(res[i][is[k]], res[i][k]);
    }
    return res;
  }
  friend ostream& operator <<(ostream &os, const Martix &mx) {
    for (int i = 0; i < mx.n; ++i)
      for (int j = 0; j < mx.m; ++j)
        os << mx[i][j] << " \n"[j==mx.m-1];
    return os;
  }
 private:
  int n, m;
  vector<vector<U>> a;
};

int dataNum;               //样本数目
double attri[13][N], price[N], min_in[13], max_in[13], min_out, max_out, r[13];
Martix<double> w; // w = (X'X)^(-1)X'y
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
  // w = (X'X)^(-1)X'y
  Martix<double> X(dataNum, 5), y(dataNum, 1);
  for (int i = 0; i < dataNum; ++i) {
    for (int j = 0; j < 4; ++j) {
      X[i][j] = attri[i][choose[j]];
    }
    X[i][4] = 1;
    y[i][0] = price[i];
  }
  w = inv(X.T()*X)*X.T()*y;
}

double Predict(double inx[4]) {
  Martix<double> x(5, 1);
  for (int i = 0; i < 4; ++i) x[i][0] = inx[i];
  x[0][4] = 1;
  return (w*x)[0][0];
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
    return r[x] > r[y];
  });
  // 多元线性回归
  LineReg();
  Outputs();
  system("pause");
  return 0;
}