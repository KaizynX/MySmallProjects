/*
 * @Author: Kaizyn
 * @Date: 2021-06-02 15:43:09
 * @LastEditTime: 2021-06-02 15:51:58
 */
#include <bits/stdc++.h>

using namespace std;

const int N = 10;
const int INF = 1e9;

int n;
int a[N], dp[N][N];

int main() {
  cin >> n;
  for (int i = 1; i <= n; ++i) cin >> a[i];
  for (int len = 3; len <= n; ++len) {
    for (int l = 1, r; (r = l+len-1) <= n; ++l) {
      dp[l][r] = INF;
      for (int k = l; k < r; ++k) {
        dp[l][r] = min(dp[l][r], dp[l][k]+dp[k+1][r]+a[l]*a[k]*a[r]);
      }
    }
  }
  cout << dp[1][n] << '\n';
  return 0;
}
/*
7
5 10 3 12 5 50 6
*/