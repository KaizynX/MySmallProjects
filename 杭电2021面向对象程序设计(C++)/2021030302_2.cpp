/*
 * @Author: Kaizyn
 * @Date: 2021-03-04 15:04:14
 * @LastEditTime: 2021-03-04 16:51:08
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

list<int> l1, l2, l3;

void print(list<int> l) {
  while (l.size()) {
    cout << l.front();
    l.pop_front();
    if (l.size()) cout << "->";
    else cout << '\n';
  }
}

template <typename T>
void merge(T l1, T l2, T &l3) {
  while (l1.size() && l2.size()) {
    if (l1.front() == l2.front()) {
      l3.push_back(l1.front());
      l3.push_back(l2.front());
      l1.pop_front();
      l2.pop_front();
    } else if (l1.front() < l2.front()) {
      l3.push_back(l1.front());
      l1.pop_front();
    } else {
      l3.push_back(l2.front());
      l2.pop_front();
    }
  }
  while (l1.size()) {
    l3.push_back(l1.front());
    l1.pop_front();
  }
  while (l2.size()) {
    l3.push_back(l2.front());
    l2.pop_front();
  }
}

signed main() {
  for (int i = 1, x; cin >> x, x; ++i) {
    if (i&1) l1.push_back(x);
    else l2.push_back(x);
  }
  print(l1);
  print(l2);
  merge(l1, l2, l3);
  print(l3);
  return 0;
}