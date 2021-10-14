/*
 * @Author: Kaizyn
 * @Date: 2021-10-13 11:16:47
 * @LastEditTime: 2021-10-14 13:14:15
 */
#include <bits/stdc++.h>
using namespace std;

struct _pcb {
  long pid;
  char name[20];
  int strategy; // 控制策略
  int priority; // 优先级
  // int *stack; // 栈指针
  // _pcb *next;
  friend istream& operator >> (istream &is, _pcb &p) {
    return is >> p.pid >> p.name >> p.strategy >> p.priority;
  }
  friend ostream& operator << (ostream &os, const _pcb &p) {
    // return os << p.pid << ' ' << p.name << ' ' <<  p.strategy << ' ' << p.priority << '\n';
    return os << p.pid << '\n' << p.priority << '\n';
    // return os << p.pid << '\n' << p.strategy << '\n';
  }
};

struct Manager {
  vector<_pcb> pcbs;
  void append(_pcb &p) {
    pcbs.emplace_back(p);
  }
  void sort() {
    ::sort(pcbs.begin(), pcbs.end(), [](_pcb &x, _pcb &y) {
      return x.priority == y.priority ? x.pid < y.pid : x.priority < y.priority;
    });
  }
  void print() {
    for (_pcb &p : pcbs) {
      cout << p.pid << '\n';
    }
  }
  auto find(long pid) {
    for (auto it = pcbs.begin(); it != pcbs.end(); ++it) {
      if (it->pid == pid) return it;
    }
    return pcbs.end();
  }
  auto modify(long pid, int what) {
    auto p = find(pid);
    if (p != pcbs.end()) {
      p->priority = what;
      // p->strategy = what;
    }
    return p;
  }
  void _delete(long pid) {
    auto p = find(pid);
    if (p != pcbs.end()) {
      pcbs.erase(p);
    }
  }
  void insert(long pid, _pcb &p) {
    auto it = find(pid);
    if (it != pcbs.end()) {
      pcbs.insert(it+1, p);
    }
  }
};

Manager manager;

int main() {
  string str, opt;
  long pid, what;
  stringstream ss;
  _pcb p;
  while (getline(cin, str)) {
    ss.clear();
    ss << str;
    if (isdigit(str[0])) {
      ss >> p;
      manager.append(p);
    } else {
      ss >> opt;
      if (opt == "sort") {
        manager.sort();
      } else if (opt == "append") {
        ss >> p;
        manager.append(p);
      } else if (opt == "modify") {
        ss >> pid >> what;
        cout << *manager.modify(pid, what);
      } else if (opt == "delete") {
        ss >> pid;
        manager._delete(pid);
      } else if (opt == "insert") {
        ss >> pid >> p;
        manager.insert(pid, p);
      } else if (opt == "find") {
        ss >> pid;
        cout << *manager.find(pid);
      }
      if (opt != "modify" && opt != "find") manager.print();
    }
  }
  return 0;
}