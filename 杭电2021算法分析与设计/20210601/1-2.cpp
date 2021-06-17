/*
 * @Author: Kaizyn
 * @Date: 2021-06-01 23:10:22
 * @LastEditTime: 2021-06-01 23:16:19
 */
#include <bits/stdc++.h>

using namespace std;

const int N = 10;

int n, m;
int a[N], b[N], dp[N][N];

int main() {
  cin >> n;
  for (int i = 1; i <= n; ++i) cin >> a[i];
  cin >> m;
  for (int i = 1; i <= m; ++i) cin >> b[i];
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
      if (a[i] == b[j]) dp[i][j] = max(dp[i][j], dp[i-1][j-1]+1);
    }
  }
  cout << dp[n][m] << '\n';
  return 0;
}
/*
8
1 0 0 1 0 1 0 1
9
0 1 0 1 1 0 1 1 0
*/