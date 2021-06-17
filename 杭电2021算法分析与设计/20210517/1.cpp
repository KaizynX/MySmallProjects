/*
 * @Author: Kaizyn
 * @Date: 2021-05-17 21:52:38
 * @LastEditTime: 2021-05-17 22:00:04
 */
#include <bits/stdc++.h>

using namespace std;

int n;
vector<int> pset;

int nearest_point_pair(int l, int r) {
  if (l+1 == r) return l;
  int mid = (l+r)/2;
  auto lhs = nearest_point_pair(l, mid), rhs = nearest_point_pair(mid, r);
  return pset[lhs+1]-pset[lhs] <= pset[rhs+1]-pset[rhs] ? lhs : rhs;
}

signed main() {
  cin >> n;
  pset.resize(n);
  for (int i = 0; i < n; ++i) cin >> pset[i];
  int ans = nearest_point_pair(0, n-1);
  cout << "最近的点对是(" << ans+1 << ',' << ans+2 << ")\n";
  return 0;
}