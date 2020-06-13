#include <bits/stdc++.h>
using namespace std;
#define int unsigned

struct CLOCK{ //输出总用时
	double st;
	CLOCK(){st=clock();}
	~CLOCK(){cerr<<endl<<(clock()-st)/1000<<"s"<<endl;}
}Clock;

struct DISC{ //离散化
	vector<int> b;
	int init(vector<int> &a){
		b=a;
		sort(b.begin(),b.end());
		b.erase(unique(b.begin(),b.end()),b.end());
		for(auto &i:a)
			i=lower_bound(b.begin(),b.end(),i)-b.begin();
		return b.size();
	}
	const int &operator[](int n)const{
		return b[n];
	}
}Disc;

class Solve{
private:
	static const int N=560010;
	typedef pair<int,int> pii;
	vector<int> a[N],b[N];
	int s;
	set<pii> order;
	int deg[N];
	queue<int> q;
	int dis[N],disdcnt[N],dcnt;
	bool del[N],vis[N];
	vector<int> rec;
	vector<vector<int>> ans;
	void dfs(int x){
		vis[x]=1;
		for(const auto &p:a[x])
		if(p==s){
			if(rec.size()>=3)ans.push_back(rec);
		}
		else if(!vis[p] && disdcnt[p]==dcnt){
			rec.push_back(p);
			if(rec.size()+dis[p]<=8)dfs(p);
			rec.pop_back();
		}
		vis[x]=0;
	}
	void bfs(){
		dcnt++;
		q.push(s);
		disdcnt[s]=dcnt; dis[s]=0;
		while(!q.empty()){
			int x=q.front(); q.pop();
			for(const auto &p:b[x])
			if(disdcnt[p]!=dcnt && !del[p]){
				disdcnt[p]=dcnt;
				dis[p]=dis[x]+1;
				if(dis[p]<7)q.push(p);
			}
		}
	}
public:
	vector<vector<int>> solve(const vector<int> &eset,int n){
		for(int i=0;i<eset.size();i+=2){
			a[eset[i]].push_back(eset[i^1]);
			b[eset[i^1]].push_back(eset[i]);
			deg[eset[i]]++;
			deg[eset[i^1]]++;
		}
		for(int i=0;i<n;i++){
			order.insert(pii(deg[i],i));
		}
		for(int i=0;i<n;i++){
			s=(--order.end())->second; order.erase(--order.end());
			bfs();
			rec.assign(1,s);
			dfs(s);
			del[s]=1;
			for(const auto &p:a[s])
			if(!del[p]){
				order.erase(order.lower_bound(pii(deg[p],p)));
				deg[p]--;
				order.insert(pii(deg[p],p));
			}
			for(const auto &p:b[s])
			if(!del[p]){
				order.erase(order.lower_bound(pii(deg[p],p)));
				deg[p]--;
				order.insert(pii(deg[p],p));
			}
		}
		return ans;
	}
}solve;

vector<int> input(){ //读入eset
	vector<int> eset;
	freopen("test_data.txt","r",stdin);
	int x,y,z;
	while(~scanf("%u,%u,%u",&x,&y,&z))
		eset.push_back(x),eset.push_back(y);
	return eset;
}

void output(const vector<vector<int>> &ans){ //输出ans
	freopen("output.txt","w",stdout);
	printf("%u\n",(int)ans.size());
	for(const auto &arr:ans)
	for(int j=0;j<arr.size();j++)
		printf("%u%c",Disc[arr[j]],",\n"[j==arr.size()-1]);
}

void adjust(vector<vector<int>> &ans){ //把环里的最小值转到最前并排序
	for(auto &arr:ans){
		rotate(arr.begin(),min_element(arr.begin(),arr.end()),arr.end());
	}
	sort(ans.begin(),ans.end(),[](const vector<int> &a,const vector<int> &b)->bool{
		if(a.size()!=b.size())return a.size()<b.size();
		return a<b;
	});
}

signed main(){
	vector<int> eset=input();
	int n=Disc.init(eset);
	vector<vector<int>> ans=solve.solve(eset,n);
	adjust(ans);
	output(ans);
	return 0;
}