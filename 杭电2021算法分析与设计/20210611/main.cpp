/*
 * @Author: Kaizyn
 * @Date: 2021-06-11 13:44:56
 * @LastEditTime: 2021-06-11 13:53:21
 */
#include <bits/stdc++.h>

using namespace std;

const int N = 1e2+7;

int n, m;
int dis[N];
vector<pair<int, int>> e[N];

inline void Dijkstra() {
  priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int>>> q;
  memset(dis, 0x7f, sizeof dis);
  dis[1] = 0;
  q.push(make_pair(0, 1));
  while(q.size()) {
    int u = q.top().second;
    int d = q.top().first;
    q.pop();
    if (dis[u] < d) continue;
    for (auto &p : e[u]) {
      int v = p.first;
      int w = p.second;
      if(d+w >= dis[v]) continue;
      dis[v] = d+w;
      q.push(make_pair(dis[v], v));
    }
  }
}

signed main() {
  cin >> n >> m;
  for (int i = 1, u, v, w; i <= m; ++i) {
    cin >> u >> v >> w;
    e[u].emplace_back(v, w);
    e[v].emplace_back(u, w);
  }
  Dijkstra();
  for (int i = 1; i <= n; ++i) {
    cout << dis[i] << " \n"[i==n];
  }
  return 0;
}
/*
3 3
1 2 1
1 3 10
2 3 2
*/