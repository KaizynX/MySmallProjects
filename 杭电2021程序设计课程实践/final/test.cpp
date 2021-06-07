/*
 * @Author: Kaizyn
 * @Date: 2021-06-04 20:41:17
 * @LastEditTime: 2021-06-05 10:45:13
 */
#include <bits/stdc++.h>
#include <tchar.h> 

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

// basic_string<wchar_t> s;
// wstring s;

string buf; // 全局字符缓冲区

// 去除首尾空字符
string trim(string str) {
  str.erase(0, str.find_first_not_of(_T(" \n\r\t")));
  str.erase(str.find_last_not_of(_T(" \n\r\t")) + 1);
  return str;
}


// 输入函数,如果输入不符合要求就一直输入直到正确为止
template <class T>
void input(istream &is, T &obj) {
  for (bool ok = false; !ok; ) {
    getline(is, buf);
    try {
      ok = obj.check();
    } catch (const char* msg) {
      cerr << "错误:" << msg << "请重新输入:" << endl;
    }
  }
}

class IdNumber {
 public:
  friend istream& operator >>(istream &is, IdNumber &in) {
    cout << endl;
    input(is, in);
    return is;
  }
  friend ostream& operator <<(ostream &os, const IdNumber &in) {
    return os << in.id;
  }
  bool check() {
    id = trim(buf);
    if (id.empty()) return throw "输入不能为空", false;
    if (id.size() != 15u && id.size() != 18u) return throw "位数不对", false;
    if (regex_match(id, regex("^[1-9]\\d{5}\\d{2}((0[1-9])|(10|11|12))(([0-2][1-9])|10|20|30|31)\\d{3}$")) ||
        regex_match(id, regex("^[1-9]\\d{5}(18|19|([23]\\d))\\d{2}((0[1-9])|(10|11|12))(([0-2][1-9])|10|20|30|31)\\d{3}[0-9Xx]$")))
      return true;
    throw "输入错误"; return false;
  }
 private:
  string id;
};

signed main() {
#ifdef ONLINE_JUDGE
  ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
#endif
  IdNumber id;;
  cin >> id;
  cout << id << endl;
  return 0;
}
/*
lanhua wang
third
13777777777
331003199901016666
hdu
A66666
shit
san zhang
15555555555
r
y
y
1:0:1
23:59:59
2:0:1
20:0:0
*/