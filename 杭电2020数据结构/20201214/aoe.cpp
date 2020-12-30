/*
 * @Author: Kaizyn
 * @Date: 2020-12-16 20:48:26
 * @LastEditTime: 2020-12-16 21:04:40
 */
#include <bits/stdc++.h>

// #define DEBUG

using namespace std;

const double eps = 1e-7;
const double PI = acos(-1);
typedef pair<int, int> pii;
const int MOD = 998244353;
const int INF = 0x3f3f3f3f;
const int N = 20;

int n;
int a[N], t[N], res[N];
vector<pii> e[N];

inline void solve() {
  cin >> n;
  int u, v, w;
  while (cin >> u >> v >> w) {
    e[v].emplace_back(u, w);
  }
  iota(a+1, a+n+1, 1);
  do {
    memset(t, -1, sizeof t);
    t[1] = 0;
    int flag = 1, ct = 0;
    for (int i = 2, u; i <= n; ++i) {
      u = a[i];
      for (auto &p : e[u]) {
        int v = p.first, w = p.second;
        if (t[v] == -1) continue;
        else t[u] = ct+w;
      }
      if (t[u] == -1) flag = 0;
      else ct = t[u];
    }
    if (flag) for (int i = 1; i <= n; ++i) res[i] = max(t[i], res[i]);
  } while (next_permutation(a+2, a+n+1));
  for (int i = 1; i <= n; ++i) cout << res[i] << " \n"[i==n];
}

signed main() {
#ifndef DEBUG
  ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#endif
  int T = 1;
  // cin >> T;
  for (int t = 1; t <= T; ++t) {
    solve();
  }
  return 0;
}
/*
10
1 2 8
1 3 6
1 5 7
2 4 3
3 4 10
3 7 9
5 7 9
5 8 13
7 8 2
8 9 6
7 9 8
4 9 19
4 6 4
6 10 14
9 10 10
*/