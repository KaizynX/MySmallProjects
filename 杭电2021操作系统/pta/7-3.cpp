/*
 * @Author: Kaizyn
 * @Date: 2021-10-16 15:58:41
 * @LastEditTime: 2021-10-16 16:48:39
 */
#include <bits/stdc++.h>
using namespace std;

struct Source {
  vector<int> num;
  Source() = default;
  Source(int n) { num.resize(n); }
  operator vector<int>() const { return num; }
  operator int() const { return accumulate(num.begin(), num.end(), 0); }
  int& operator [] (const int &i) { return num.at(i); }
  bool check() const { return *min_element(num.begin(), num.end()) >= 0; }
  bool operator < (const Source &s) const { return num < s.num; }
  bool operator > (const Source &s) const { return num > s.num; }
  bool operator == (const Source &s) const { return num == s.num; }
  bool operator != (const Source &s) const { return num != s.num; }
  bool operator <= (const Source &s) const { return num <= s.num; }
  bool operator >= (const Source &s) const { return num >= s.num; }
  Source operator + (const Source &s) const { Source ret(*this); return ret += s; }
  Source operator - (const Source &s) const { Source ret(*this); return ret -= s; }
  Source& operator -= (const Source &s) {
    for (size_t i = 0; i < num.size(); ++i) {
      num[i] -= s.num[i];
    }
    return *this;
  }
  Source& operator += (const Source &s) {
    for (size_t i = 0; i < num.size(); ++i) {
      num[i] += s.num[i];
    }
    return *this;
  }
  friend istream& operator >> (istream &is, Source &s) {
    for (size_t i = 0; i < s.num.size(); ++i) is >> s[i];
    return is;
  }
};

struct _pcb {
  int pid;
  Source max_request, has_request;
  _pcb() = default;
  _pcb(int n) : max_request(n), has_request(n) {}
  bool operator == (const int &id) const { return pid == id; }
  bool operator < (const _pcb &p) const {
    return int(max_request-has_request) < int(p.max_request-p.has_request);
  }
  friend ostream& operator << (ostream &os, const _pcb &p) {
    return os << 'P' << setfill('0') << setw(2) << p.pid;
  }
};

bool safe_check(vector<_pcb> pcbs, Source reserve_source, int print = 0) {
  while (pcbs.size()) {
    auto it = min_element(pcbs.begin(), pcbs.end());
    reserve_source -= it->max_request - it->has_request;
    if (!reserve_source.check()) return false;
    reserve_source += it->max_request;
    if (print) cout << *it << '\n';
    pcbs.erase(it);
  }
  return true;
}

int main() {
  int source_num, process_num;
  cin >> source_num >> process_num;
  vector<_pcb> pcbs;
  Source reserve_source(source_num);
  pcbs.resize(process_num, source_num);
  for (int i = 0; i < process_num; ++i) {
    pcbs[i].pid = i;
    cin >> pcbs[i].max_request;
  }
  for (int i = 0; i < process_num; ++i) {
    cin >> pcbs[i].has_request;
  }
  cin >> reserve_source;
  Source apply_request(source_num);
  for (int pid; cin >> pid >> apply_request; ) {
    auto p = find(pcbs.begin(), pcbs.end(), pid);
    p->has_request += apply_request;
    reserve_source -= apply_request;
    if (!reserve_source.check()) { // ???
      assert(0);
    }
    if (!safe_check(pcbs, reserve_source, 0)) {
      cout << "unsafe\n";
    } else {
      cout << "safe\n";
      safe_check(pcbs, reserve_source, 1);
    }
  }
  return 0;
}