/*
 * @Author: Kaizyn
 * @Date: 2020-08-25 12:49:23
 * @LastEditTime: 2020-08-25 12:58:22
 */
#include <bits/stdc++.h>

using namespace std;

const int N = 1e5+7;
const long long INF = 1e18;

int n, m, k, s, t;
int c[N];
long long dis[N];
vector<int> e[N];
priority_queue<pair<long long, int>> q;

signed main() {
  freopen("2.in", "r", stdin);
  cin >> n >> m >> k >> s >> t;
  for (int i = 1; i <= n; ++i) cin >> c[i];
  for (int i = 1, u, v; i <= m; ++i) {
    cin >> u >> v;
    e[u].emplace_back(v);
  }
  memset(dis, 0x3f, sizeof dis);
  q.push({-1, s});
  dis[s] = 1; 
  while (q.size()) {
    int u = q.top().second;
    long long ud = -q.top().first;
    q.pop();
    if (ud > dis[u]) continue;
    for (int &v : e[u]) {
      long long vd = ud+1;
      if (vd < dis[v]) {
        dis[v] = vd;
        q.push({-vd, v});
      }
    }
  }
  cout << (dis[t] >= INF ? -1 : dis[t]) << endl;
  return 0;
}
