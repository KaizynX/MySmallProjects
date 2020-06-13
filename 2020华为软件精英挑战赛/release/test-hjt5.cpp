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
struct DISC{ //离散化
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
int in_deg[N],ot_deg[N],deg[N];
queue<int> q;
int dis_b[N],dcnt_b[N],dcnt;
int dis_a[N],dcnt_a[N];
bool del[N],vis[N],inq[N];
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
		for(auto &i:arr)i=Disc[i];
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
		++ot_deg[eset[i]];
		++in_deg[eset[i^1]];
	}
	/******* topo ******/
	static queue<int> q;
	for(int i=0;i<n;++i){
		if(in_deg[i]==0 || ot_deg[i]==0){
			q.push(i);
			inq[i]=1;
		}
	}
	while(q.size()){
		int x=q.front();q.pop();
		for(const int &p:a[x])if(!del[p]){
			if(--in_deg[p]==0 && !inq[p]){
				q.push(p);
				inq[p]=1;
			}
		}
		for(const int &p:b[x])if(!del[p]){
			if(--ot_deg[p]==0 && !inq[p]){
				q.push(p);
				inq[p]=1;
			}
		}
		del[x]=1;
		in_deg[x]=ot_deg[x]=0;
		inq[x]=0;
	}
	/******* topo ******/
	for(int i=0;i<n;i++)
	if(!del[i]){
		order.insert(pii(in_deg[i]+ot_deg[i],i));
	}
	while(order.size()){
		auto it=--order.end();
		s=it->second; order.erase(it);
		dcnt++;
		bfs_a3();
		bfs_b7();
		rec.assign(1,s);
		dfs(s);
		
		q.push(s);
		inq[s]=1;
		while(q.size()){
			int x=q.front();q.pop();
			for(const int &p:a[x])if(!del[p]){
				if(--in_deg[p]==0 && !inq[p]){
					q.push(p);
					inq[p]=1;
				}
			}
			for(const int &p:b[x])if(!del[p]){
				if(--ot_deg[p]==0 && !inq[p]){
					q.push(p);
					inq[p]=1;
				}
			}
			auto it = order.lower_bound(pii(0,x));
			if (it!=order.end())order.erase(it);
			del[x]=1;
			in_deg[x]=ot_deg[x]=0;
			inq[x]=0;
		}
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
		printf("%u%c",arr[j],",\n"[j==arr.size()-1]);
}


signed main(){
	vector<int> eset=input();
	int n=Disc.init(eset);
	vector<vector<int>> ans=Solve::solve(eset,n);
	output(ans);
	
	timer("");
	return 0;
}
