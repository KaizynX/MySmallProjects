/*
 * @Author: Kaizyn
 * @Date: 2021-04-07 10:53:54
 * @LastEditTime: 2021-04-07 11:29:17
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

class String {
 public:
  int length() const { return strlen(s); }
  friend istream& operator >>(istream &is, String &str) {
    static char buf[233];
    is >> buf;
    int len = strlen(buf);
    str.s = new char[len+1];
    for (int i = 0; i <= len; ++i) str.s[i] = buf[i];
    return is;
  }
  friend ostream& operator <<(ostream &os, String &str) {
    if(str.s) os << str.s;
    return os;
  }
  friend String operator +(String s1, String s2) {
    String s3;
    int l1 = s1.length(), l2 = s2.length();
    s3.s = new char[l1+l2+1];
    for (int i = 0; i < l1; ++i) s3.s[i] = s1.s[i];
    for (int i = 0; i <= l2; ++i) s3.s[l1+i] = s2.s[i];
    return s3;
  }
  String() {}
  String(const String &str) {
    s = new char[str.length()+1];
    for (int i = 0; i <= str.length(); ++i) s[i] = str.s[i];
  }
  String operator =(String str) {
    s = new char[str.length()+1];
    for (int i = 0; i <= str.length(); ++i) s[i] = str.s[i];
    return *this;
  }
  String substr(int j, int l) {
    String s3;
    // --j;
    s3.s = new char[l+1];
    for (int i = 0; i < l; ++i) s3.s[i] = s[j+i];
    s3.s[l] = '\0';
    return s3;
  }
 private:
  char *s;
};

signed main() {
  String s[5];
  char op;
  int i, j, k, l;
  cin >> s[1] >> s[2];
  while (cin >> op) {
    if (op == 'P') {
      cin >> i;
      cout << s[i] << '\n';
    } else if (op == 'C') {
      cin >> i >> j >> k;
      s[k] = s[i]+s[j];
    } else if (op == 'A') {
      cin >> i >> j;
      s[j] = s[i];
    } else {
      cin >> i >> j >> l >> k;
      s[k] = s[i].substr(j, l);
    }
  }
  return 0;
}