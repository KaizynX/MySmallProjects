/*
 * @Author: Kaizyn
 * @Date: 2021-10-13 11:16:47
 * @LastEditTime: 2021-10-13 11:33:26
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
    return is >> pid >> name >> strategy >> priority;
  }
};

struct Manager {
  vector<_pcb> pcbs;
  void append(_pcb &p) {
    pcbs.emplace_back(p);
  }
  void sort() {
    sort(pcbs.begin(), pcbs.end(), [](_pcb &x, _pcb &y) {
      return x.priority == y.priority ? x.pid < y.pid : x.priority > y.priority;
    });
  }
  void print() {
    for (_pcb &p : pcbs) {
      cout << p.pid << '\n';
    }
  }
  auto find(int pid) {
    for (auto it = pcbs.begin(); it != pcbs.end(); ++it) {
      if (it->pid == pid) return it;
    }
    return pcbs.end();
  }
  void modify(int pid, int what) {
    auto p = find(pid);
    if (p != pcbs.end()) {
      p->priority = what;
    }
    cout << pid << '\n' << what << '\n';
  }
  void _delete(int pid) {
    auto p = find(pid);
    if (p != pcbs.end()) {
      pcbs.erase(p);
    }
  }
  void insert(int pid, _pcb &p) {
    pcbs.insert(find(pid), p);
  }
};

Manager manager;

int main() {
  string str, opt;
  stringstream ss;
  _pcb p;
  while (getline(cin, str)) {
    ss.clear();
    ss >> str;
    if (isdigit(str[0])) {
      ss << p;
      manager.append(p);
    } else {
      ss << opt;
      if (opt == "sort") {
        manager.sort();
      } else if (opt == "append") {
        ss << p;
        manager.append(p);
      } else if (opt == "")
      if (opt != "modify") manager.print();
    }
  }
  return;
}