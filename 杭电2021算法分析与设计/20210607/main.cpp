/*
 * @Author: Kaizyn
 * @Date: 2021-06-07 20:49:50
 * @LastEditTime: 2021-06-07 20:55:15
 */
#include <bits/stdc++.h>
using namespace std;
signed main() {
  int k, ans = 0;
  cin >> k;
  vector<int> a(k);
  for (int i = 0; i < k; ++i) cin >> a[i];
  while (a.size() >= 2u) {
    auto pm = min_element(a.begin(), a.end());
    int m = *pm;
    a.erase(pm);
    auto pn = min_element(a.begin(), a.end());
    int n = *pn;
    a.erase(pn);
    ans += n+m-1;
    a.push_back(n+m);
  }
  cout << "所需的总比较次数:" << ans << endl;
  return 0;
}