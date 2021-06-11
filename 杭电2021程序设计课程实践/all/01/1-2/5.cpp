/*
 * @Author: Kaizyn
 * @Date: 2021-03-27 23:17:27
 * @LastEditTime: 2021-03-27 23:19:49
 */
#include <bits/stdc++.h>

using namespace std;

stack<int> stk;
queue<int> que;

int main() {
  for (int a; cin >> a; ) {
    if (a > 0) stk.push(a);
    if (a < 0) que.push(a);
  }
  for ( ; stk.size(); cout << stk.top() << ' ', stk.pop());
  cout << '\n';
  for ( ; que.size(); cout << que.front() << ' ', que.pop());
  cout << '\n';
  return 0;
}
/*
1 -2 8 -8 2 -9 5
*/