/*
 * @Author: Kaizyn
 * @Date: 2020-08-25 11:07:50
 * @LastEditTime: 2020-08-25 16:56:40
 */
#include <bits/stdc++.h>

// #define DEBUG

using namespace std;

const double eps = 1e-7;
const double PI = acos(-1);
typedef pair<int, int> pii;
const int MOD = 998244353;
const int INF = 0x3f3f3f3f;
mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());

int my_rand(int l, int r) {
  int d = r-l+1;
  return rnd()%d+l;
}

int prime[9] = {2,3,5,7,11,13,17,19,23};

void yes(int n) {
  cout << n << endl;
  for (int i = 1, b; i <= n; ++i) {
    do {
      b = my_rand(0, 1<<9);
    } while (__builtin_popcount(b) < 5);
    int k = 1;
    for (int j = 0; j < 9; ++j) {
      if ((b>>j)&1) k *= prime[j];
    }
    if (rnd()%2) k = -k;
    cout << k << " \n"[i==n];
  }
}

void no(int n, int l, int r) {
  cout << n << endl;
  int p = my_rand(2, 23);
  for (int i = 1, k; i <= n; ++i) {
    k = my_rand(l/p, r/p)*p;
    cout << k << " \n"[i==n];
  }
}

void rand(int n, int l, int r) {
  cout << n << endl;
  for (int i = 1; i <= n; ++i) {
    cout << my_rand(l, r) << " \n"[i==n];
  }
}

signed main() {
  freopen("10.in", "w", stdout);
  int n = 1e5, L = -1e9, R = 1e9;
  cout << 5 << endl;
  rand(my_rand(n/10*9, n), L, R);
  rand(my_rand(n/10*9, n), L, R);
  no(my_rand(n/10*9, n), L, R);
  no(my_rand(n/10*9, n), L, R);
  yes(n);
  return 0;
}