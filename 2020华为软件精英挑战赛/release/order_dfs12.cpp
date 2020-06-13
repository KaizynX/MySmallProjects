#include <bits/stdc++.h>   
#include <pthread.h>
using namespace std;
#define int unsigned
#define push_back emplace_back

const int N = 280001;
const int M = 560001;
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

struct Info
{
	int start;
	int end;
};

struct Queue{
	int a[1<<16];
	unsigned short h,t;
	Queue(){h=t=0;}
	void push(int x){a[t++]=x;}
	void pop(){h++;}
	bool empty(){return h==t;}
	int front(){return a[h];}
	int size(){return t-h;}
	int pop_getfront(){return a[h++];}
};

namespace DISC {
#define u32 unsigned
#define re register
	u32 a[M], b[M], *c;
	u32 len[N];
	char str[N][11];
	int cnt0[1 << 8], cnt8[1 << 8], cnt16[1 << 8], cnt24[1 << 8];
	int n, m, part;

	inline void sort() {
		for (int re i = 1; i < 256; ++i) {
			cnt0[i] += cnt0[i - 1];
			cnt8[i] += cnt8[i - 1];
			cnt16[i] += cnt16[i - 1];
			cnt24[i] += cnt24[i - 1];
		}

		re int rep = n >> 3, tim = rep;
		re u32 *now = a + n - 1;
		while (tim--) {
			b[--cnt0[now[0] & 255]] = now[0];
			b[--cnt0[now[-1] & 255]] = now[-1];
			b[--cnt0[now[-2] & 255]] = now[-2];
			b[--cnt0[now[-3] & 255]] = now[-3];
			b[--cnt0[now[-4] & 255]] = now[-4];
			b[--cnt0[now[-5] & 255]] = now[-5];
			b[--cnt0[now[-6] & 255]] = now[-6];
			b[--cnt0[now[-7] & 255]] = now[-7]; now -= 8;
		}
		switch (n & 7) {
		case 7: {b[--cnt0[*now & 255]] = *now; --now; }
		case 6: {b[--cnt0[*now & 255]] = *now; --now; }
		case 5: {b[--cnt0[*now & 255]] = *now; --now; }
		case 4: {b[--cnt0[*now & 255]] = *now; --now; }
		case 3: {b[--cnt0[*now & 255]] = *now; --now; }
		case 2: {b[--cnt0[*now & 255]] = *now; --now; }
		case 1: {b[--cnt0[*now & 255]] = *now; --now; }
		}
		tim = rep;
		now = b + n - 1;
		while (tim--) {
			a[--cnt8[now[0] >> 8 & 255]] = now[0];
			a[--cnt8[now[-1] >> 8 & 255]] = now[-1];
			a[--cnt8[now[-2] >> 8 & 255]] = now[-2];
			a[--cnt8[now[-3] >> 8 & 255]] = now[-3];
			a[--cnt8[now[-4] >> 8 & 255]] = now[-4];
			a[--cnt8[now[-5] >> 8 & 255]] = now[-5];
			a[--cnt8[now[-6] >> 8 & 255]] = now[-6];
			a[--cnt8[now[-7] >> 8 & 255]] = now[-7]; now -= 8;
		}
		switch (n & 7) {
		case 7: {a[--cnt8[*now >> 8 & 255]] = *now; --now; }
		case 6: {a[--cnt8[*now >> 8 & 255]] = *now; --now; }
		case 5: {a[--cnt8[*now >> 8 & 255]] = *now; --now; }
		case 4: {a[--cnt8[*now >> 8 & 255]] = *now; --now; }
		case 3: {a[--cnt8[*now >> 8 & 255]] = *now; --now; }
		case 2: {a[--cnt8[*now >> 8 & 255]] = *now; --now; }
		case 1: {a[--cnt8[*now >> 8 & 255]] = *now; --now; }
		}
		tim = rep;
		now = a + n - 1;
		while (tim--) {
			b[--cnt16[now[0] >> 16 & 255]] = now[0];
			b[--cnt16[now[-1] >> 16 & 255]] = now[-1];
			b[--cnt16[now[-2] >> 16 & 255]] = now[-2];
			b[--cnt16[now[-3] >> 16 & 255]] = now[-3];
			b[--cnt16[now[-4] >> 16 & 255]] = now[-4];
			b[--cnt16[now[-5] >> 16 & 255]] = now[-5];
			b[--cnt16[now[-6] >> 16 & 255]] = now[-6];
			b[--cnt16[now[-7] >> 16 & 255]] = now[-7]; now -= 8;
		}
		switch (n & 7) {
		case 7: {b[--cnt16[*now >> 16 & 255]] = *now; --now; }
		case 6: {b[--cnt16[*now >> 16 & 255]] = *now; --now; }
		case 5: {b[--cnt16[*now >> 16 & 255]] = *now; --now; }
		case 4: {b[--cnt16[*now >> 16 & 255]] = *now; --now; }
		case 3: {b[--cnt16[*now >> 16 & 255]] = *now; --now; }
		case 2: {b[--cnt16[*now >> 16 & 255]] = *now; --now; }
		case 1: {b[--cnt16[*now >> 16 & 255]] = *now; --now; }
		}
		tim = rep;
		now = b + n - 1;
		while (tim--) {
			a[--cnt24[now[0] >> 24]] = now[0];
			a[--cnt24[now[-1] >> 24]] = now[-1];
			a[--cnt24[now[-2] >> 24]] = now[-2];
			a[--cnt24[now[-3] >> 24]] = now[-3];
			a[--cnt24[now[-4] >> 24]] = now[-4];
			a[--cnt24[now[-5] >> 24]] = now[-5];
			a[--cnt24[now[-6] >> 24]] = now[-6];
			a[--cnt24[now[-7] >> 24]] = now[-7]; now -= 8;
		}
		switch (n & 7) {
		case 7: {a[--cnt24[*now >> 24]] = *now; --now; }
		case 6: {a[--cnt24[*now >> 24]] = *now; --now; }
		case 5: {a[--cnt24[*now >> 24]] = *now; --now; }
		case 4: {a[--cnt24[*now >> 24]] = *now; --now; }
		case 3: {a[--cnt24[*now >> 24]] = *now; --now; }
		case 2: {a[--cnt24[*now >> 24]] = *now; --now; }
		case 1: {a[--cnt24[*now >> 24]] = *now; --now; }
		}
	}

