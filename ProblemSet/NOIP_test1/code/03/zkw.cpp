/*
 * @Author: Kaizyn
 * @Date: 2020-08-25 14:49:44
 * @LastEditTime: 2020-08-25 18:14:45
 */
#include <bits/stdc++.h>

using namespace std;

const int N = 1e5+7;
const int INF = 0x3f3f3f3f;

int n, m, L, R;
int a[N], dp[N], head[N];
long long presum[N];
vector<int> q[N];

struct seg{
  typedef int ll;
#define repeat(i,a,b) for(int i=(a),_=(b);i<_;i++)
#define repeat_back(i,a,b) for(int i=(b)-1,_=(a);i>=_;i--)
  #define U(a,b) max(a,b) //查询操作
  ll a0=-INF; //查询操作的零元
  int n; ll a[1024*1024*3]; //内存等于2^k且大于等于两倍inn
  void build(int inn){ //建树
    for(n=1;n<=inn;n<<=1);
    repeat(i,0,n)a[n+i]=-INF;
    repeat_back(i,1,n)up(i);
  }
  void up(int x){
    a[x]=U(a[x<<1],a[(x<<1)^1]);
  }
  void update(int x,ll k){ //位置x加上k
    a[x+=n]=k; //也可以赋值等操作
    while(x>>=1)up(x);
  }
  ll query(int l,int r){ //区间查询
    ll ans=a0;
    for(l+=n-1,r+=n+1;l^r^1;l>>=1,r>>=1){
        if(~l & 1)ans=U(ans,a[l^1]); //l^1其实是l+1
        if(r & 1)ans=U(ans,a[r^1]); //r^1其实是r-1
    }
    return ans;
  }
}seg;

void my_add(int x, int k) {
  while (head[x] < (int)q[x].size() && dp[q[x].back()] <= dp[k]) q[x].pop_back();
  q[x].push_back(k);
  if (q[x].size()-head[x] == 1) seg.update(x, dp[k]);
}

void my_del(int x, int k) {
  if (q[x][head[x]] != k) return;
  ++head[x];
  seg.update(x, head[x] < (int)q[x].size() ? dp[q[x][head[x]]] : -INF);
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
  freopen("1.in", "r", stdin);
  cin >> n >> L >> R;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    presum[i] = presum[i-1]+a[i];
  }
  discrete();
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
  for (int i = 1; i <= m; ++i) q[i].clear(), head[i] = 0;
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