/*
 * @Author: Kaizyn
 * @Date: 2021-05-24 11:07:48
 * @LastEditTime: 2021-05-24 11:28:17
 */
#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;

int k;
string A, B;
vector<vector<int>> dp;

signed main() {
#ifdef ONLINE_JUDGE
  ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
#endif
  cin >> A >> B >> k;
  int la = A.size(), lb = B.size();
  assert(lb >= la);
  dp = vector<vector<int>>(la+1, vector<int>(lb+1, INF));
  dp[0][0] = 0;
  for (int i = 0; i <= la; ++i) {
    for (int j = 0; j <= lb; ++j) {
      if (i < la && j < lb) dp[i+1][j+1] = min(dp[i+1][j+1], dp[i][j]+abs(A[i]-B[j]));
      if (i < la) dp[i+1][j] = min(dp[i+1][j], dp[i][j]+k);
      if (j < lb) dp[i][j+1] = min(dp[i][j+1], dp[i][j]+k);
    }
  }
  cout << dp[la][lb] << '\n';
  return 0;
}