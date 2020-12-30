/*
 * @Author: Kaizyn
 * @Date: 2020-12-16 21:08:16
 * @LastEditTime: 2020-12-16 21:52:13
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

void print() {
  printf("d: ");
  for (int i = 1; i <= n; ++i) {
    if (d[i] == INF) printf("inf");
    else printf("%3d", d[i]);
    putchar(" \n"[i==n]);
  }
}

void Prim() {
  printf("i =");
  for (int i = 1; i <= n; ++i) printf("%3d%c", i, " \n"[i==n]);
  memset(d, 0x3f, sizeof d);
  d[1] = 0;
  for (int i = 1; i <= n; ++i) {
    print();
    int u = 0;
    for (int j = 1; j <= n; ++j) {
      if (!vis[j] && d[j] < d[u]) u = j;
    }
    vis[u] = 1;
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
1 2 2
2 4 2
1 3 3 
3 4 1
4 5 2
4 6 4
5 6 1
5 7 2
6 7 2
6 8 1
7 8 1
*/