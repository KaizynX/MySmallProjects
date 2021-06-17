/*
 * @Author: Kaizyn
 * @Date: 2021-06-01 13:06:45
 * @LastEditTime: 2021-06-01 13:08:19
 */
#include <bits/stdc++.h>

using namespace std;

signed main() {
  int n, lis = 0;
  cin >> n;
  vector<int> a(n), dp(n, 1);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
    for (int j = 0; j < i; ++j) {
      if (a[i] > a[j]) dp[i] = max(dp[i], dp[j]+1);
    }
    lis = max(lis, dp[i]);
  }
  cout << lis << '\n';
  return 0;
}