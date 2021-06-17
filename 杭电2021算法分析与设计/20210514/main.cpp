/*
 * @Author: Kaizyn
 * @Date: 2021-05-17 21:43:58
 * @LastEditTime: 2021-05-17 21:47:25
 */
#include <bits/stdc++.h>

using namespace std;

int n;
vector<int> a;

int min_element(int l, int r) {
  if (l+1 == r) return a[l];
  int mid = (l+r)/2;
  return min(min_element(l, mid), min_element(mid, r));
}

int max_element(int l, int r) {
  if (l+1 == r) return a[l];
  int mid = (l+r)/2;
  return max(max_element(l, mid), max_element(mid, r));
}

signed main() {
  cin >> n;
  a.resize(n);
  for (int i = 0; i < n; ++i) cin >> a[i];
  cout << min_element(0, n) << '\n';
  cout << max_element(0, n) << '\n';
  return 0;
}