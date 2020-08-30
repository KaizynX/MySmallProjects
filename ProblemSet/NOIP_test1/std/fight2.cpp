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
int a[N],t[N],dp[N],n,l,r;
struct seg{
	#define U(a,b) max(a,b)
	const ll a0=-inf;
	int n; ll a[1024*1024*4*2];
	void init(int inn){
		for(n=1;n<=inn;n<<=1);
		repeat(i,0,n)a[n+i]=a0;
		repeat_back(i,1,n)up(i);
	}
	void up(int x){
		a[x]=U(a[x<<1],a[(x<<1)^1]);
	}
	void update(int x,ll k){
		a[x+=n]=k;
		while(x>>=1)up(x);
	}
	ll query(int l,int r){
		ll ans=a0;
		for(l+=n-1,r+=n+1;l^r^1;l>>=1,r>>=1){
			if(~l & 1)ans=U(ans,a[l^1]);
			if(r & 1)ans=U(ans,a[r^1]);
		}
		return ans;
	}
}tr;
struct Disc{
	int b[N],pre[N],nxt[N];
	void init(int a[],int n){
		copy(a,a+n,b); sort(b,b+n);
		pre[0]=0;
		repeat(i,1,n){
			if(b[i]==b[i-1])pre[i]=pre[i-1];
			else pre[i]=i;
		}
		nxt[n-1]=n-1;
		repeat_back(i,0,n-1){
			if(b[i]==b[i+1])nxt[i]=nxt[i+1];
			else nxt[i]=i;
		}
		repeat(i,0,n){
			a[i]=lower_bound(b,b+n,a[i])-b;
			b[a[i]]--;
		}
	}
}d;
void work(){
	d.init(a,n+1); tr.init(N);
	repeat(i,1,n+1){
		if(i-l>=0)
			tr.update(a[i-l],dp[i-l]);
		if(i-r-1>=0)
			tr.update(a[i-r-1],-inf);
		dp[i]=max({tr.query(d.pre[a[i]],d.nxt[a[i]]),tr.query(0,d.pre[a[i]]-1)+1,tr.query(d.nxt[a[i]]+1,N)-1});
	}
}
void Solve(){
	n=read(),l=read(),r=read();
	repeat(i,1,n+1)t[i]=a[i]=a[i-1]+read();
	work();
	cout<<dp[n]<<endl;
	repeat(i,0,n+1)a[i]=-t[i];
	work();
	cout<<dp[n]<<endl;
}
signed main(){
	//freopen("data.txt","r",stdin);
	int T=1; //T=read();
	while(T--)Solve();
	return 0;
}