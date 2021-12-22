/*
 * @Author: Kaizyn
 * @Date: 2021-12-15 21:59:25
 * @LastEditTime: 2021-12-22 16:03:33
 */
#include <bits/stdc++.h>

// #define DEBUG

#ifdef MULTI_THREAD
#include <thread>
#endif

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
constexpr int INF = 1e9;
constexpr double eps = 1e-2; // 精度,若修改注意int范围

struct Node {
  int x, y;
  Node() {}
  Node(int _x, int _y) : x(_x), y(_y) {}
  bool operator < (const Node &rhs) const {
    return make_pair(x, y) < make_pair(rhs.x, rhs.y);
  }
  // 计算两点间距离
  friend int calc_dis(Node &a, Node &b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
  }
  friend istream& operator >> (istream &is, Node &nd) {
    static double x, y;
    is >> x >> y;
    nd = Node(x / eps + .5, y / eps + .5);
    return is;
  }
  friend ostream& operator << (ostream &os, const Node &nd) {
    return os << nd.x * eps << ' ' << nd.y * eps;
  }
};

struct Timer {
  clock_t t;
  void start(string name = "program") {
    cerr << name << " start!\n";
    t = clock();
  }
  void stop(string name = "program") {
    // cerr << name << " end. Elapsed Time: " << (clock() - t) / CLOCKS_PER_SEC  << " s\n";
    cerr << name << " end. Elapsed Time: " << (clock() - t) << " ms\n";
  }
} timer;

using Edge = vector<Node>;
vector<Edge> edges;
vector<vector<int>> dist[2][2];

template <typename T>
void Min(T &x, const T &y) {
  if (y < x) x = y;
}

void Input() {
  string filename = "test.txt";
  cout << "输入文件名:"; cin >> filename;
  ifstream file(filename, ios::in);
  int move_tag;
  Node point;
  Edge edge;
  while (file >> point  >> move_tag) {
    if (point.x == 0 && point.y == 0 && move_tag == 0) break;
    assert(move_tag == 0); // 若出错说明数据格式不是预期的
    edge.clear();
    while (file >> point >> move_tag && move_tag <= 0) {
      edge.emplace_back(point);
    }
    edge.emplace_back(point);
    assert(edge.size() >= 2u); // 一条线段必然由两个以上点构成
    edges.emplace_back(edge);
  }
  file.close();
}

// 计算两条边端点间距离 0(from begin to end) 1(from rbegin to rend)
void CalcDist() {
  int num = edges.size();
  for (int ui : {0, 1})
  for (int vi : {0, 1}) {
    auto &dis = dist[ui][vi];
    dis.resize(num, vector<int>(num));
    for (int i = 0; i < num; ++i)
    for (int j = 0; j < num; ++j) {
      dis[i][j] = calc_dis(
          ui ? *edges[i].begin() : *edges[i].rbegin(),
          vi ? *edges[j].rbegin() : *edges[j].begin()
      );
    }
  }
}

void Output(vector<int> seq) {
  static string filename = "out.txt";
  static vector<int> dp[2], path[2];
  for (int i : {0, 1}) {
    dp[i].resize(seq.size());
    path[i].resize(seq.size());
  }
  dp[0][0] = dp[1][0] = 0;
  for (unsigned i = 1; i < seq.size(); ++i) {
    dp[0][i] = dp[1][i] = INF;
    for (int ui : {0, 1})
    for (int vi : {0, 1}) {
      int val = dp[ui][i - 1] + dist[ui][vi][seq[i - 1]][seq[i]];
      if (val < dp[vi][i]) {
        dp[vi][i] = val;
        path[vi][i] = ui;
      }
    }
  }

  ofstream file(filename, ios::out);
  int state = dp[0].back() < dp[1].back() ? 0 : 1;
  for (int i = seq.size() - 1; i >= 0; state = path[state][i], --i) {
    auto edge = edges[seq[i]];
    if (!state) reverse(edge.begin(), edge.end());
    file << edge[0] << " 0\n"; // 不知道有什么用但输入格式如此
    for (unsigned j = 0; j < edge.size(); ++j) {
      file << edge[j];
      if (j + 1 == edge.size()) file << " 33\n";
      else if (j == 0) file << " -33\n";
      else file << " 0\n";
    }
  }
  file << "0 0 0\n";
  file.close();
}

namespace GA {
constexpr double Pcross = 0.75; // 交叉概率
constexpr double Pmutation = 0.15; // 变异概率
constexpr double Cross_part = 0.4; // 交叉比例
constexpr int Max_epoc = 20000; // 最大迭代次数
constexpr int Pop_size = 100; // 种群大小
using Colony = vector<int>;

mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());
std::default_random_engine random(rnd());
std::uniform_int_distribution<int> rnd_Pop(0, Pop_size - 1), rnd_Num;
vector<Colony> populations;
vector<int> energy;
int num, cross_size;
int ans_energy = INF;
Colony ans;
#ifdef MULTI_THREAD
std::thread write_thread;
#endif

