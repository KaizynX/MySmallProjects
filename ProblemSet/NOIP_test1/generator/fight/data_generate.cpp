/*
 * @Author: Kaizyn
 * @Date: 2020-08-25 11:07:50
 * @LastEditTime: 2020-08-25 18:04:58
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

int n, L, R;
int a[N];

signed main() {
  freopen("1.in", "w", stdout);
  n = 1e3;
  L = 7;
  R = 666;
  for (int i = 1; i <= n; ++i) {
    a[i] = my_rand(-1e9, 1e9);
  }
  cout << n << " " << L << " " << R << endl;
  for (int i = 1; i <= n; ++i) {
    cout << a[i] << " \n"[i==n];
  }
  return 0;
}