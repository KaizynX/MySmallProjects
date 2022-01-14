/*
 * @Author: Kaizyn
 * @Date: 2021-10-16 10:23:38
 * @LastEditTime: 2021-10-16 10:56:15
 */
#include <bits/stdc++.h>
using namespace std;
constexpr int READY = 1;
constexpr int RUNNING = 2;
constexpr int TIMESLICE = 2;

struct _pcb {
  int pid;
  int state;
  int time;
  friend ostream& operator << (ostream &os, const _pcb &p) {
    return os << 'P' << setfill('0') << setw(2) << p.pid;
  }
};

typedef vector<_pcb>::iterator ptr;

string to_lower(string str) {
  transform(str.begin(), str.end(), str.begin(), ::tolower);
  return str;
}

template <typename T>
ptr get_next(vector<_pcb> &pcbs, T cmp) {
  ptr ret = pcbs.end();
  for (ptr it = pcbs.begin(); it != pcbs.end(); ++it) {
    if (it->state != READY) continue;
    if (cmp(it, ret)) ret = it;
  }
  return ret;
}

int main() {
  int n;
  string method;
  vector<_pcb> pcbs;
  cin >> method >> n;
  pcbs.resize(n);
  for (int i = 0; i < n; ++i) {
    cin >> pcbs[i].time;
    pcbs[i].pid = i;
    pcbs[i].state = READY;
  }
  cout << method << '\n';
  method = to_lower(method);
  auto cmp = [&pcbs, &method](ptr x, ptr y) {
    if (y == pcbs.end()) return true;
    if (x == pcbs.end()) return false;
    return method == "fcfs" ? x < y : x->time < y->time;
  };
  _pcb p;
  ptr cur = pcbs.end();
  while (true) {
    if (cur == pcbs.end()) cur = get_next(pcbs, cmp);
    if (cur == pcbs.end()) break;
    p = move(*cur);
    pcbs.erase(cur);
    cout << p << '\n';
    p.state = RUNNING;
    p.time -= TIMESLICE;
    cur = get_next(pcbs, cmp);
    if (p.time <= 0) continue;
    p.state = READY;
    pcbs.emplace_back(p);
  }
  return 0;
}