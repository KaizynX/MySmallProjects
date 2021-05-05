/*
 * @Author: Kaizyn
 * @Date: 2021-04-28 10:37:07
 * @LastEditTime: 2021-04-28 11:39:40
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
const int N = 50+7;

/*自定义字符串类 mystring，包含私有成员变量char *buf；成员函数包括：无参构造函数（输出"construct 0"）、带参构造函数（输出"construct 1"）、析构函数（输出"destruct"），输出函数，并重载运算符=（分别用类mystring 和strcpy、strcat函数，在"c++"之后添加键盘输入字符串信息）；在main（）中分别定义2个 mystring类对象str1（ch）和str2，其中ch为字符数组（从键盘输入字符信息为其赋值），直接通过语句str2=str1;使str2中的信息赋值为“c++”与str1中字符串的连接结果，分别输出str1和str2的字符串。
*/

class mystring {
 public:
  mystring() {
    buf = new char[1];
    buf[0] = 0;
    cout << "construct 0\n";
  }
  mystring(char *_buf) {
    buf = new char[strlen(_buf)+1];
    strcpy(buf, _buf);
    cout << "construct 1\n";
  }
  ~mystring() {
    delete[] buf;
    cout << "destruct\n";
  }
  mystring& operator =(const mystring &ms) {
    if (buf) delete buf;
    buf = new char[ms.len()+4];
    strcpy(buf, "c++");
    strcat(buf, ms.str());
    return *this;
  }
  char *str() const {
    return buf;
  }
  int len() const {
    return buf ? strlen(buf) : 0;
  }
  void print() {
    if (buf) puts(buf);
  }
 private:
  char *buf;
};

signed main() {
  char ch[N];
  scanf("%s", ch);
  mystring str1(ch);
  str1.print();
  mystring str2;
  str2 = str1;
  str2.print();
  return 0;
}