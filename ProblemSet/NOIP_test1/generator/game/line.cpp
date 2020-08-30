/*
 * @Author: Kaizyn
 * @Date: 2020-08-25 11:07:50
 * @LastEditTime: 2020-08-25 14:28:31
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
  n = 1e5;
  m = n;
  k = 5555;
  // s = my_rand(1, n);
  // t = my_rand(1, n);
  s = n;
  t = 1;
  for (int i = 1; i <= n; ++i) {
    // c[i] = my_rand(1, n);
    c[i] = 23333;
  }
  for (int i = 1; i <= 66; ++i) c[my_rand(1, n)] = my_rand(1, n); 
  cout << n << " " << m << " " << k << " " << s << " " << t << endl;
  for (int i = 1; i <= n; ++i) {
    cout << c[i] << " \n"[i==n];
  }
  cout << 1 << " " << n << endl;
  for (int i = 2; i <= n; ++i) {
    cout << i << " " << i-1 << endl;
  }
  return 0;
}