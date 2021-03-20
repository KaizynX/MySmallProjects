/*
 * @Author: Kaizyn
 * @Date: 2021-03-17 10:06:34
 * @LastEditTime: 2021-03-17 10:33:29
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

struct Set{
  vector<int> v;
  Set() { v = vector<int>(); }
  void insert(int x) {
    for (auto it = v.begin(); it != v.end(); ++it) {
      if (*it == x) return;
      if (*it > x) return v.insert(it, x), void();
    }
    v.insert(v.end(), x);
  }
  friend Set Union(Set a, Set b) {
    Set c = a;
    for (int x : b.v) c.insert(x);
    return c;
  }
  friend Set Intersection(Set a, Set b) {
    Set c;
    for (int x : a.v) {
      if (binary_search(b.v.begin(), b.v.end(), x)) c.insert(x);
    }
    return c;
  }
  friend Set Difference(Set a, Set b) {
    Set c;
    for (int x : a.v) {
      if (!binary_search(b.v.begin(), b.v.end(), x)) c.insert(x);
    }
    return c;
  }
  friend ostream& operator <<(ostream &os, Set s) {
    os << '{';
    for (int i = 0; i < (int)s.v.size(); ++i) {
      os << s.v[i];
      if (i+1 != (int)s.v.size()) os << ',';
    }
    return os << '}';
  }
};

signed main() {
#ifdef ONLINE_JUDGE
  ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
#endif
  int m, n;
  Set a, b;
  cin >> m >> n;
  for (int i = 1, x; i <= m; ++i) {
    cin >> x;
    a.insert(x);
  }
  for (int i = 1, x; i <= n; ++i) {
    cin >> x;
    b.insert(x);
  }
  cout << a << '\n';
  cout << b << '\n';
  cout << Union(a, b) << '\n';
  cout << Intersection(a, b) << '\n';
  cout << Difference(a, b) << '\n';
  return 0;
}