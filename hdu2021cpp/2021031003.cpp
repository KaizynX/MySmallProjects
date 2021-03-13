/*
 * @Author: Kaizyn
 * @Date: 2021-03-13 10:33:24
 * @LastEditTime: 2021-03-13 10:37:08
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
// const ll INF = 1e18;
const int N = 1e2+7;

int stk[2][N], sz[2];

signed main() {
#ifdef ONLINE_JUDGE
  ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#endif
  for (int v, x; cin >> v >> x; stk[v-1][++sz[v-1]] = x) {}
  for (int i = 0; i < 2; ++i) {
    while (sz[i]) {
      cout << stk[i][sz[i]] << " \n"[sz[i] == 1];
      --sz[i];
    }
  }
  return 0;
}