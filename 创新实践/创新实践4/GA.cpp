/*
 * @Author: Kaizyn
 * @Date: 2021-12-15 21:59:25
 * @LastEditTime: 2021-12-15 23:52:02
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

using Edge = vector<Node>;
vector<Edge> edges;
vector<vector<int>> dist[2][2];

template <typename T>
void Min(T &x, const T &y) {
  if (y < x) x = y;
}

void Input() {
  string filename = "test.txt";
  // cout << "输入文件名:\n"; cin >> filename;
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
  #ifdef DEBUG
  orzeach(points);
  #endif
}

// 计算两条边端点间距离
void CalcDist() {
  int num = edges.size();
  for (int ui : {0, 1})
  for (int vi : {0, 1}) {
    auto dis = dist[ui][vi];
    dis.resize(num, vector<int>(num));
    for (int i = 0; i < num; ++i)
    for (int j = i + 1; j < num; ++j) {
      dis[i][j] = dis[j][i] = calc_dis(
          ui ? *edges[i].rbegin() : *edges[i].begin(),
          vi ? *edges[i].rbegin() : *edges[i].begin()
      );
    }
  }
}

void Output(vector<int> seq) {
  static string filename = "out.txt";
  ofstream file(filename, ios::out);
  for (int i : seq) {
    file << edges[i][0] << " 0\n";
    for (unsigned j = 0; j < edges[i].size(); ++j) {
      file << edges[i][j];
      if (j + 1 == edges[i].size()) file << " 33\n";
      else if (j == 0) file << " -33\n";
      else file << " 0\n";
    }
  }
  file << "0 0 0\n";
  file.close();
}

// TODO: 并无有效使用适应函数, 交换函数
namespace GA {
constexpr double Pcross = 0.5; // 交叉概率
constexpr double Pmutation = 0.1; // 变异概率
constexpr double Cross_part = 0.4; // 交叉比例
constexpr int Max_epoc = 200; // 最大迭代次数
constexpr int Pop_size = 20; // 种群大小
using Colony = vector<int>;

mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());
std::default_random_engine random(rnd());
std::uniform_int_distribution<int> rnd_Pop(0, Pop_size - 1);
vector<Colony> populations;
vector<double> fitness, energy;
int num, cross_size;
double ans_energy;
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

void Solve() {
  num = edges.size();
  cross_size = num * Cross_part;
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
#ifdef MULTI_THREAD
      if (write_thread.joinable()) write_thread.join();
      write_thread = thread(output, ans);
      write_thread.detach();
#else
      Output(ans); // 关掉以节省时间
#endif
    }
  }
}

void InitPop() {
  populations.resize(Pop_size);
  fitness.resize(Pop_size);
  energy.resize(Pop_size);
  for (Colony &population : populations) {
    populations.resize(num);
    iota(population.begin(), population.end(), 0);
    shuffle(population.begin(), population.end(), rnd);
  }
  CalcFitness();
}

void CalcFitness() {
  double sum_fitness = 0, sum_energy = 0;
  for (int i = 0; i < Pop_size; ++i) {
    energy[i] = CalcEnergy(populations[i]);
    sum_energy += energy[i];
  }
  for (int i = 0; i < Pop_size; ++i) {
    sum_fitness += sum_energy / energy[i];
    fitness[i] = sum_fitness;
  }
  for (int i = 0; i < Pop_size; ++i) {
    fitness[i] /= sum_fitness;
  }
}

// 锦标赛选择法
void Select() {
  static vector<Colony> tmp(Pop_size);
  tmp.clear();
  for (int i = 0, x, y; i < Pop_size; ++i) {
    x = rnd_Pop(random);
    y = rnd_Pop(random);
    if (energy[x] > energy[y]) swap(x, y);
    tmp.emplace_back(populations[x]);
  }
  swap(tmp, populations);
}

void Cross() {
  Colony tmp[2];
  for (int i = 1; i < Pop_size; ++i) {
    double p = rnd() % (int)1e9 / 1e9;
    if (p > Pcross) continue;
    int s = rnd() % (Pop_size - cross_size);
    tmp[0] = populations[i - 1];
    tmp[1] = populations[i];
    copy(populations[i - 1].begin() + s, populations[i - 1].begin() + s + cross_size,  tmp[1].begin() + s);
    copy(populations[i].begin() + s, populations[i].begin() + s + cross_size,  tmp[0].begin() + s);
    swap(tmp[0], populations[i - 1]);
    swap(tmp[1], populations[i]);
  }
}

void Mutation() {
  for (int i = 0, x, y; i < Pop_size; ++i) {
    double p = rnd() % (int)1e9 / 1e9;
    if (p > Pmutation) continue;
    x = rnd_Pop(random);
    y = rnd_Pop(random);
    swap(populations[x], populations[y]);
  }
}

double CalcEnergy(const Colony &pop) {
  static vector<int> dp[2];
  dp[0].resize(pop.size());
  dp[1].resize(pop.size());
  dp[0][0] = dp[0][1] = 0;
  for (unsigned i = 1; i < pop.size(); ++i) {
    dp[0][i] = dp[1][i] = INF;
    for (int ui : {0, 1})
    for (int vi : {0, 1}) {
      Min(dp[vi][i], dp[ui][i - 1] + dist[ui][vi][pop[i - 1]][pop[i]]);
    }
  }
  return min(dp[0].back(), dp[1].back());
}

} // namespace GA

struct Timer {
  clock_t t;
  void start() {
    cerr << "Start timer\n";
    t = clock();
  }
  void stop() {
    cerr << "Elapsed Time: " << (clock() - t) / CLOCKS_PER_SEC  << " s\n";
  }
} timer;

signed main() {
  Input();
  cerr << "the size of edges is : " << edges.size() << '\n';
  CalcDist();

  GA::Solve();

  system("pause");
  return 0;
}