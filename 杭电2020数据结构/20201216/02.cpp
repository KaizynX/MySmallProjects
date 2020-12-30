/*
 * @Author: Kaizyn
 * @Date: 2020-12-16 21:08:16
 * @LastEditTime: 2020-12-16 21:54:17
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
int d[N], vis[N];
vector<pii> e[N];

void print(int u) {
  for (auto &p : e[u]) {
    int v = p.first, w = p.second;
    if (vis[v]) printf("(%d,%d)%d\n", u, v, w);
  }
}

void Prim() {
  puts("依次得到的边为:");
  memset(d, 0x3f, sizeof d);
  d[0] = 0;
  for (int i = 1; i < n; ++i) {
    int u = n;
    for (int j = 0; j < n; ++j) {
      if (!vis[j] && d[j] < d[u]) u = j;
    }
    vis[u] = 1;
    print(u);
    for (auto &p : e[u]) {
      int v = p.first, w = p.second;
      d[v] = min(d[v], d[u]+w);
    }
  }
}

inline void solve() {
  cin >> n;
  for (int u, v, w; cin >> u >> v >> w; ) {
    e[u].emplace_back(v, w);
    e[v].emplace_back(u, w);
  }
  Prim();
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
8
0 1 8
0 2 5
0 3 2
1 5 6
2 3 25
2 4 13
3 5 9
3 6 10
4 6 4
5 7 20
*/