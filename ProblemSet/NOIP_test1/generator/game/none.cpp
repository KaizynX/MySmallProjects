/*
 * @Author: Kaizyn
 * @Date: 2020-08-25 11:07:50
 * @LastEditTime: 2020-08-25 14:41:49
 */
#include <bits/stdc++.h>

// #define DEBUG

using namespace std;

const double eps = 1e-7;
const double PI = acos(-1);
typedef pair<int, int> pii;
const int MOD = 998244353;
const int INF = 0x3f3f3f3f;
const int N = 1e5+7;
mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());

int my_rand(int l, int r) {
  int d = r-l+1;
  return rnd()%d+l;
}

template <class T>
void my_shuffle(T s, T t) {
  int n = t-s;
  for (int i = 1; i < n; ++i) {
    swap(*(s+i), *(s+rnd()%i));
  }
}

int n, m, k, s, t;
int c[N];
map<pii, int> mp;

void my_get(int &u, int &v, int l, int r) {
  u = my_rand(l, r);
  do {
    v = my_rand(l, r);
  } while (u == v);
}

signed main() {
  freopen("2.in", "w", stdout);
  n = 1e5;
  m = 4e5;
  k = 56789;
  // s = my_rand(1, n);
  // t = my_rand(1, n);
  s = 99999;
  t = 10101;
  for (int i = 1; i <= n; ++i) {
    c[i] = my_rand(1, n);
  }
  cout << n << " " << m << " " << k << " " << s << " " << t << endl;
  for (int i = 1; i <= n; ++i) {
    cout << c[i] << " \n"[i==n];
  }
  for (int i = 1, j; i <= n; ++i) {
    do {
      j = i <= n/2 ? my_rand(1, n/2) : my_rand(n/2+1, n);
    } while (i == j);
    mp[{i, j}] = 1;
    cout << i << " " << j << endl;
  }
  for (int i = n+1, u, v; i <= m; ++i) {
    if (rnd()%2) {
      do {
        my_get(u, v, 1, n/2);
      } while (mp.count({u, v}));
    } else {
      do {
        my_get(u, v, n/2+1, n);
      } while (mp.count({u, v}));
    }
    cout << u << " " << v << endl;
    mp[{u, v}] = 1;
  }
  return 0;
}