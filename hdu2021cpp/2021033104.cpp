/*
 * @Author: Kaizyn
 * @Date: 2021-03-31 10:54:18
 * @LastEditTime: 2021-03-31 11:03:41
 */
#include <bits/stdc++.h>

// #define DEBUG

using namespace std;

const double eps = 1e-7;
const double PI = acos(-1);
typedef pair<int, int> pii;
typedef long long ll;
const int MOD = 998244353; // 1e9+7;
const int INF = 0x3f3f3f3f;
// const ll INF = 1e18;
const int N = 1e6+7;

class Student {
 public:
  Student() {}
  Student(string nm, int h, int w) : name(nm), height(h), weight(w) {}
  bool none() const {
    return name.empty();
  }
  bool operator <(Student &s) const {
    if (none()) return 1;
    return height < s.height;
  }
  void display() {
    cout << name << ' ' << height << ' ' << weight;
  }
 private:
  string name;
  int height, weight;
};

int n;
Student dorm[N];

signed main() {
#ifdef ONLINE_JUDGE
  // ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
#endif
  cin >> n;
  int id, h, w;
  string name;
  for (int i = 1; i <= n; ++i) {
    cin >> id >> name >> h >> w;
    Student stu(name, h, w);
    if (dorm[id] < stu) dorm[id] = stu;
  }
  for (int i = 0; i < 1e6; ++i) {
    if (dorm[i].none()) continue;
    printf("%06d ", i);
    dorm[i].display();
    cout << '\n';
  }
  return 0;
}