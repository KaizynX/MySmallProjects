/*
 * @Author: Kaizyn
 * @Date: 2021-05-06 19:33:47
 * @LastEditTime: 2021-05-07 13:03:08
 */
#include <bits/stdc++.h>

using namespace std;

// const int N = 1e2+7;
const int M = 13;

template <typename U>
class Martix {
 public:
  Martix() {}
  Martix(const int &_n, const int &_m = 1) : n(_n), m(_m) {
    a = vector<vector<U>>(n, vector<U>(m, 0));
  }
  bool empty() const { return n == 0 || m == 0; }
  auto size() const { return {n, m}; }
  vector<U>& operator [](const int &i) { return a[i]; }
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
        res[k][j] *= res[k][k];
      for (int i = 0; i < n; ++i) if (i != k)
        for (int j = 0; j < n; ++j) if (j != k)
          res[i][j] -= res[i][k]*res[k][j];
      for (int i = 0; i < n; ++i) if (i != k)
        res[i][k] *= -res[k][k];
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
        os << mx.a[i][j] << " \n"[j==mx.m-1];
    return os;
  }
 private:
  int n, m;
  vector<vector<U>> a;
};

int dataNum;               //样本数目
// double attri[M][N], price[N], min_in[M], max_in[M], min_out, max_out, r[M];
vector<vector<double>> attri(M);
vector<double> price, min_in(M), max_in(M), r(M);
double min_out, max_out;
Martix<double> W; // (5, 1)
Martix<double> X, Y, FY; // X(N, 5) Y(N, 1) FY(N, 1)
vector<int> choose(M);
vector<string> Attribute_name(M+1);

//数据读入
bool Inputs() {
  string fname = "housing.txt";                         //存储文件名
  cout << "请输入存放数据的文件名：";
  cin >> fname;
  ifstream fp(fname);
  if (!fp.is_open()) return cout << "不能打开输入的文件\n", false;
  for (int i = 0; i < M+1; ++i) fp >> Attribute_name[i];
  for (int i = 0; !fp.eof(); ++i, ++dataNum) {
    double data;
    for (int j = 0; j < M; ++j) {
      fp >> data;
      attri[j].emplace_back(data);
    }
    fp >> data;
    price.emplace_back(data);
  }
  fp.close();
  return true;
}

//使用最大最小归一化数据
void Normalization(vector<double> &x, double &min_val, double &max_val) {
  min_val = max_val = x[0];
  for (auto &v : x) {
    min_val = min(min_val, v);
    max_val = max(max_val, v);
  }
  for (auto &v : x) {
    v = (v-min_val)/(max_val-min_val);
  }
}

// 计算相关系数
double Correlation_coefficient(vector<double> &x, vector<double> &y) {
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
  X = Martix<double>(dataNum, 5);
  Y = Martix<double>(dataNum, 1);
  for (int i = 0; i < dataNum; ++i) {
    for (int j = 0; j < 4; ++j) {
      X[i][j] = attri[choose[j]][i];
    }
    X[i][4] = 1;
    Y[i][0] = price[i];
  }
  W = inv(X.T()*X)*X.T()*Y;
}

double MSE() {
  double mse = 0;
  FY = X*W;
  for (int i = 0; i < dataNum; ++i) {
    mse += (FY[i][0]-Y[i][0])*(FY[i][0]-Y[i][0]);
  }
  return mse/dataNum;
}

//输出
bool Outputs() {
  Martix<double> x(5, 1);
  for (int i = 0, j; i < 4; ++i) {
    j = choose[i];
    cout << "请输入房屋的" << Attribute_name[j] << "属性值:";
    if (!(cin >> x[i][0])) return false;
    // 归一化
    x[i][0] = (x[i][0]-min_in[j])/(max_in[j]-min_in[j]);
  }
  x[4][0] = 1;
  double y = (x.T()*W)[0][0];
  y = y*(max_out-min_out)+min_out;
  cout << "预计房价为：" << y << "元\n";
  return true;
}

int main() {
  if (!Inputs()) return 0;    //判断数据样本读入是否成功
  // 归一化
  for (int i = 0; i < M; ++i) Normalization(attri[i], min_in[i], max_in[i]);
  Normalization(price, min_out, max_out);
  // 计算相关系数
  for (int i = 0; i < M; ++i) {
    r[i] = Correlation_coefficient(attri[i], price);
    cout << Attribute_name[i] << "属性的相关系数为:" << r[i] << '\n';
  }
  // 挑选四个最相关的维度
  iota(choose.begin(), choose.end(), 0);
  sort(choose.begin(), choose.end(), [&](int x, int y) {
    return abs(r[x]) > abs(r[y]);
  });
  cout << "挑选的四个维度为:";
  for (int i = 0; i < 4; ++i) cout << Attribute_name[choose[i]] << ",\n"[i==3];
  // 多元线性回归
  LineReg();
  // 模型评估
  cout << "MSE=" << MSE() << '\n';
  // 房价预测
  while (Outputs()) {}
  system("pause");
  return 0;
}