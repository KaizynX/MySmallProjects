/*
 * @Author: Kaizyn
 * @Date: 2021-10-13 11:16:47
 * @LastEditTime: 2021-10-14 20:01:30
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
  bool operator < (const _pcb &p) const {
    return priority == p.priority ? pid < p.pid : priority < p.priority;
  }
  bool operator == (const long &id) const {
    return pid == id;
  }
  friend istream& operator >> (istream &is, _pcb &p) {
    return is >> p.pid >> p.name >> p.strategy >> p.priority;
  }
  friend ostream& operator << (ostream &os, const _pcb &p) {
    return os << p.pid << '\n' << p.priority << '\n';
  }
};

struct Manager {
  list<_pcb> pcbs; // vector<_pcb> pcbs;
  void append(_pcb &p) {
    pcbs.push_back(p);
  }
  void sort() {
    pcbs.sort();
    // ::sort(pcbs.begin(), pcbs.end());
  }
  void print() {
    for (_pcb &p : pcbs) cout << p.pid << '\n';
  }
  auto find(long pid) {
    return ::find(pcbs.begin(), pcbs.end(), pid);
  }
  auto modify(long pid, int priority) {
    auto p = find(pid);
    if (p != pcbs.end()) p->priority = priority;
    return p;
  }
  void _delete(long pid) {
    auto p = find(pid);
    if (p != pcbs.end()) pcbs.erase(p);
  }
  void insert(long pid, _pcb &p) {
    auto it = find(pid);
    if (it != pcbs.end()) pcbs.insert(++it, p);
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