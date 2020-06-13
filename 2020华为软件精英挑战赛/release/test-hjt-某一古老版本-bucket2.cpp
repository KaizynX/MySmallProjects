#pragma GCC optimize(3)
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
//#define sortdisc
#ifdef sortdisc
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
#else
struct DISC{ //离散化 /*new*/
	vector<int> b;
	unordered_map<int,int> m;
	int init(vector<int> &a){
		int cnt=0;
		b.assign(1,0);
		for(auto &i:a){
			int &x=m[i];
			if(x==0){x=++cnt; b.push_back(i);}
			i=x;
		}
		return b.size();
	}
	const int &operator[](int n)const{
		return b[n];
	}
}Disc;
#endif
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
			if(dis_b[p]<4 || (dcnt_a[p]==dcnt && dis_b[p]+dis_a[p]<=7))q.push(p);
		}
	}
}
void adjust(vector<vector<int>> &ans){
	for(auto &arr:ans){
		for(auto &i:arr)i=Disc[i];
		rotate(arr.begin(),min_element(arr.begin(),arr.end()),arr.end());
	}
	sort(ans.begin(),ans.end(),[](const vector<int> &a,const vector<int> &b)->bool{
		if(a.size()!=b.size())return a.size()<b.size();
		return a<b;
	});
}
namespace bkt{
	struct element{
		int pre,nxt;
	}bkt[N];
	int head[N],top;
	void add(int i,int deg){
		int &h=head[deg];
		bkt[i]={0,h};
		bkt[h].pre=i;
		h=i;
	}
	void erase(int i,int deg){
		bkt[bkt[i].pre].nxt=bkt[i].nxt;
		bkt[bkt[i].nxt].pre=bkt[i].pre;
		if(i==head[deg])head[deg]=bkt[i].nxt;
	}
}
vector<vector<int>> solve(const vector<int> &eset,int n){
	for(int i=0;i<eset.size();i+=2){
		a[eset[i]].push_back(eset[i^1]);
		b[eset[i^1]].push_back(eset[i]);
		deg[eset[i]]++;
		deg[eset[i^1]]++;
	}
	for(int i=0;i<n;i++)bkt::add(i,deg[i]);

	bkt::top=N-1;
	while(1){
		while(bkt::top!=0 && bkt::head[bkt::top]==0)bkt::top--;
		if(bkt::top==0)break;
		
		s=bkt::head[bkt::top];
		
		dcnt++;
		bfs_a3();
		bfs_b7();
		rec.assign(1,s);
		dfs(s);
		del[s]=1;
		
		bkt::erase(s,deg[s]);
		for(const auto &p:a[s])
		if(!del[p]){
			bkt::erase(p,deg[p]);
			deg[p]--;
			bkt::add(p,deg[p]);
		}
		for(const auto &p:b[s])
		if(!del[p]){
			bkt::erase(p,deg[p]);
			deg[p]--;
			bkt::add(p,deg[p]);
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
		printf("%u%c",arr[j],",\n"[j==arr.size()-1]); /*new*/
}

signed main(){
	vector<int> eset=input();
	timer("input");
	
	int n=Disc.init(eset);
	timer("disc");
	
	vector<vector<int>> ans=Solve::solve(eset,n);
	timer("calc");
	
	output(ans);
	timer("output");
	return 0;
}