/*
 * @Author: Kaizyn
 * @Date: 2021-05-10 08:49:16
 * @LastEditTime: 2021-05-10 09:06:17
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
const int N = 2e5+7;

int n;
vector<int> a;

void sort(int l, int r) {
  if (r-l <= 1) return;
  int block = sqrt(r-l)+.5, num = (r-l+block-1)/block;
  vector<int> head(num), tail(num), tmp(r-l);
  for (int i = 0; i < num; ++i) {
    head[i] = l+i*block;
    tail[i] = min(head[i]+block, r);
    sort(head[i], tail[i]);
  }
  for (int i = 0, k; i < r-l; ++i) {
    k = -1;
    for (int j = 0; j < num; ++j) {
      if (head[j] >= tail[j]) continue;
      if (k == -1 || a[head[j]] < a[head[k]]) k = j;
    }
    tmp[i] = a[head[k]++];
  }
  for (int i = 0; i < r-l; ++i) a[l+i] = tmp[i];
  // memcpy(a.begin()+l, tmp.begin(), sizeof(int)*(r-l));
}

signed main() {
#ifdef ONLINE_JUDGE
  ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
#endif
  cin >> n;
  a.resize(n);
  for (int i = 0; i < n; ++i) cin >> a[i];
  sort(0, n);
  for (int i = 0; i < n; ++i) cout << a[i] << " \n"[i==n-1];
  return 0;
}