void InitPop();                       // 初始化种群
void CalcFitness();                   // 计算适应值
void Select();                        // 选择算子
void Cross();                         // 交叉算子
void Mutation();                      // 变异算子
double CalcEnergy(const Colony&);     // 计算路程长度

int Solve() {
  timer.start();
  num = edges.size();
  cross_size = num * Cross_part;
  rnd_Num = std::uniform_int_distribution<int>(0, num - 1);
  InitPop();
  for (int i = 0; i < Max_epoc; ++i) {
    Select();//选择(复制)
    Cross();//交叉
    Mutation();//变异
    CalcFitness();//计算适应值
    int id = min_element(energy.begin(), energy.end()) - energy.begin();
    if (energy[id] < ans_energy) {
      ans_energy = energy[id];
      ans = populations[id];
      cerr << i << "\tth iteration, distance: " << ans_energy * eps << '\n';
      timer.stop();
#ifdef MULTI_THREAD
      if (write_thread.joinable()) write_thread.join();
      write_thread = thread(output, ans);
      write_thread.detach();
#else
      Output(ans); // 关掉以节省时间
#endif
    }
    #ifdef DEBUG
    cerr << i << "th iteration, energy = " << ans_energy << '\n';
    for (auto &population : populations) orzeach(population);
    #endif
  }
  return ans_energy;
}

void InitPop() {
  populations.resize(Pop_size);
  // fitness.resize(Pop_size);
  energy.resize(Pop_size);
  for (Colony &population : populations) {
    population.resize(num);
    iota(population.begin(), population.end(), 0);
    shuffle(population.begin(), population.end(), rnd);
  }
  iota(populations[0].begin(), populations[0].end(), 0); // 原顺序
  CalcFitness();
}

void CalcFitness() {
  for (int i = 0; i < Pop_size; ++i) {
    energy[i] = CalcEnergy(populations[i]);
  }
}

// 锦标赛选择法
void Select() {
  static vector<Colony> tmp(Pop_size);
  for (int i = 0, x, y; i < Pop_size; ++i) {
    x = rnd_Pop(random);
    y = rnd_Pop(random);
    if (energy[x] > energy[y]) swap(x, y);
    tmp[i] = populations[x];
  }
  swap(tmp, populations);
}

void Unique(Colony &seq) {
  vector<int> cnt(num, 0);
  for (int &i : seq) ++cnt[i];
  int j = 0;
  for (int &i : seq) {
    if (cnt[i] > 1) {
      --cnt[i];
      while (cnt[j] > 0) ++j;
      i = j;
      j++;
    }
  }
}

void Cross() {
  static Colony tmp[2];
  for (int i = 1; i < Pop_size; ++i) {
    double p = rnd() % (int)1e9 / 1e9;
    if (p > Pcross) continue;
    int s = rnd() % (num - cross_size);
    tmp[0] = populations[i - 1];
    tmp[1] = populations[i];
    copy(populations[i - 1].begin() + s, populations[i - 1].begin() + s + cross_size,  tmp[1].begin() + s);
    copy(populations[i].begin() + s, populations[i].begin() + s + cross_size,  tmp[0].begin() + s);
    Unique(tmp[0]);
    Unique(tmp[1]);
    swap(tmp[0], populations[i - 1]);
    swap(tmp[1], populations[i]);
  }
}

void Mutation() {
  for (int i = 0, x, y; i < Pop_size; ++i) {
    double p = rnd() % (int)1e9 / 1e9;
    if (p > Pmutation) continue;
    x = rnd_Num(random);
    y = rnd_Num(random);
    swap(populations[i][x], populations[i][y]);
  }
}

double CalcEnergy(const Colony &pop) {
  static int dp[2][2];
  dp[0][0] = dp[0][1] = 0;
  for (unsigned i = 1; i < pop.size(); ++i) {
    int *cur = dp[i & 1], *pre = dp[~i & 1];
    cur[0] = cur[1] = INF;
    for (int ui : {0, 1})
    for (int vi : {0, 1}) {
      Min(cur[vi], pre[ui] + dist[ui][vi][pop[i - 1]][pop[i]]);
    }
  }
  return min(dp[~pop.size() & 1][0], dp[~pop.size() & 1][1]);
}

} // namespace GA

signed main() {
  Input();
  cerr << "The size of edges is : " << edges.size() << '\n';
  CalcDist();

  int ans_energy = GA::Solve();
  cerr << "The distance of empty path is " << ans_energy * eps << '\n';

  system("pause");
  return 0;
}