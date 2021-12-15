/*
 * @Author: Kaizyn
 * @Date: 2021-12-08 14:42:29
 * @LastEditTime: 2021-12-15 17:19:27
 */
#include <bits/stdc++.h>

// #define DEBUG

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
const double eps = 1e-2; // 精度,若修改注意int范围

struct Node {
  int x, y;
  Node() {}
  Node(int _x, int _y) : x(_x), y(_y) {}
  bool operator < (const Node &rhs) const {
    return make_pair(x, y) < make_pair(rhs.x, rhs.y);
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

struct Outputer;

struct Edge {
  int u, v;
  vector<Node> paths;
  Edge() {}
  Edge(int _u, int _v) : u(_u), v(_v) {}
  void reverse() {
    swap(u, v);
    std::reverse(paths.begin(), paths.end());
  }
  // friend void print(Edge &edge, int start_point) ;
  friend struct Outputer;
};

vector<Node> points;
vector<Edge> edges;
vector<vector<int>> edge_ids;

// 把点映射成整数
int get_id(Node &point) {
  static map<Node, int> point_id_map;
  if (point_id_map.count(point)) return point_id_map[point];
  points.emplace_back(point); return point_id_map[point] = points.size() - 1;
}

// 计算两点间距离
int calc_dis(Node &a, Node &b) {
  return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

// 加入一条边
void add_edge(const Edge &edge) {
  int u = edge.u, v = edge.v;
  #ifdef DEBUG
  cout << "add_edge:" << u << ' ' << v << '\n';
  #endif
  if (max(u, v) >= (int)edge_ids.size()) edge_ids.resize(max(u, v) + 1);
  edge_ids[u].emplace_back(edges.size());
  edge_ids[v].emplace_back(edges.size());
  edges.emplace_back(edge);
}

void input() {
  string filename = "test.txt";
  // cout << "输入文件名:\n"; cin >> filename;
  ifstream file(filename, ios::in);
  int move_tag;
  Node point;
  Edge edge;
  while (file >> point  >> move_tag) {
    if (point.x == 0 && point.y == 0 && move_tag == 0) break;
    assert(move_tag == 0); // 若出错说明数据格式不是预期的
    edge.paths.clear();
    edge.u = get_id(point); // 端点1
    while (file >> point >> move_tag && move_tag <= 0) {
      edge.paths.emplace_back(point);
    }
    edge.paths.emplace_back(point);
    edge.v = get_id(point); // 端点2
    assert(edge.paths.size() >= 2u); // 一条线段必然由两个以上点构成
    add_edge(edge);
  }
  file.close();
  #ifdef DEBUG
  orzeach(points);
  #endif
}

struct Outputer {
  string filename = "out.txt";
  ofstream file;
  Outputer() {
    file.open(filename, ios::out);
  }
  ~Outputer() {
    file << "0 0 0\n";
    file.close();
  }
  void operator ()(const Node &point, int move_tag = 0) {
    file << point << ' ' << move_tag << '\n';
  }
  void operator ()(Edge &edge, int start_point) {
    if (edge.paths.empty()) {
      file << points[edge.u ^ edge.v ^ start_point] << " 0\n";
    } else {
      if (start_point != edge.u) edge.reverse();
      assert(start_point == edge.u); // 若出错说明这个起点和这条边不吻合
      for (unsigned i = 0; i < edge.paths.size(); ++i) {
        file << edge.paths[i];
        if (i == 0) file << " -33\n";
        else if (i+1 == edge.paths.size()) file << " 33\n";
        else file << " 0\n";
      }
    }
  }
} output;

// 一般图最小权完美匹配 随机算法 拷贝于网络
namespace Work {
  const int INF=2e2/eps;
  vector<vector<int>> w;
  vector<int> match, path, p, d, v;
  int n, m, k, len;
  bool dfs(int i) {
    path[len++] = i;
    if (v[i]) return true;
    v[i] = true;
    for (int j = 0; j < k; ++j) {
      if (i != j && match[i] != j && !v[j]) {
        int kok = match[j];
        if (d[kok] < d[i] + w[i][j] - w[j][kok]) {
          d[kok] = d[i] + w[i][j] - w[j][kok];
          if (dfs(kok)) return true;
        }
      }
    }
    --len;
    v[i] = false;
    return false;
  }

  double solve() {
    mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());
    k = points.size();
    assert(k % 2 == 0); // 无向图显然满足条件
    w.resize(k);
    match = path = p = d = v = vector<int>(k, 0);
    for (int i = 0; i < k; ++i) {
      p[i] = i;
      match[i] = i ^ 1;
      w[i].resize(k);
      for (int j = 0; j < k; ++j) {
        w[i][j] = INF - calc_dis(points[i], points[j]);
      }
    }
    for (auto edge : edges) {
      w[edge.u][edge.v] = w[edge.v][edge.u] = 0;
    }
    int cnt = 0;
    while (true) {
      len = 0;
      bool flag = false;
      d = v = vector<int>(k, 0);
      for (int i = 0; i < k; ++i) {
        if (dfs(p[i])) {
          flag = true;
          int t = match[path[len - 1]], j = len - 2;
          while (path[j] != path[len - 1]) {
            match[t] = path[j];
            swap(t, match[path[j]]);
            --j;
          }
          match[t] = path[j];
          match[path[j]] = t;
          break;
        }
      }
      if (!flag) {
        if (++cnt >= 3) break;
        shuffle(p.begin(), p.end(), rnd);
      }
    }
    int tot_dist = 0;
    for (int i = 0; i < k; ++i) {
      if (match[i] == i) return -1;
      if (match[i] < i) continue;
      tot_dist += INF - w[i][match[i]];
      add_edge(Edge(i, match[i]));
      #ifdef DEBUG
      cout << i << " mathch with " << match[i] << '\n';
      #endif
    }
    return tot_dist;
  }
}

// 求欧拉路
namespace Hierholzer{
int point_num;
vector<int> edge_vis;
vector<vector<int>::iterator> edge_beg;

void dfs(int u) {
  for (auto &it = edge_beg[u]; it != edge_ids[u].end(); ) {
    if (edge_vis[*it]) {
      ++it;
    } else {
      edge_vis[*it] = 1;
      int v = edges[*it].u ^ edges[*it].v ^ u;
      output(edges[*it], u);
      ++it;
      dfs(v);
    }
  }
}

void solve() {
  point_num = points.size();
  edge_vis = vector<int>(edges.size(), 0);
  edge_beg.resize(point_num);
  for (int i = 0; i < point_num; ++i) {
    edge_beg[i] = edge_ids[i].begin();
  }
  int count = 0;
  for (int i = 0; i < point_num; ++i) {
    if (edge_beg[i] == edge_ids[i].end()) continue;
    output(points[i]);
    dfs(i);
    ++count;
  }
  assert(count == 1); // 如果出错说明没有形成连通图
}

} // namespace Hierholzer

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

// TODO: 删掉最长的空程形成半欧拉图
signed main() {
  timer.start();
  input();
  cerr << "the size of edges is : " << edges.size() << '\n';
  timer.stop();

  timer.start();
  long long tot_dist = Work::solve();
  assert(~tot_dist); // 如果出错说明匹配失败
  cerr << "total_idle_distance:" << tot_dist*eps << '\n';
  timer.stop();

  timer.start();
  Hierholzer::solve();
  timer.stop();

  system("pause");
  return 0;
}