/*
 * @Author: Kaizyn
 * @Date: 2021-03-13 10:41:53
 * @LastEditTime: 2021-03-13 10:44:59
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

queue<int> q[2];

signed main() {
#ifdef ONLINE_JUDGE
  ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#endif
  int n;
  cin >> n;
  for (int _ = n, id, x; _; --_) {
    char op;
    cin >> op >> id;
    --id;
    if (op == 'D') { // 出队
      cout << q[id].front() << ' ';
      q[id].pop();
    } else if (op == 'E') { // 入队
      cin >> x;
      q[id].push(x);
    } else {
      while (q[id].size()) cout << q[id].front() << ' ', q[id].pop();
    }
  }
  return 0;
}