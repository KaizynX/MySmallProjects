/*
 * @Author: Kaizyn
 * @Date: 2021-03-04 15:04:14
 * @LastEditTime: 2021-03-04 18:57:44
 */
#include <bits/stdc++.h>

// #define DEBUG

using namespace std;

const double eps = 1e-7;
const double PI = acos(-1);
typedef pair<int, int> pii;
typedef long long ll;
const int MOD = 998244353;
const int INF = 0x3f3f3f3f;
// const ll INF = 1e18;

vector<int> v;

signed main() {
  for (int x; cin >> x, x; v.push_back(x)) {}
  sort(v.begin(), v.end());
  for (int i = 0, j = 0; i < (int)v.size(); ++i) {
    if (v[i]%2 == 1) {
      if (j) cout << "->";
      cout << v[i];
      ++j;
    }
  }
  cout << '\n';
  for (int i = 0, j = 0; i < (int)v.size(); ++i) {
    if (v[i]%2 == 0) {
      if (j) cout << "->";
      cout << v[i];
      ++j;
    }
  }
  cout << '\n';
  for (int i = 0, j = 0; i < (int)v.size(); ++i) {
    if (j) cout << "->";
    cout << v[i];
    ++j;
  }
  cout << '\n';
  return 0;
}