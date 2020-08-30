/*
 * @Author: Kaizyn
 * @Date: 2020-08-25 11:07:50
 * @LastEditTime: 2020-08-25 13:05:04
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
int c[N], fa[N], id[N];

signed main() {
  freopen("2.in", "w", stdout);
  n = 1e5;
  m = n;
  for (int i = 1; i <= n; ++i) {
    c[i] = my_rand(1, n);
    id[i] = i;
    if (i == 1) continue;
    fa[i] = my_rand(1, i-1);
    if (my_rand(1, 100) < 96) c[i] = c[fa[i]];
  }
  fa[1] = my_rand(2, n);
  my_shuffle(id+1, id+n+1);
  s = my_rand(2, n);
  t = 1;
  k = 7;
  cout << n << " " << m << " " << k << " " << id[s] << " " << id[t] << endl;
  for (int i = 1; i <= n; ++i) {
    cout << c[i] << " \n"[i==n];
  }
  for (int i = 1; i <= n; ++i) {
    cout << id[i] << " " << id[fa[i]] << endl;
  }
  return 0;
}