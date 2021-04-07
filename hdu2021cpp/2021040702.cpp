/*
 * @Author: Kaizyn
 * @Date: 2021-04-07 11:30:39
 * @LastEditTime: 2021-04-07 11:44:39
 */
#include <bits/stdc++.h>

// #define DEBUG

using namespace std;

class Fraction {
 public:
  typedef int T;
  void normalize() {
    if (a == 0) return (void)(b = 1);
    T g = __gcd(a, b);
    a /= g; b /= g;
    if (b < 0) a = -a, b = -b;
  }
  Fraction(const T &_a = 0, const T &_b = 1) : a(_a), b(_b) { this->normalize(); }
  friend bool operator < (const Fraction &f1, const Fraction &f2) { return f1.a*f2.b < f2.a*f1.b; }
  friend bool operator > (const Fraction &f1, const Fraction &f2) { return f1.a*f2.b > f2.a*f1.b; }
  friend bool operator == (const Fraction &f1, const Fraction &f2) { return f1.a*f2.b == f2.a*f1.b; }
  friend bool operator != (const Fraction &f1, const Fraction &f2) { return f1.a*f2.b != f2.a*f1.b; }
  friend bool operator <= (const Fraction &f1, const Fraction &f2) { return f1 < f2 || f1 == f2; }
  friend bool operator >= (const Fraction &f1, const Fraction &f2) { return f1 > f2 || f1 == f2; }
  friend Fraction operator + (const Fraction &f1, const Fraction &f2) { return Fraction(f1.a*f2.b+f2.a*f1.b, f1.b*f2.b); }
  friend Fraction operator - (const Fraction &f1, const Fraction &f2) { return Fraction(f1.a*f2.b-f2.a*f1.b, f1.b*f2.b); }
  friend Fraction operator * (const Fraction &f1, const Fraction &f2) { return Fraction(f1.a*f2.a, f1.b*f2.b); }
  friend Fraction operator / (const Fraction &f1, const Fraction &f2) { return Fraction(f1.a*f2.b, f1.b*f2.a); }
  Fraction& operator += (const Fraction &f) { return *this = *this+f; }
  Fraction& operator -= (const Fraction &f) { return *this = *this-f; }
  Fraction& operator *= (const Fraction &f) { return *this = *this*f; }
  Fraction& operator /= (const Fraction &f) { return *this = *this/f; }
  friend istream& operator >> (istream &is, Fraction &f) {
    is >> f.a >> f.b;
    f.normalize();
    return is;
  }
  friend ostream& operator << (ostream &os, const Fraction &f) {
    if (f.b == 1) return os << f.a;
    return os << f.a << "/" << f.b;
  }
 private:
  T a, b;
};

signed main() {
  Fraction a, b;
  cin >> a >> b;
  cout << a << '\n' << b << '\n'
      << a+b << '\t' << a-b << '\t' << a*b << '\t' << a/b << '\n';
  return 0;
}