	inline int init(u32 *_c, const int &_n) {
		c = _c;
		n = _n;
		memcpy(a, c, sizeof(u32)*n);
		for (u32 re *to = a + n, *now = a; now < to; ++now) {
			++cnt0[*now & 255];
			++cnt8[*now >> 8 & 255];
			++cnt16[*now >> 16 & 255];
			++cnt24[*now >> 24 & 255];
		}
		sort();
		m = unique(a, a + n) - a;
		for (u32 *it = c, *ed = c + n; it < ed; ++it) *it = lower_bound(a, a + m, *it) - a;
		char *ptr;
		for (re int i = 0; i < m; ++i) {
			int &x = a[i];
			ptr = str[i];
			if (x >= 1000000000u) *(ptr++) = (x / 1000000000u) ^ 48u;
			if (x >= 100000000u)  *(ptr++) = (x / 100000000u % 10u) ^ 48u;
			if (x >= 10000000u)   *(ptr++) = (x / 10000000u % 10u) ^ 48u;
			if (x >= 1000000u)    *(ptr++) = (x / 1000000u % 10u) ^ 48u;
			if (x >= 100000u)     *(ptr++) = (x / 100000u % 10u) ^ 48u;
			if (x >= 10000u)      *(ptr++) = (x / 10000u % 10u) ^ 48u;
			if (x >= 1000u)       *(ptr++) = (x / 1000u % 10u) ^ 48u;
			if (x >= 100u)        *(ptr++) = (x / 100u % 10u) ^ 48u;
			if (x >= 10u)         *(ptr++) = (x / 10u % 10u) ^ 48u;
			*(ptr++) = (x % 10u) ^ 48u;
			len[i] = ptr - str[i];
		}
		return m;
	}
#undef u32
#undef re
}

