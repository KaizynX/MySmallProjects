/*
 * @Author: Kaizyn
 * @Date: 2021-03-31 11:27:45
 * @LastEditTime: 2021-03-31 11:30:14
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

class Line;
class Point;

class Point {
 public:
  Point() {}
  Point(int _x, int _y) : x(_x), y(_y) {}
  // double dist(Point p, Line l);
  friend double dist(Point p, Line l);
 private:
  int x, y;
};

class Line {
 public:
  // friend double Point::dist(Point p, Line l);
  friend double dist(Point p, Line l);
  Line() {}
  Line(int _a, int _b, int _c) : a(_a), b(_b), c(_c) {}
 private:
  int a, b, c;
};

/*
double Point::dist(Point p, Line l) {
  return abs((l.a*p.x+l.b*p.y+l.c)/sqrt(l.a*l.a+l.b*l.b));
}
*/
double dist(Point p, Line l) {
  return abs((l.a*p.x+l.b*p.y+l.c)/sqrt(l.a*l.a+l.b*l.b));
}

signed main() {
#ifdef ONLINE_JUDGE
  ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
#endif
  int x, y, a, b, c;
  scanf("%d%d%d%d%d", &x, &y, &a, &b, &c);
  // scanf("%lf%lf%lf%lf%lf", &x, &y, &a, &b, &c);
  Point p(x, y);
  Line l(a, b, c);
  double d = dist(p, l);
  if (d == 0) puts("The distance is: 0");
  else printf("The distance is: %.2f\n", dist(p, l));
  return 0;
}