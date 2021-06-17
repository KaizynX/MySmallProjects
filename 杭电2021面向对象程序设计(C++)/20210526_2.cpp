/*
 * @Author: Kaizyn
 * @Date: 2021-05-26 10:07:25
 * @LastEditTime: 2021-05-26 11:11:41
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
// const int N = ;

template <class T>
inline void work(vector<T> &v) {
  string str;
  T x;
  int id;
  while (cin >> str && str != "quit") {
    if (str == "push") {
      cin >> x;
      v.push_back(x);
    } else if (str == "put") {
      cin >> id >> x;
      if (id < 0 || id >= (int)v.size()) {
        cout << "invalid index:" << id << ' ';
      } else {
        v[id] = x;
      }
    } else if (str == "fetch") {
      cin >> id;
      if (id < 0 || id >= (int)v.size()) {
        cout << "invalid index:" << id << ' ';
      } else {
        cout << v[id] << ' ';
      }
    }
  }
  cout << '\n';
}

signed main() {
  string str;
  int x;
  while (cin >> str >> x) {
    if (str == "int") {
      vector<int> v(x);
      work(v);
    } else if (str == "string") {
      vector<string> v(x);
      work(v);
    }
  }
  return 0;
}