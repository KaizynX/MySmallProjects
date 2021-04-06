/*
 * @Author: Kaizyn
 * @Date: 2021-04-04 11:19:51
 * @LastEditTime: 2021-04-04 11:51:19
 */
// 汉诺塔非递归
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

/*
void hanio(int n, int t1 = 1, int t2 = 2, int t3 = 3) {
  if (n < 1) return;
  hanio(n-1, t1, t3, t2);
  cout << "from " << t1 << " to " << t3 << '\n';
  hanio(n-1, t2, t1, t3);
}
*/

void hanio(int sz) {
  stack<int> sn, st1, st2, st3, ss;
  int n, t1, t2, t3, state;
  function<void()> push = [&]() {
    sn.push(n);
    st1.push(t1);
    st2.push(t2);
    st3.push(t3);
    ss.push(state);
  };
  function<void()> top = [&]() {
    n = sn.top();
    t1 = st1.top();
    t2 = st2.top();
    t3 = st3.top();
    state = ss.top();
  };
  function<void()> pop = [&]() {
    sn.pop();
    st1.pop();
    st2.pop();
    st3.pop();
    ss.pop();
  };
  n = sz; t1 = 1; t2 = 2; t3 = 3; state = 0;
  push();
  while (sn.size()) {
    top();
    pop();
    switch (state) {
    case 0:
      if (n < 1) continue;
      state = 1;
      push();
      n -= 1; swap(t2, t3); state = 0;
      push();
    continue;
    case 1:
      cout << "from " << t1 << " to " << t3 << '\n';
      n -= 1; swap(t1, t2); state = 0;
      push();
    }
  }
}

signed main() {
#ifdef ONLINE_JUDGE
  ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
#endif
  int n;
  cin >> n;
  hanio(n);
  return 0;
}