/*
 * @Author: Kaizyn
 * @Date: 2021-10-12 16:18:08
 * @LastEditTime: 2021-10-15 08:56:54
 */
#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
template <typename T>
using greater_queue = priority_queue<T, vector<T>, greater<T>>;
constexpr int timeslice = 2;

void print(int id) {
  printf("P%02d\n", id);
}

template <typename T>
T get_front(queue<T> &q) {
  return q.front();
}

template <typename T>
T get_front(greater_queue<T> &q) {
  return q.top();
}

template <typename T>
void work(T &q) {
  pii cur = get_front(q);
  q.pop();
  print(cur.second);
  cur.first -= timeslice;
  if (cur.first > 0) q.push(cur);
}

template <int giao, typename T>
void solve(T q) {
  int n;
  cin >> n;
  for (int i = 0, t; i < n; ++i) {
    cin >> t;
    q.push(make_pair(t, i));
    // if (giao) work(q);
  }
  while (q.size()) work(q);
}

string to_lower(string str) {
  transform(str.begin(), str.end(), str.begin(), ::tolower);
  return str;
}

int main() {
  string method;
  cin >> method;
  cout << method << '\n';
  method = to_lower(method);
  if (method == "fcfs") {
    solve<0>(queue<pii>());
  } else if (method == "spf") {
    solve<1>(greater_queue<pii>());
  }
}