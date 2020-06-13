#include <bits/stdc++.h>
using namespace std;
#define int unsigned
#define push_back emplace_back

const int THREAD_COUNT = 1;

struct Timer{
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

#define sortdisc
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
set<pii> order;
int in_deg[N],ot_deg[N],deg[N];
bool del[N],inq[N];
vector<vector<int>> ans;

int multi_dis_b[THREAD_COUNT][N],multi_dcnt_b[THREAD_COUNT][N];
int multi_dis_a[THREAD_COUNT][N],multi_dcnt_a[THREAD_COUNT][N];
bool multi_vis[THREAD_COUNT][N];
vector<int> multi_rec[THREAD_COUNT];
queue<int> multi_q[THREAD_COUNT];

void dfs(const int &id, const int &s, const int &x){
	bool *vis=multi_vis[id];
	int *dcnt_b=multi_dcnt_b[id],*dis_b=multi_dis_b[id];
	vector<int> &rec=multi_rec[id];

	vis[x]=1;
	for(const auto &p:a[x])
	if(p==s){ // 这里ans可能要加个锁
		if(rec.size()>=3)ans.push_back(rec);
	}
	else if(!vis[p] && dcnt_b[p]==s){
		rec.push_back(p);
		if(rec.size()+dis_b[p]<=8)dfs(id, s, p);
		rec.pop_back();
	}
	vis[x]=0;
}
void bfs_a3(const int &id, const int &s){
	int *dcnt_a=multi_dcnt_a[id],*dis_a=multi_dis_a[id];

	queue<int> q;
	q.push(s);
	dcnt_a[s]=s; dis_a[s]=0;
	while(!q.empty()){
		int x=q.front(); q.pop();
		for(const auto &p:a[x])
		if(dcnt_a[p]!=s && !del[p]){
			dcnt_a[p]=s;
			dis_a[p]=dis_a[x]+1;
			if(dis_a[p]<3)q.push(p);
		}
	}
}
void bfs_b7(const int &id, const int &s){
	int *dcnt_a=multi_dcnt_a[id],*dis_a=multi_dis_a[id],
		*dcnt_b=multi_dcnt_b[id],*dis_b=multi_dis_b[id];

	queue<int> q;
	q.push(s);
	dcnt_b[s]=s; dis_b[s]=0;
	while(!q.empty()){
		int x=q.front(); q.pop();
		for(const auto &p:b[x])
		if(dcnt_b[p]!=s && !del[p]){
			dcnt_b[p]=s;
			dis_b[p]=dis_b[x]+1;
			if(/*dis_b[p]<7*/ dis_b[p]<4 || (dcnt_a[p]==s && dis_b[p]+dis_a[p]<=7))q.push(p);
		}
	}
}
void adjust(vector<vector<int>> &ans){ //把环里的最小值转到最前并排序
	for(auto &arr:ans){
#ifndef sortdisc
		for(auto &i:arr)i=Disc[i];
#endif
		rotate(arr.begin(),min_element(arr.begin(),arr.end()),arr.end());
	}
	sort(ans.begin(),ans.end(),[](const vector<int> &a,const vector<int> &b)->bool{
		if(a.size()!=b.size())return a.size()<b.size();
		return a<b;
	});
	ans.erase(unique(ans.begin(), ans.end()),ans.end());
}
inline void* multi_thread_solve(void *arg){
	int id=(*(pii*)arg).first,s=(*(pii*)arg).second;
	bfs_a3(id, s);
	bfs_b7(id, s);
	multi_rec[id].assign(1,s);
	dfs(id, s, s);
}
vector<vector<int>> solve(const vector<int> &eset,int n){
	/* new! */
	ans.reserve(3000000);
	memset(multi_dcnt_a, -1, sizeof multi_dcnt_a);
	memset(multi_dcnt_b, -1, sizeof multi_dcnt_b);

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
		deg[i]=in_deg[i]+ot_deg[i];
		order.insert(pii(in_deg[i]+ot_deg[i],i));
	}
	//多多多多线程
	pthread_t tids[THREAD_COUNT];
	while(order.size()){
		/*
		for(int i=0;i<THREAD_COUNT && order.size();++i){
			auto it=--order.end();
			int s=it->second; order.erase(it);
			pii arg=pii(i,s);
			int rc = pthread_create(&tids[i], NULL, multi_thread_solve, (void *)&arg);
			if (rc) cerr << "Wrong!" << endl;
			q.push(s);
			inq[s]=1;
		}
		void *status;
		for(int i=0;i<THREAD_COUNT;++i){
			int rc = pthread_join(tids[i], &status);
			if(rc) cerr << "Wrong!" << endl;
		}
		*/
		for(int i=0;i<THREAD_COUNT && order.size();++i){
			auto it=--order.end();
			int s=it->second; order.erase(it);
			pii arg=pii(i,s);
			multi_thread_solve((void*)&arg);
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
			auto it = order.lower_bound(pii(deg[x],x));
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
	// freopen("test_data.txt","r",stdin);
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
#ifdef sortdisc
		printf("%u%c",Disc[arr[j]],",\n"[j==arr.size()-1]);
#else
		printf("%u%c",arr[j],",\n"[j==arr.size()-1]);
#endif
}


signed main(){
	vector<int> eset=input();
	int n=Disc.init(eset);
	vector<vector<int>> ans=Solve::solve(eset,n);
	output(ans);
	
	timer("");
	return 0;
}
