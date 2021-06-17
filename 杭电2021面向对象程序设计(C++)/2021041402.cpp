/*
 * @Author: Kaizyn
 * @Date: 2021-04-14 11:41:52
 * @LastEditTime: 2021-04-14 11:55:48
 */
#include <bits/stdc++.h>

// #define DEBUG

using namespace std;

class CUIControl {
 public:
  virtual void Clicked() {}
  string get_name() { return name; }
  friend istream& operator >>(istream &is, CUIControl &c) {
    return is >> c.name;
  }
 private:
  string name;
};

// 菜单类
class CMenu : public CUIControl {
 public:
  virtual void Clicked() {
    cout << "menu-" << get_name() << " Clicked\n";
  }
};
// 按钮类
class CButton : public CUIControl {
 public:
  virtual void Clicked() {
    cout << "button-" << get_name() << " Clicked\n";
  }
};

void clear(vector<CUIControl*> &vec) {
  while (vec.size()) {
    delete vec.back();
    vec.pop_back();
  }
}

signed main() {
  int n;
  string str;
  vector<CUIControl*> vec; 
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    CUIControl *cur;
    cin >> str;
    if (str == "menu") {
      cur = new CMenu;
    } else {
      cur = new CButton;
    }
    cin >> *cur;
    vec.emplace_back(cur);
  }
  while (cin >> str) {
    int x;
    cin >> x;
    vec[x-1]->Clicked();
  }
  clear(vec);
  return 0;
}