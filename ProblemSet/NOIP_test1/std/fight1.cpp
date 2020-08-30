#include <bits/stdc++.h>

using namespace std;

const int N = 1e5+7;
const int INF = 0x3f3f3f3f;

int n, m, L, R;
int a[N], dp[N];
long long presum[N];
deque<int> q[N];

struct SegmentTree {
  int n;
  int tr[N<<2];
  void build(int n) {
    this->n = n;
    memset(tr, 0x9f, sizeof tr);
  }
  void push_up(int i) {
    tr[i] = max(tr[i<<1], tr[i<<1|1]);
  }
  void update(int x, int k) {
    update(x, k, 1, n, 1);
  }
  void update(int x, int k, int l, int r, int i) {
    if (l == r) {
      tr[i] = k;
      return;
    }
    int mid = (l+r)>>1;
    if (x <= mid) update(x, k, l, mid, i<<1);
    else update(x, k, mid+1, r, i<<1|1);
    push_up(i);
  }
  int query(int x, int y) {
    return query(x, y, 1, n, 1);
  }
  int query(int x, int y, int l, int r, int i) {
    if (x <= l && y >= r) return tr[i];
    int mid = (l+r)>>1;
    if (y <= mid) return query(x, y, l, mid, i<<1);
    if (x >  mid) return query(x, y, mid+1, r, i<<1|1);
    return max(query(x, y, l, mid, i<<1), query(x, y, mid+1, r, i<<1|1));
  }
} seg;

void my_add(int x, int k) {
  while (q[x].size() && dp[q[x].back()] <= dp[k]) q[x].pop_back();
  if (!q[x].size()) seg.update(x, dp[k]);
  q[x].push_back(k);
}

void my_del(int x, int k) {
  if (q[x].front() != k) return;
  q[x].pop_front();
  seg.update(x, q[x].size() ? dp[q[x].front()] : -INF);
}

void discrete() {
  vector<long long> dis;
  for (int i = 0; i <= n; ++i) dis.push_back(presum[i]);
  sort(dis.begin(), dis.end());
  dis.erase(unique(dis.begin(), dis.end()), dis.end());
  m = dis.size();
  for (int i = 0; i <= n; ++i) {
    presum[i] = lower_bound(dis.begin(), dis.end(), presum[i])-dis.begin()+1;
  }
}

signed main() {
  cin >> n >> L >> R;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    presum[i] = presum[i-1]+a[i];
  }
  discrete(); // 离散化
  // 小辣
  seg.build(m);
  for (int i = 1; i <= n; ++i) {
    if (i-L >= 0) my_add(presum[i-L], i-L);
    if (i-R-1 >= 0) my_del(presum[i-R-1], i-R-1);
    dp[i] = seg.query(presum[i], presum[i]);
    if (presum[i] > 1) dp[i] = max(dp[i], seg.query(1, presum[i]-1)+1);
    if (presum[i] < m) dp[i] = max(dp[i], seg.query(presum[i]+1, m)-1);
  }
  cout << dp[n] << endl;
  // 小汤
  for (int i = 1; i <= m; ++i) q[i].clear();
  seg.build(m);
  for (int i = 1; i <= n; ++i) {
    if (i-L >= 0) my_add(presum[i-L], i-L);
    if (i-R-1 >= 0) my_del(presum[i-R-1], i-R-1);
    dp[i] = seg.query(presum[i], presum[i]);
    if (presum[i] > 1) dp[i] = max(dp[i], seg.query(1, presum[i]-1)-1);
    if (presum[i] < m) dp[i] = max(dp[i], seg.query(presum[i]+1, m)+1);
  }
  cout << dp[n] << endl;
  return 0;
}