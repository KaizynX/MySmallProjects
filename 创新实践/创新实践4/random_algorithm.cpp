/*
 * @Author: Kaizyn
 * @Date: 2021-12-08 14:42:29
 * @LastEditTime: 2021-12-08 15:54:12
 */
/*
 * @Author: Kaizyn
 * @Date: 2021-12-08 13:13:30
 * @LastEditTime: 2021-12-08 14:40:22
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
const double eps = 1e-2; // 精度

struct Node {
  int x, y;
  Node (int _x, int _y) : x(_x), y(_y) {}
  bool operator < (const Node &rhs) const {
    return make_pair(x, y) < make_pair(rhs.x, rhs.y);
  }
};

struct Message {
  double x, y;
  int mv;
  Message (double _x, double _y, int _mv) : x(_x), y(_y), mv(_mv) {}
  friend istream& operator >> (istream &is, Message &mesg) {
    return is >> mesg.x >> mesg.y >> mesg.mv;
  }
  friend ostream& operator << (ostream &os, const Message &mesg) {
    return os << mesg.x << ' ' << mesg.y << ' ' << mesg.mv << '\n';
  }
};

/********************
 * 每个点由坐标(x, y)表示
 * 每条边由两个点编号(x, y)表示
 ********************/
vector<Node> points, edges;
map<Node, int> point_id_map;
int edge_tag;
vector<vector<int>> edge_ids;

// 把点映射成整数
int get_id(Node &point) {
  if (point_id_map.count(point)) return point_id_map[point];
  points.emplace_back(point); return point_id_map[point] = points.size() - 1;
}

// 计算两点间距离
double calc_dis(Node &a, Node &b) {
  return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

// 加入一条边
void add_edge(int u, int v) {
  if (max(u, v) >= (int)edge_ids.size()) edge_ids.resize(max(u, v) + 1);
  edge_ids[u].emplace_back(edges.size());
  edge_ids[v].emplace_back(edges.size());
  edges.emplace_back(Node(u, v));
}

void input_data() {
  string filename = "test.txt";
  // cout << "输入文件名:\n"; cin >> filename;
  ifstream file(filename, ios::in);
  double x, y;
  int z = 0, op, id;
  while (file >> x >> y >> op) {
    Node point(x / eps + .5, y / eps + .5);
    if (point.x == 0 && point.y == 0 && op == 0) break;
    if (op < 0) z = 1;
    if (op > 0) z = 0;
    if (z) {
      id = get_id(point);
      if (op >= 0) {
        assert(!points.empty());
        add_edge(get_id(points.back()), id);
      }
    }
  }
  edge_tag = edges.size();
  file.close();
}

// 求度数为奇数的点编号集
vector<int> get_single_points() {
  int point_num = point_id_map.size();
  vector<int> deg(point_num, 0), single_point_ids;
  for (Node &edge : edges) {
    ++deg[edge.x];
    ++deg[edge.y];
  }
  for (int i = 0; i < point_num; ++i) {
    if (deg[i] % 2 == 1) {
      single_point_ids.emplace_back(i);
    }
  }
  return single_point_ids;
}

// 一般图最小权完美匹配 随机算法
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

  double solve(vector<int> &point_ids) {
    mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());
    k = point_ids.size();
    assert(k % 2 == 0);
    w.resize(k);
    match = path = p = d = v = vector<int>(k, 0);
    for (int i = 0; i < k; ++i) {
      p[i] = i;
      match[i] = i ^ 1;
      w[i].resize(k);
      for (int j = 0; j < k; ++j) {
        w[i][j] = INF - calc_dis(points[point_ids[i]], points[point_ids[j]]);
      }
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
      add_edge(i, match[i]);
    }
    return tot_dist;
  }
}

// 求欧拉路
namespace Hierholzer{
int point_num;
vector<int> edge_vis;
vector<vector<int>::iterator> edge_beg;
vector<Message> mesgs;

void add_mesg(int v, int id) {
  if (id < edge_tag) {
    mesgs.emplace_back(Message(points[v].x / eps, points[v].y / eps, 0));
  } else {
    if (mesgs.size()) mesgs.back().mv = 33;
    mesgs.emplace_back(Message(points[v].x / eps, points[v].y / eps, 0));
    mesgs.emplace_back(Message(points[v].x / eps, points[v].y / eps, -33));
  }
}

void dfs(int u) {
  for (auto &it = edge_beg[u]; it != edge_ids[u].end(); ) {
    if (edge_vis[*it]) {
      ++it;
    } else {
      edge_vis[*it] = 1;
      int v = edges[*it].x ^ edges[*it].y ^ u;
      add_mesg(v, *it);
      ++it;
      dfs(v);
    }
  }
}

vector<Message> solve() {
  mesgs.clear();
  point_num = point_id_map.size();
  edge_vis = vector<int>(edges.size(), 0);
  for (int i = 0; i < point_num; ++i) {
    edge_beg[i] = edge_ids[i].begin();
  }
  mesgs.emplace_back(Message(points[0].x / eps, points[0].y / eps, 0));
  mesgs.emplace_back(Message(points[0].x / eps, points[0].y / eps, -33));
  dfs(0);
  return mesgs;
}

} // namespace Hierholzer

void output_data(vector<Message> &mesgs) {
  string filename = "out.txt";
  // cout << "输出文件名:\n"; cin >> filename;
  ofstream file(filename, ios::out);
  for (Message &mes : mesgs) file << mes;
  file << "0 0 0\n";
  file.close();
}

signed main() {
  input_data();
  vector<int> single_point_ids = get_single_points();
  // cout << single_point_ids.size() << '\n';
  long long tot_dist = Work::solve(single_point_ids);
  assert(~tot_dist);
  cout << "空程距离:" << tot_dist*eps << '\n';
  vector<Message> mesgs = Hierholzer::solve();
  cout << mesgs.size() << '\n';
  output_data(mesgs);
  system("pause");
  return 0;
}