namespace Solve{
int a[N][50], b[N][255];
int *a_end[N], *b_end[N];
int n, circle_num;
int in_deg[N],ot_deg[N];
int dis_b[N],dcnt_b[N],dcnt;
bool vis[N];
Queue q;
int rec[10];
char ans3[11*3*500000];
char ans4[11*4*500000];
char ans5[11*5*1000000];
char ans6[11*6*2000000];
char ans7[11*7*3000000];
char *ans[]={nullptr,nullptr,nullptr,ans3,ans4,ans5,ans6,ans7};
char *ans_end[]={nullptr,nullptr,nullptr,ans3,ans4,ans5,ans6,ans7};

inline void for_dfs(const int&);
inline void bfs_b7();
inline void topo();
inline void solve(const int*, const int &, const int&);

inline void add_ans(const int &len) {
	++circle_num;
	for (int i = 0; i < len; ++i) {
		memcpy(ans_end[len], DISC::str[rec[i]], DISC::len[rec[i]]);
		ans_end[len] += DISC::len[rec[i]];
		*(ans_end[len]++) = ',';
	}
	*(ans_end[len]-1) = '\n';
}

inline void for_dfs(const int &p0) {
	static int *p1, *p2, *p3, *p4, *p5, *p6, *ed1, *ed2, *ed3, *ed4, *ed5, *ed6;
	rec[0] = p0;
	for (p1 = a[p0], ed1 = a_end[p0]; p1 != ed1; ++p1) {
		if (vis[*p1]) continue;
		rec[1] = *p1; vis[*p1] = 1;
		for (p2 = a[*p1], ed2 = a_end[*p1]; p2 != ed2; ++p2) {
			if (vis[*p2]) continue;
			rec[2] = *p2; vis[*p2] = 1;
			for (p3 = a[*p2], ed3 = a_end[*p2]; p3 != ed3; ++p3) {
				if (*p3 == p0) { add_ans(3); continue; }
				if (vis[*p3]) continue;
				rec[3] = *p3; vis[*p3] = 1;
				for (p4 = a[*p3], ed4 = a_end[*p3]; p4 != ed4; ++p4) {
					if (*p4 == p0) { add_ans(4); continue; }
					if (vis[*p4] || dcnt_b[*p4] != dcnt) continue;
					rec[4] = *p4; vis[*p4] = 1;
					for (p5 = a[*p4], ed5 = a_end[*p4]; p5 != ed5; ++p5) {
						if (*p5 == p0) { add_ans(5); continue; }
						if (vis[*p5] || dcnt_b[*p5] != dcnt || dis_b[*p5] > 2) continue;
						rec[5] = *p5; vis[*p5] = 1;
						for (p6 = a[*p5], ed6 = a_end[*p5]; p6 != ed6; ++p6) {
							if (*p6 == p0) { add_ans(6); continue; }
							if (!vis[*p6] && dcnt_b[*p6] == dcnt && dis_b[*p6] == 1) {
								rec[6] = *p6;
								add_ans(7);
							}
						}
						vis[*p5] = 0;
					}
					vis[*p4] = 0;
				}
				vis[*p3] = 0;
			}
			vis[*p2] = 0;
		}
		vis[*p1] = 0;
	}
}

inline void bfs_b7(const int &s){
	q.push(s);
	dcnt_b[s]=dcnt; dis_b[s]=0;
	while(!q.empty()){
		int x=q.pop_getfront();
		for (int *p = b[x], *ed = b_end[x]; p != ed; ++p)
		if(dcnt_b[*p]!=dcnt && !vis[*p]){
			dcnt_b[*p]=dcnt;
			dis_b[*p]=dis_b[x]+1;
			if(dis_b[*p]<3)q.push(*p);
		}
	}
}
inline void solve(const int *eset, const int &sz, const int &_n){
	n=_n;
	for (int i = 0; i < n; ++i) a_end[i] = a[i], b_end[i] = b[i];
	for(int i=0;i<sz;i+=2){
		*(a_end[eset[i]]++) = eset[i^1];
		*(b_end[eset[i^1]]++) = eset[i];
		++ot_deg[eset[i]];
		++in_deg[eset[i^1]];
	}
	topo();
	for(int i=0;i<n;++i)if(!vis[i]){
		sort(a[i], a_end[i]);
	}

	for (int i = 0; i < n; ++i) if (!vis[i]) {
		vis[i] = 1;
		dcnt++;
		bfs_b7(i);
		for_dfs(i);
		
		q.push(i);
		while(!q.empty()){
			int x=q.pop_getfront();
			for (int *p = a[x], *ed = a_end[x]; p != ed; ++p)if(!vis[*p]){
				if(--in_deg[*p]==0){
					q.push(*p);
					vis[*p]=1;
				}
			}
			for (int *p = b[x], *ed = b_end[x]; p != ed; ++p)if(!vis[*p]){
				if(--ot_deg[*p]==0){
					q.push(*p);
					vis[*p]=1;
				}
			}
		}
	}
}
inline void topo(){
	for(int i=0;i<n;++i){
		if(in_deg[i]==0 || ot_deg[i]==0){
			q.push(i);
			vis[i]=1;
		}
	}
	while(!q.empty()){
		int x=q.pop_getfront();
		for (int *p = a[x], *ed = a_end[x]; p != ed; ++p)if(!vis[*p]){
			if(--in_deg[*p]==0){
				q.push(*p);
				vis[*p]=1;
			}
		}
		for (int *p = b[x], *ed = b_end[x]; p != ed; ++p)if(!vis[*p]){
			if(--ot_deg[*p]==0){
				q.push(*p);
				vis[*p]=1;
			}
		}
	}
}

}

int eset[M], n = 0;

inline void input(){
	freopen("test_data4.txt","r",stdin);
	// freopen("sample_data.txt","r",stdin);
	int x,y,z;
	while(~scanf("%u,%u,%u",&x,&y,&z))
		eset[n++]=x,eset[n++]=y;
}

void output(){
	freopen("output.txt","w",stdout);
	printf("%u\n",Solve::circle_num);
	for (int i = 3; i <= 7; ++i) {
		*(Solve::ans_end[i]) = '\0';
		printf("%s", Solve::ans[i]);
		/*
		int *it = Solve::ans[i], *ed = Solve::ans_end[i];
		while (it != ed)
		for (int j = 0; j < i; ++j)
			printf("%u%c",DISC::a[*(it++)], ",\n"[j==i-1]);
		*/
	}
}

signed main(){
	input();
	int m=DISC::init(eset, n);
	Solve::solve(eset,n,m);
	timer("");
	// output();
	// timer("");
	return 0;
}
