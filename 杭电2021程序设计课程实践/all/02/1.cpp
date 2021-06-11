/*
 * @Author: Kaizyn
 * @Date: 2021-04-04 10:53:06
 * @LastEditTime: 2021-04-04 11:02:55
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

pii solve1(vector<int> &a, int s) {
  pii res = {a[s], a[s]};
  if (s+1 < (int)a.size()) {
    pii rhs = solve1(a, s+1);
    res.first = min(res.first, rhs.first);
    res.second = max(res.second, rhs.second);
  }
  return res;
}

pii solve2(vector<int> &a) {
  pii res = {a[0], a[0]};
  for (int i = 1; i < (int)a.size(); ++i) {
    res.first = min(res.first, a[i]);
    res.second = max(res.second, a[i]);
  }
  return res;
}

signed main() {
#ifdef ONLINE_JUDGE
  ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
#endif
  int n;
  cout << "输入n:";
  cin >> n;
  vector<int> a(n);
  cout<< "输入n个整数:";
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  cout << "递归:";
  pii res1 = solve1(a, 0);
  cout << "最小值" << res1.first << "最大值" << res1.second << '\n';
  cout << "非递归:";
  pii res2 = solve2(a);
  cout << "最小值" << res2.first << "最大值" << res2.second << '\n';
  return 0;
}
/*
5
2 3 1 5 4
*/