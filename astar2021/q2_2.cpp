/*
 * @Author: Kaizyn
 * @Date: 2022-01-26 13:29:29
 * @LastEditTime: 2022-01-26 13:30:39
 */
/*
 * @Author: Kaizyn
 * @Date: 2022-01-26 11:18:58
 * @LastEditTime: 2022-01-26 11:52:54
 */
#include <bits/stdc++.h>

#define DEBUG

using namespace std;
namespace hjt {
template<typename A,typename B>
std::ostream &operator<<(std::ostream &o,const std::pair<A,B> &x){
  return o<<'('<<x.first<<','<<x.second<<')';
}
#define repeat(i,a,b) for(int i=(a),_=(b);i<_;i++)
#define repeat_back(i,a,b) for(int i=(b)-1,_=(a);i>=_;i--)
#define qwq [&]{cerr<<"qwq"<<endl;}()
#define orz(x) [&]{cerr<<#x": "<<x<<endl;}()
#define orzarr(a,n) [&]{cerr<<#a": "; repeat(__,0,n)cerr<<(a)[__]<<" "; cerr<<endl;}()
#define orzeach(a) [&]{cerr<<#a": "; for(auto __:a)cerr<<__<<" "; cerr<<endl;}()
#define pause [&]{system("pause");}()
} using namespace hjt;

typedef long long ll;
typedef pair<int, int> pii;
const double eps = 1e-7;
const double PI = acos(-1);
const int MOD = 998244353; // 1e9+7;
const int INF = 0x3f3f3f3f;
// const ll INF = 1e18;
const int N = 1e3 + 7;

struct Node {
  double xl, xr, yl, yr, vx, vy;
  void get_v(const Node &nd) {
    vx = xl - nd.xl;
    vy = yl - nd.yl;
  }
  void fly() {
    xl += vx;
    xr += vx;
    yl += vy;
    yr += vy;
  }
  bool check_v() {
    return vx != 0.0 || vy != 0.0;
  }
  bool check() {
    return !(xl < 0 || yl < 0 || xr > 5000 || yr > 5000);
  }
  bool operator == (const Node &nd) {
    return abs(xl - nd.xl) < eps
        && abs(xr - nd.xr) < eps
        && abs(yl - nd.yl) < eps
        && abs(yr - nd.yr) < eps;
  }
  bool match(const Node &nd) {
    return abs((xr - xl) - (nd.xr - nd.xl)) < eps
        && abs((yr - yl) - (nd.yr - nd.yl)) < eps;
  }
  friend istream& operator >> (istream &is, Node &nd) {
    nd.vx = nd.vy = 0.0;
    return is >> nd.xl >> nd.yl >> nd.xr >> nd.yr;
  }
  friend ostream& operator << (ostream &os, const Node &nd) {
    return os << ' ' << nd.xl << ' ' << nd.yl << ' ' << nd.xr << ' ' << nd.yr;
  }
};

int n;
vector<Node> arr[N];
ifstream in("Question_2_data.txt");
ofstream out("Question_2_result.txt");

void print(vector<Node> &arr) {
  out << arr.size();
  for (auto &x : arr) out << x;
  out << '\n';
}

inline void solve() {
  in >> n;
  for (int i = 0, k; i < n; ++i) {
    in >> k;
    arr[i].resize(k);
    for (auto &x : arr[i]) in >> x;
  }
  for (int i = n - 36; i < n - 26; ++i) {
    print(arr[i]);
  }
}

signed main() {
#ifdef ONLINE_JUDGE
  ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
#endif
  // while (in >> n) solve();
  constexpr int T = 60;
  for (int i = 1; i <= T; ++i) {
    solve();
    cout << i << "'th OK!\n";
  }
  return 0;
}