/*
 * @Author: Kaizyn
 * @Date: 2021-05-26 10:07:25
 * @LastEditTime: 2021-05-26 11:04:00
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

template <class T>
struct Vector {
  T *arr;
  int cap, siz;
 public:
  void reallocate(int _cap) {
    if (arr) delete [] arr;
    arr = new T[cap = _cap];
    if (!arr) return cerr << "oh no!\n", void();
  }
  Vector(int _siz) : siz(_siz) {
    arr = nullptr;
    reallocate(siz);
  }
  void error(int x) {
    // cout << "invalid index:" << x << ' ';
    cout << " invalid index:" << x;
  }
  void put(int x, T y) {
    if (x < 0 || x >= siz) return error(x);
    arr[x] = y;
  }
  void push(T x) {
    if (siz >= cap) reallocate(cap*2);
    arr[siz++] = x;
  }
  void fetch(int x) {
    if (x < 0 || x >= siz) return error(x);
    // cout << arr[x] << ' ';
    cout << ' ' << arr[x];
    // return arr[x];
  }
};

template <class T>
inline void work(Vector<T> &v) {
  string str;
  T x;
  int id;
  while (cin >> str && str != "quit") {
    if (str == "push") {
      cin >> x;
      v.push(x);
    } else if (str == "put") {
      cin >> id >> x;
      v.put(id, x);
    } else if (str == "fetch") {
      cin >> id;
      v.fetch(id);
    }
  }
  cout << '\n';
}

signed main() {
  string str;
  int x;
  while (cin >> str >> x) {
    if (str == "int") {
      Vector<int> v(x);
      work(v);
    } else if (str == "string") {
      Vector<string> v(x);
      work(v);
    }
  }
  return 0;
}