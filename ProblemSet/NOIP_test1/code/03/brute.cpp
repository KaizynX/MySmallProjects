/*
 * @Author: Kaizyn
 * @Date: 2020-08-25 14:49:52
 * @LastEditTime: 2020-08-25 18:29:40
 */
#include <bits/stdc++.h>

using namespace std;

const int N = 1e5+7;
const int INF = 0x3f3f3f3f;

int n, m, L, R;
int a[N], dp[N];
long long presum[N];

signed main() {
  cin >> n >> L >> R;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    presum[i] = presum[i-1]+a[i];
  }
  for (int i = 1; i <= n; ++i) {
    dp[i] = -INF;
    for (int j = max(0, i-R); j <= i-L; ++j) {
      long long dis = presum[i]-presum[j];
      if (dis > 0) dp[i] = max(dp[i], dp[j]+1);
      if (dis == 0) dp[i] = max(dp[i], dp[j]);
      if (dis < 0) dp[i] = max(dp[i], dp[j]-1);
    }
  }
  cout << dp[n] << endl;
  for (int i = 1; i <= n; ++i) {
    dp[i] = -INF;
    for (int j = max(0, i-R); j <= i-L; ++j) {
      long long dis = presum[i]-presum[j];
      if (dis > 0) dp[i] = max(dp[i], dp[j]-1);
      if (dis == 0) dp[i] = max(dp[i], dp[j]);
      if (dis < 0) dp[i] = max(dp[i], dp[j]+1);
    }
  }
  cout << dp[n] << endl;
  return 0;
}