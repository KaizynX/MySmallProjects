/*
 * @Author: Kaizyn
 * @Date: 2021-03-31 10:16:57
 * @LastEditTime: 2021-03-31 10:49:56
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

class Student {
 public:
  // Student() { sum = num = 0; }
  void set_mark(int x) {
    sum += x;
    ++num;
  }
  int get_sum() {
    return sum;
  }
  int get_ave() {
    return sum/num;
  }
 private:
  static int sum, num;
};

int Student::sum = 0;
int Student::num = 0;

signed main() {
#ifdef ONLINE_JUDGE
  ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
#endif
  Student stu;
  for (int i = 1, x; i <= 5; ++i) {
    cin >> x;
    stu.set_mark(x);
  }
  cout << stu.get_sum() << '\n' << stu.get_ave() << '\n';
  return 0;
}