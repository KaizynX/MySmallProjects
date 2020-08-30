/*
 * @Author: Kaizyn
 * @Date: 2020-08-25 11:07:50
 * @LastEditTime: 2020-08-25 14:04:29
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

signed main() {
  freopen("2.in", "w", stdout);
  n = 31;
  m = n*n*4-4*n;
  k = 4;
  // s = my_rand(1, n);
  // t = my_rand(1, n);
  s = n*n-17;
  t = 11;
  for (int i = 1; i <= n*n; ++i) {
    // c[i] = my_rand(1, n);
    c[i] = 555;
  }
  for (int i = 1; i <= n; ++i) {
    c[my_rand(1, n*n)] = my_rand(1, n); 
  }
  cout << n*n << " " << m << " " << k << " " << s << " " << t << endl;
  for (int i = 1; i <= n*n; ++i) {
    cout << c[i] << " \n"[i==n];
  }
  for (int i = 1; i <= n*n; ++i) {
    if (i%n != 1) cout << i << " " << i-1 << endl;
    if (i%n != 0) cout << i << " " << i+1 << endl;
    if (i-n > 0) cout << i << " " << i-n << endl;
    if (i+n <= n*n) cout << i << " " << i+n << endl;
  }
  return 0;
}