/*
 * @Author: Kaizyn
 * @Date: 2021-06-01 13:02:05
 * @LastEditTime: 2021-06-01 13:05:30
 */
#include <bits/stdc++.h>

using namespace std;

signed main() {
  int n, W;
  cin >> n >> W;
  vector<int> dp(W+1, 0);
  for (int i = 1, v, w; i <= n; ++i) {
    cin >> v >> w;
    for (int j = W; j >= w; --j) {
      dp[j] = max(dp[j], dp[j-w]+v);
    }
  }
  cout << dp[W] << '\n';
  return 0;
}