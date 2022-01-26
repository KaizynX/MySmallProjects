/*
 * @Author: Kaizyn
 * @Date: 2022-01-26 10:37:22
 * @LastEditTime: 2022-01-26 11:07:03
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
// const int K = 10;
const double H = 3.0;

typedef array<double, 4> T;
T train_x[N], test_x[N];
pair<double, int> dist[N];
double train_y[N];

double calc_dist(T &x, T &y) {
  double ans = 0;
  for (int i = 0; i < 4; ++i) {
    ans += (x[i] - y[i]) * (x[i] - y[i]);
  }
  return ans;
}

signed main() {
#ifdef ONLINE_JUDGE
  ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
#endif
// for (int K = 1; K; ++K) {
for (int K : {6}) {
  // ifstream train("\\astar2021\\Question_1_traindata.txt");
  ifstream train("Question_1_traindata.txt");
  for (int i = 1; i <= 1000; ++i) {
    for (int j = 0; j < 4; ++j) train >> train_x[i][j];
    // for (int &x : train_x[i]) train >> x;
    train >> train_y[i];
  }
  // orzeach(train_x[1]);
  train.close();
  // ifstream test("/astar2021/Question_1_testdata.txt");
  ifstream test("Question_1_testdata.txt");
  for (int i = 1; i <= 1000; ++i) {
    for (int j = 0; j < 4; ++j) test >> test_x[i][j];
    // for (int &x : test_x[i]) train >> x;
  }
  test.close();
  // ofstream answer("/astar2021/Question_1_answer.txt");
  ofstream answer("Question_1_answer.txt");
  int cnt = 0;
  for (int i = 1; i <= 1000; ++i) {
    for (int j = 1; j <= 1000; ++j) {
      dist[j] = {calc_dist(test_x[i], train_x[j]), j};
    }
    sort(dist + 1, dist + 1000 + 1);
    int ans = 0;
    /*
    for (int k = 1; k <= K; ++k) {
      ans += train_y[dist[k].second] >= H;
    }
    ans = ans >= (K + 1) / 2;
    */
    double live = 0;
    for (int k = 1; k <= K; ++k) {
      live += train_y[dist[k].second];
    }
    live /= K;
    ans = live >= H;

    cnt += ans;
    answer << ans << '\n';
  }
  cout << "K=" << K << ",cnt=" << cnt << '\n';
  answer.close();
}
  system("pause");
  return 0;
}