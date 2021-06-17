/*
 * @Author: Kaizyn
 * @Date: 2021-03-31 11:07:59
 * @LastEditTime: 2021-03-31 11:19:27
 */
#include <bits/stdc++.h>

// #define DEBUG

using namespace std;

const double eps = 1e-7;
const double PI = acos(-1);
typedef pair<int, int> pii;
typedef long long ll;
const int MOD = 998244353; // 1e9+7;
const int INF = 0x3f3f3f3f;
// const ll INF = 1e18;
// const int N = ;

/*
class Complex {
 public:
  Complex() {}
  Complex(double r, double i) : real(r), image(i) {}
  void reverse() {
    real = -real;
    image = -image;
  }
  void print() {
    printf("(%.f, %.f)", real, image);
  }
 private:
  double real, image;
};
*/
class Complex {
 public:
  typedef double T;
  Complex (const double &_real = 0, const double &_imag = 0) : real(_real), imag(_imag) {}
  Complex operator - () { return Complex(-real, -imag); }
  friend Complex operator + (Complex c1, Complex c2) { return Complex(c1.real+c2.real, c1.imag+c2.imag); }
  friend Complex operator - (Complex c1, Complex c2) { return Complex(c1.real-c2.real, c1.imag-c2.imag); }
  friend Complex operator * (Complex c1, Complex c2) { return Complex(c1.real*c2.real-c1.imag*c2.imag, c1.real*c2.imag+c1.imag*c2.real); }
  Complex& operator += (Complex c) { return *this = *this+c; }
  Complex& operator -= (Complex c) { return *this = *this-c; }
  Complex& operator *= (Complex c) { return *this = *this*c; }
  friend istream& operator >> (istream &is, Complex &c) { return is >> c.real >> c.imag; }
  friend ostream& operator << (ostream &os, Complex &c) { return os << '(' << c.real << ", " << c.imag << ")";}
  Complex conjugate() { return Complex(real, -imag); }
  friend Complex conjugate(Complex c) { return Complex(c.real, -c.imag); }
 private:
  T real, imag;
};

signed main() {
#ifdef ONLINE_JUDGE
  ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
#endif
  Complex c1, c2, c3;
  cin >> c1 >> c2;
  c3 = c1+c2;
  cout << c3 << '\n';
  c3 = c1-c2;
  cout << c3 << '\n';
  cout << c2 << '\n';
  return 0;
}