#include <bits/stdc++.h>
using namespace std;
#define repeat(i,a,b) for(int i=(a),_=(b);i<_;i++)
#define repeat_back(i,a,b) for(int i=(b)-1,_=(a);i>=_;i--)
#define mst(a,x) memset(a,x,sizeof(a))
#define fi first
#define se second
#define endl "\n"
mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());
int cansel_sync=(ios::sync_with_stdio(0),cin.tie(0),0);
const int N=100010; typedef long long ll; const int inf=~0u>>2; const ll INF=~0ull>>2; ll read(){ll x; if(scanf("%lld",&x)==-1)exit(0); return x;}
#define int ll
vector<int> a[N];
int co[N],dis[N],vis[N];
typedef pair<int,int> pii;
void Solve(){
	int n=read(),m=read(),k=read(),s=read(),t=read();
	repeat(i,1,n+1)co[i]=read();
	while(m--){
		int x=read(),y=read();
		a[x].push_back(y);
	}
	fill(dis,dis+n+1,INF); dis[s]=1;
	priority_queue<pii,vector<pii>,greater<pii>> q; q.push({dis[s],s});
	while(!q.empty()){
		int x=q.top().se; q.pop();
		if(vis[x])continue; vis[x]=1;
		for(auto p:a[x]){
			int cost=dis[x];
			if(co[p]!=co[x])cost=(cost+k-1)/k*k+1;
			else cost++;
			if(cost<dis[p]){
				dis[p]=cost;
				q.push({dis[p],p});
			}
		}
	}
	if(dis[t]!=INF)
		printf("%lld\n",(dis[t]+k-1)/k);
	else puts("-1");
}
signed main(){
	//freopen("data.txt","r",stdin);
	int T=1; //T=read();
	while(T--)Solve();
	return 0;
}