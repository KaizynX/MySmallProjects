/*
 * @Author: Kaizyn
 * @Date: 2021-05-19 10:25:13
 * @LastEditTime: 2021-05-19 10:28:06
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

template <typename T>
class Shit {
  T a, b;
 public:
  void fuck() {
    cin >> a >> b;
    cout << max(a, b) << ' '
        << min(a, b) << ' '
        << a+b << ' '
        << a-b << ' '
        << a*b << ' '
        << a/b << '\n';
  }
};

signed main() {
#ifdef ONLINE_JUDGE
  ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
#endif
  Shit<int> s1;
  Shit<double> s2;
  s1.fuck();
  s2.fuck();
  return 0;
}