#include <bits/stdc++.h>
using namespace std;
#define int unsigned

struct Timer{ //计时器
	double start,pre;
	Timer(){start=pre=clock();}
	void operator()(const string &s){
		double now=clock();
		cerr<<"["<<s<<"] ";
		cerr<<"Interval: "<<(now-pre)/1000<<"s | ";
		cerr<<"Total:"<<(now-start)/1000<<"s"<<endl;
		pre=now;
	}
}timer;

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

namespace Solve{
const int N=560010;
typedef pair<int,int> pii;
vector<int> a[N],b[N];
int s;
set<pii> order;
int deg[N];
queue<int> q;
int dis_b[N],dcnt_b[N],dcnt;
int dis_a[N],dcnt_a[N];
bool del[N],vis[N];
vector<int> rec;
vector<vector<int>> ans;
void dfs(int x){
	vis[x]=1;
	for(const auto &p:a[x])
	if(p==s){
		if(rec.size()>=3)ans.push_back(rec);
	}
	else if(!vis[p] && dcnt_b[p]==dcnt){
		rec.push_back(p);
		if(rec.size()+dis_b[p]<=8)dfs(p);
		rec.pop_back();
	}
	vis[x]=0;
}
void bfs_a3(){
	q.push(s);
	dcnt_a[s]=dcnt; dis_a[s]=0;
	while(!q.empty()){
		int x=q.front(); q.pop();
		for(const auto &p:a[x])
		if(dcnt_a[p]!=dcnt && !del[p]){
			dcnt_a[p]=dcnt;
			dis_a[p]=dis_a[x]+1;
			if(dis_a[p]<3)q.push(p);
		}
	}
}
void bfs_b7(){
	q.push(s);
	dcnt_b[s]=dcnt; dis_b[s]=0;
	while(!q.empty()){
		int x=q.front(); q.pop();
		for(const auto &p:b[x])
		if(dcnt_b[p]!=dcnt && !del[p]){
			dcnt_b[p]=dcnt;
			dis_b[p]=dis_b[x]+1;
			if(/*dis_b[p]<7*/ dis_b[p]<4 || (dcnt_a[p]==dcnt && dis_b[p]+dis_a[p]<=7))q.push(p);
		}
	}
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
		auto it=--order.end();
		s=it->second; order.erase(it);
		dcnt++;
		bfs_a3();
		bfs_b7();
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
	adjust(ans);
	return ans;
}
}

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


signed main(){
	vector<int> eset=input();
	int n=Disc.init(eset);
	vector<vector<int>> ans=Solve::solve(eset,n);
	output(ans);
	
	timer("");
	return 0;
}
