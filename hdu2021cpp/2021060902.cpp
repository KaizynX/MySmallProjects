/*
 * @Author: Kaizyn
 * @Date: 2021-06-09 10:25:26
 * @LastEditTime: 2021-06-09 11:40:31
 */
#include <bits/stdc++.h>

using namespace std;

template <class T>
class Queue {
 public:
  void push_back(T x) {
    v.push_back(x);
  }
  T pop() {
    T x = v.front();
    v.erase(v.begin());
    return x;
  }
  void assign(Queue<T> q) {
    v = q.v;
  }
  void print() {
    for (T &i : v) cout << i << ' ';
  }
 private:
  vector<T> v;
};

template <class T>
inline void solve() {
  vector<Queue<T>> v(5);
  string op;
  T x;
  int n;
  cin >> n; 
  cout << "Start:\n";
  for (int _ = n, i, i2; _; --_) {
    cin >> op;
    if (op == "push") {
      cin >> i >> x;
      v[i].push_back(x);
    } else if (op == "pop") {
      cin >> i;
      cout << v[i].pop() << ' ';
    } else if (op == "assign") {
      cin >> i >> i2;
      v[i2].assign(v[i]);
    }
  }
  v[4] = v[1];
  cout << "\nFinal:\n";
  for (int i = 1; i <= 4; ++i) {
    v[i].print();
    cout << '\n';
  }
}

signed main() {
  string T;
  cin >> T;
  if (T == "int") {
    solve<int>();
  } else if (T == "string") {
    solve<string>();
  }
  return 0;
}