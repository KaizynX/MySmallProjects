#include <bits/stdc++.h>
using namespace std;
#define int unsigned

struct Timer{ //��ʱ��
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

struct DISC{ //��ɢ��
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
set<int> a[N],b[N];
int s;
set<pii> order;
int deg[N];
queue<int> q;
int dis_b[N],dcnt_b[N],dcnt;
int dis_a[N],dcnt_a[N];
bool vis[N];
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
		if(dcnt_a[p]!=dcnt){
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
		if(dcnt_b[p]!=dcnt){
			dcnt_b[p]=dcnt;
			dis_b[p]=dis_b[x]+1;
			if(/*dis_b[p]<7*/ dis_b[p]<4 || (dcnt_a[p]==dcnt && dis_b[p]+dis_a[p]<=7))q.push(p);
		}
	}
}
void adjust(vector<vector<int>> &ans){ //�ѻ������Сֵת����ǰ������
	for(auto &arr:ans){
		rotate(arr.begin(),min_element(arr.begin(),arr.end()),arr.end());
	}
	sort(ans.begin(),ans.end(),[](const vector<int> &a,const vector<int> &b)->bool{
		if(a.size()!=b.size())return a.size()<b.size();
		return a<b;
	});
}
vector<vector<int>>& solve(const vector<int> &eset,int n){
	for(int i=0;i<eset.size();i+=2){
		a[eset[i]].insert(eset[i^1]);
		b[eset[i^1]].insert(eset[i]);
	}
	/******* topo ******/
	static queue<int> q;
	for(int i=0;i<n;++i){
		if(b[i].empty())q.push(i);
	}
	while(q.size()){
		int x=q.front();q.pop();
		for(const int &p:a[x]){
			b[p].erase(x);
			if(b[p].empty())q.push(p);
		}
		a[x].clear();
	}
	for(int i=0;i<n;++i){
		if(a[i].empty())q.push(i);
	}
	while(q.size()){
		int x=q.front();q.pop();
		for(const int &p:b[x]){
			a[p].erase(x);
			if(a[p].empty())q.push(p);
		}
		b[x].clear();
	}
	/******* topo ******/
	for(int i=0;i<n;i++){
		deg[i]=a[i].size()+b[i].size();
		if(deg[i]>0)order.insert(pii(deg[i],i));
	}
	while(order.size()){
		auto it=--order.end();
		s=it->second; order.erase(it);
		dcnt++;
		bfs_a3();
		bfs_b7();
		rec.assign(1,s);
		dfs(s);
		
		for(const auto &p:a[s]){
			order.erase(order.lower_bound(pii(deg[p],p)));
			deg[p]--;
			b[p].erase(s);
			order.insert(pii(deg[p],p));
		}
		for(const auto &p:b[s]){
			order.erase(order.lower_bound(pii(deg[p],p)));
			deg[p]--;
			a[p].erase(s);
			order.insert(pii(deg[p],p));
		}
		a[s].clear();
		b[s].clear();
		deg[s]=0;
	}
	adjust(ans);
	return ans;
}
}

vector<int> input(){ //����eset
	vector<int> eset;
	freopen("test_data2.txt","r",stdin);
	int x,y,z;
	while(~scanf("%u,%u,%u",&x,&y,&z))
		eset.push_back(x),eset.push_back(y);
	return eset;
}

void output(const vector<vector<int>> &ans){ //���ans
	freopen("output.txt","w",stdout);
	printf("%u\n",(int)ans.size());
	for(const auto &arr:ans)
	for(int j=0;j<arr.size();j++)
		printf("%u%c",Disc[arr[j]],",\n"[j==arr.size()-1]);
}


signed main(){
	vector<int> eset=input();
	int n=Disc.init(eset);
	vector<vector<int>>& ans=Solve::solve(eset,n);
	output(ans);
	
	timer("");
	return 0;
}
