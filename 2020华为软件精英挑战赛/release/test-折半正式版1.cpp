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
/*
namespace allc{
	static char space[10000000],*sp=space;
	template<typename T>
	struct allc:allocator<T>{
		allc(){}
		template<typename U>
		allc(const allc<U> &a){}
		template<typename U>
		allc<T>& operator=(const allc<U> &a){return *this;}
		template<typename U>
		struct rebind{typedef allc<U> other;};
		T* allocate(size_t n){
			T *res=(T*)sp;
			sp+=n*sizeof(T);
			return res;
		}
		void deallocate(T* p,size_t n){}
	};
	void clear(){sp=space;}
}
*/
namespace Solve{
const int N=560010;
typedef pair<int,int> pii;
vector<int> a[N],b[N];
int s;
set<pii> order;
int deg[N];
bool del[N],vis[N];
vector<vector<int>> ans;
void adjust(vector<vector<int>> &ans){ //把环里的最小值转到最前并排序
	for(auto &arr:ans){
		rotate(arr.begin(),min_element(arr.begin(),arr.end()),arr.end());
	}
	sort(ans.begin(),ans.end(),[](const vector<int> &a,const vector<int> &b)->bool{
		if(a.size()!=b.size())return a.size()<b.size();
		return a<b;
	});
	//ans.erase(unique(ans.begin(),ans.end()),ans.end());
}
vector<int> rec;
vector<vector<int>> path_rec[N];
vector<int> path_rec_set;
void dfs_rec_b3(int x){
	if(path_rec[x].empty()){
		path_rec_set.push_back(x);
	}
	path_rec[x].push_back(rec);
	
	if(rec.size()>=3)return;
	vis[x]=1;
	for(const auto &p:b[x])
	if(!vis[p]){
		rec.push_back(p);
		dfs_rec_b3(p);
		rec.pop_back();
	}
	vis[x]=0;
}
void ans_append(const vector<int> &path){
	for(int i=0;i<path.size();i++)
		if(vis[path[i]])return;
	ans.push_back(rec);
	for(signed i=path.size()-1;i>=0;i--){
		ans.back().push_back(path[i]);
	}
}
void dfs_a3(int x){
	if(rec.size()==4){
		for(const auto &p:a[x])
		if(p==s){
			ans.push_back(rec);
		}
		else if(!path_rec[p].empty()){
			for(const auto &path:path_rec[p]){
				ans_append(path);
			}
		}
	}
	else{
		vis[x]=1;
		for(const auto &p:a[x])
		if(p==s){
			if(rec.size()==3)ans.push_back(rec);
		}
		else if(!vis[p]){
			rec.push_back(p);
			dfs_a3(p);
			rec.pop_back();
		}
		vis[x]=0;
	}
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
		rec.clear();
		dfs_rec_b3(s);
		rec.assign(1,s);
		dfs_a3(s);
		for(auto i:path_rec_set)path_rec[i].clear();
		path_rec_set.clear();
		del[s]=1; vis[s]=1;
		
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
	timer("input");
	int n=Disc.init(eset);
	timer("disc");
	vector<vector<int>> ans=Solve::solve(eset,n);
	timer("solve");
	output(ans);
	timer("output");
	return 0;
}
