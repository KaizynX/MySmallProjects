/*
 * @Author: Kaizyn
 * @Date: 2021-04-04 11:03:34
 * @LastEditTime: 2021-04-04 11:17:04
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
const int dir[] = {0, -1, 0, 1, 0};
// const ll INF = 1e18;
// const int N = ;

int n, m;
vector<vector<int>> a, vis;

void solve1(int x, int y) {
  vis[x][y] = 1;
  for (int d = 0, nx, ny; d < 4; ++d) {
    nx = x+dir[d];
    ny = y+dir[d+1];
    if (nx < 0 || ny < 0 || nx >= n || ny >= m
        || vis[nx][ny] || a[nx][ny] != a[x][y]) continue;
    solve1(nx, ny);
  }
}

void solve2(int sx, int sy) {
  static queue<pii> q;
  q.push({sx, sy});
  vis[sx][sy] = 1;
  while (q.size()) {
    int x = q.front().first;
    int y = q.front().second;
    q.pop();
    for (int d = 0, nx, ny; d < 4; ++d) {
      nx = x+dir[d];
      ny = y+dir[d+1];
      if (nx < 0 || ny < 0 || nx >= n || ny >= m
          || vis[nx][ny] || a[nx][ny] != a[x][y]) continue;
      q.push({nx, ny});
      vis[nx][ny] = 1;
    }
  }
}

signed main() {
#ifdef ONLINE_JUDGE
  ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
#endif
  cin >> n >> m;
  a = vector<vector<int>>(n, vector<int>(m));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> a[i][j];
    }
  }
  int res = 0;
  vis = vector<vector<int>>(n, vector<int>(m, 0));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) if (!vis[i][j]) {
      solve1(i, j);
      ++res;
    }
  }
  cout << "递归:" << res << '\n';

  res = 0;
  vis = vector<vector<int>>(n, vector<int>(m, 0));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) if (!vis[i][j]) {
      solve2(i, j);
      ++res;
    }
  }
  cout << "非递归:" << res << '\n';
  return 0;
}
/*
7 6
4 4 4 4 4 4
4 1 3 2 1 4
4 1 2 2 1 4
4 1 1 1 1 4
4 1 2 2 3 4
4 3 3 3 3 4
4 4 4 4 4 4
*/