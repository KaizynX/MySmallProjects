/*
 * @Author: Kaizyn
 * @Date: 2021-04-28 09:52:43
 * @LastEditTime: 2021-04-28 10:18:54
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
// const int N = ;

class Date {
 protected:
  int year;
  int month;
  int day;
};

struct Time {
 protected:
  int hour;
  int minute;
  int second;
};

class Schedule : public Date, public Time{
 public:
  bool read() {
    scanf("%d", &ID);
    if (!ID) return false;
    scanf("%d/%d/%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);
    return true;
  }
  void print() {
    printf("The urgent schedule is No.%d: %d/%d/%d %d:%d:%d\n", ID, year, month, day, hour, minute, second);
  }
  bool operator < (const Schedule & s2) {//判断当前日程时间是否早于s2
    return vector<int>{year, month, day, hour, minute, second} <
        vector<int>{s2.year, s2.month, s2.day, s2.hour, s2.minute, s2.second};
  }
 private:
  int ID;//日程的ID
};

signed main() {
  Schedule s1, s2;
  s1.read();
  while (s2.read()) {
    if (s2 < s1) s1 = s2;
  }
  s1.print();
  return 0;
}