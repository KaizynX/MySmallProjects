/*
 * @Author: Kaizyn
 * @Date: 2021-03-13 10:24:44
 * @LastEditTime: 2021-03-13 10:32:31
 */
#include <bits/stdc++.h>

// #define DEBUG

using namespace std;

const double PI = 3.1415926;

class Circle {
  double r;
 public:
  Circle() {}
  Circle(double _r) : r(_r) {}
  double get_price() const {
    return r*r*PI*20+2*PI*r*35;
  }
};

signed main() {
  double r;
  cin >> r;
  Circle cir(r);
  cout << setiosflags(ios::fixed) << setprecision(2) << cir.get_price() << '\n';
  return 0;
}