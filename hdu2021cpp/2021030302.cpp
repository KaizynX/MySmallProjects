/*
 * @Author: Kaizyn
 * @Date: 2021-03-04 14:42:19
 * @LastEditTime: 2021-03-04 16:48:47
 */
#include <bits/stdc++.h>

using namespace std;

list<int> l1, l2, l3;

void print(list<int> l) {
  while (l.size()) {
    cout << l.front();
    l.pop_front();
    if (l.size()) cout << "->";
    else cout << '\n';
  }
}

void merge(list<int> l1, list<int> l2, list<int> &l3) {
  /*
  l3.assign(l1.size()+l2.size(), 0);
  merge(l1.begin(), l1.end(), l2.begin(), l2.end(), l3.begin());
  */
}

signed main() {
  for (int i = 1, x; (cin >> x) && x; ++i) {
    if (i&1) l1.push_back(x);
    else l2.push_back(x);
  }
  print(l1);
  print(l2);
  merge(l1, l2, l3);
  print(l3);
  return 0;
}