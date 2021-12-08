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

/********************
 * 每个点由坐标(x, y)表示
 * 每条边由两个点编号(x, y)表示
 ********************/
vector<Node> points, edges;
map<Node, int> point_id_map;
vector<int> vis;
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
      if (op == 0) {
        assert(!points.empty());
        add_edge(get_id(points.back()), id);
      }
    }
  }
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
  const ll OO=2e2/eps;
  const int MAXN=4e2+7;
  ll w[MAXN][MAXN], g[MAXN][MAXN];
  int match[MAXN], path[MAXN], p[MAXN], len;
  ll d[MAXN];
  bool v[MAXN];
  int n, m, k;
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
    for (int i = 0; i < k; ++i) p[i] = i, match[i] = i ^ 1;
    for (int i = 0; i < k; ++i) {
      for (int j = 0; j < k; ++j) {
        w[i][j] = OO-calc_dis(points[point_ids[i]], points[point_ids[j]]);
      }
    }
    int cnt = 0;
    while (true) {
      len = 0;
      bool flag = false;
      memset(d, 0, sizeof(d));
      memset(v, 0, sizeof(v));
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
        shuffle(p, p + k, rnd);
      }
      // cout << "here goes one turn.\n";
    }
    // double ans = 0;
    ll ans = 0;
    for (int i = 0; i < k; ++i) {
      // double t = w[i][match[i]];
      ll t = w[i][match[i]];
      //    cout << t << endl;
      if (t == 0) {
        return -1;
      }
      ans += OO - t;
    }
    return ans/2;
  }
}

signed main() {
  input_data();
  vector<int> single_point_ids = get_single_points();
  // cout << single_point_ids.size() << '\n';
  long long tot_dist = Work::solve(single_point_ids);
  assert(~tot_dist);
  cout << "空程距离:" << tot_dist*eps << '\n';
  system("pause");
  return 0;
}