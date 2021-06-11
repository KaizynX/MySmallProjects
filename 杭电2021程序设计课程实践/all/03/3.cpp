/*
 * @Author: Kaizyn
 * @Date: 2021-04-08 14:19:16
 * @LastEditTime: 2021-04-08 14:20:55
 */
#include <bits/stdc++.h>

using namespace std;

signed main() {
  int n;
  cin >> n;
  vector<int> a(n);
  iota(a.begin(), a.end(), 1);
  do {
    for (auto &i : a) cout << i << ' ';
    cout << endl;
  } while (next_permutation(a.begin(), a.end()));
  return 0;
}