#include <bits/stdc++.h>
using namespace std;
int main() {
  int T, n, g;
  cin >> T;
  while (T--) {
    cin >> n;
    g = 0;
    for (int i = 1, a; i <= n; ++i) {
      cin >> a;
      g = __gcd(g, abs(a));
    }
    cout << (g == 1 ? "Yes" : "No") << endl;
  }
  return 0;
}