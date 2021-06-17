/*
 * @Author: Kaizyn
 * @Date: 2021-06-01 09:29:02
 * @LastEditTime: 2021-06-01 09:31:49
 */
#include <bits/stdc++.h>

using namespace std;

signed main() {
  int n;
  cin >> n;
  vector<vector<int>> a(n), dp(n);
  for (int i = 0; i < n; ++i) {
    a[i].resize(i+1);
    dp[i].resize(i+1);
    for (int j = 0; j <= i; ++j) {
      cin >> a[i][j];
      dp[i][j] = a[i][j];
    }
  }
  for (int i = n-2; i >= 0; --i) {
    for (int j = 0; j <= i; ++j) {
      dp[i][j] = max(dp[i+1][j], dp[i+1][j+1])+a[i][j];
    }
  }
  cout << dp[0][0] << '\n';
  return 0;
}