/*
#pragma GCC target("sse,sse2,sse3,sse4.1,sse4.2,popcnt,abm,mmx,avx")
//#pragma comment(linker,"/STACK:102400000,102400000")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
*/
#pragma GCC optimize(3)
#include <bits/stdc++.h>   
#include<pthread.h>
using namespace std;
#define int unsigned
#define push_back emplace_back
// #define MULTI_THREAD

#define solve_repeat

const int N = 280001;
const int M = 560001;
const int THREAD_COUNT = 1;

struct Timer{
	double start, pre, sum, now; int cnt;
	Timer(){start = pre = clock(); sum = cnt = 0;}
	void operator()(const string &s = "default", const bool &record = 0, const bool &silent = 0){
		now = clock();
		if(!silent)
			cerr << setiosflags(ios::fixed) << setprecision(3) << setw(10) << s << " * " <<
				"Interval:" << setw(6) << (now - pre) / CLOCKS_PER_SEC << "s | " <<
				"Total:" << setw(6) << (now - start) / CLOCKS_PER_SEC << "s";
		if(record){
			sum += now - pre; ++cnt;
			if(!silent)cerr << setiosflags(ios::fixed) << setprecision(3) <<
				" | Average:" << setw(6) << sum / (cnt * CLOCKS_PER_SEC) << "s (count " << cnt << " times)";
		}
		if(!silent)cerr << endl;
		pre = now;
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
const int dis1 = 1u<<30;
const int dis2 = 2u<<30;
const int dis3 = 3u<<30;
const int dcnt_b = (1u<<30)-1;

int A[N][51], b[N][51];
int *a_begin[N], *a_end[N], *b_end[N];
int in_deg[N],ot_deg[N];
int dcnt[N]; // dis_b << 30 + dcnt_b
bool vis[N];
Queue q;
int rec[10];
int ans3[3*500000];
int ans4[4*500000];
int ans5[5*1000000];
int ans6[6*2000000];
int ans7[7*3000000];
int *ans[]={nullptr,nullptr,nullptr,ans3,ans4,ans5,ans6,ans7};
int *ans_end[]={nullptr,nullptr,nullptr,ans3,ans4,ans5,ans6,ans7};

inline void for_dfs(const int&);
inline void bfs_b7(const int&);
inline void topo(const int&);
inline void solve(const int*, const int &, const int&);

inline void for_dfs(const int &p0) {
#define add_ans(len); memcpy(ans_end[len], rec, sizeof(int)*len);ans_end[len]+=len;
	static int *p1, *p2, *p3, *p4, *p5, *p6, *ed1, *ed2, *ed3, *ed4, *ed5, *ed6;
	int circle_end = p0+dis1;
	rec[0] = p0;
	for (p1 = a_begin[p0], ed1 = a_end[p0]; p1 != ed1; ++p1) {
		if (vis[*p1]) continue;
		rec[1] = *p1; vis[*p1] = 1;
		for (p2 = a_begin[*p1], ed2 = a_end[*p1]; p2 != ed2; ++p2) {
			if (vis[*p2]) continue;
			rec[2] = *p2; vis[*p2] = 1;
			if (dcnt[*p2] == circle_end) { add_ans(3); }
			for (p3 = a_begin[*p2], ed3 = a_end[*p2]; p3 != ed3; ++p3) {
				if (vis[*p3]) continue;
				rec[3] = *p3; vis[*p3] = 1;
				if (dcnt[*p3] == circle_end) { add_ans(4); }
				for (p4 = a_begin[*p3], ed4 = a_end[*p3]; p4 != ed4; ++p4) {
					if (vis[*p4] || (dcnt[*p4]&dcnt_b) != p0) continue;
					rec[4] = *p4; vis[*p4] = 1;
					if (dcnt[*p4] == circle_end) { add_ans(5); }
					for (p5 = a_begin[*p4], ed5 = a_end[*p4]; p5 != ed5; ++p5) {
						if (vis[*p5] || (dcnt[*p5]&dcnt_b) != p0 || dcnt[*p5] >= dis3) continue;
						rec[5] = *p5; vis[*p5] = 1;
						if (dcnt[*p5] == circle_end) { add_ans(6); }
						for (p6 = a_begin[*p5], ed6 = a_end[*p5]; p6 != ed6; ++p6) {
							if (!vis[*p6] && dcnt[*p6] == circle_end) {
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
#undef add_ans
}

inline void bfs_b7(const int &s){
	q.push(s);
	dcnt[s] = s;
	int x, next_dcnt;
	while(!q.empty()){
		x = q.pop_getfront();
		next_dcnt = dcnt[x]+dis1;
		if (next_dcnt < dis3) {
			for (int *p = b[x], *ed = b_end[x]; p != ed; ++p)
			if((dcnt[*p]&dcnt_b) != s && !vis[*p]){
				dcnt[*p] = next_dcnt;
				q.push(*p);
			}
		} else {
			for (int *p = b[x], *ed = b_end[x]; p != ed; ++p)
			if((dcnt[*p]&dcnt_b) != s && !vis[*p]){
				dcnt[*p] = next_dcnt;
			}
		}
	}
}
inline void solve(const int *eset, const int &sz, const int &n){
#ifdef solve_repeat
	memset(vis, 0, sizeof(bool)*n);
	ans_end[3] = ans3;
	ans_end[4] = ans4;
	ans_end[5] = ans5;
	ans_end[6] = ans6;
	ans_end[7] = ans7;
	timer("",0,1);
#endif
	memset(dcnt, 0xff, sizeof(int)*(n));
	for (int i = 0; i < n; ++i) {
		a_begin[i] = a_end[i] = A[i];
		b_end[i] = b[i];
	}
	for (int i = 0; i < sz; i += 2){
		*(a_end[eset[i]]++) = eset[i^1];
		*(b_end[eset[i^1]]++) = eset[i];
	}
	topo(n);
	for(int i=0;i<n;++i)if(!vis[i]){
		sort(a_begin[i], a_end[i]);
	}

	for (int i = 0; i < n; ++i) if (!vis[i]) {
		vis[i] = 1;
		bfs_b7(i);
		for_dfs(i);
		
		for(register const int *p = b[i], *ed = b_end[i]; p != ed; ++p)
			++a_begin[*p];
		
		q.push(i);
		while(!q.empty()){
			int x=q.pop_getfront();
			for (int *p = a_begin[x], *ed = a_end[x]; p != ed; ++p)if(!vis[*p]){
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
inline void topo(const int &n){
	for(int i = 0; i < n; ++i){
		if((in_deg[i] = b_end[i] - b[i]) == 0 || (ot_deg[i] = a_end[i] - a_begin[i]) == 0){
			q.push(i);
			vis[i] = 1;
		}
	}
	while(!q.empty()){
		int x=q.pop_getfront();
		for (int *p = a_begin[x], *ed = a_end[x]; p != ed; ++p)if(!vis[*p]){
			if(--in_deg[*p] == 0){
				q.push(*p);
				vis[*p] = 1;
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
	int num = 0;
	for (int i = 3; i <= 7; ++i) num += (Solve::ans_end[i]-Solve::ans[i])/i;
	printf("%u\n",num);
	for (int i = 3; i <= 7; ++i) {
		int *it = Solve::ans[i], *ed = Solve::ans_end[i];
		while (it != ed)
		for (int j = 0; j < i; ++j)
			printf("%u%c",DISC::a[*(it++)], ",\n"[j==i-1]);
	}
}

signed main(){
	input();
	timer("input");
	int m = DISC::init(eset, n);
	timer("disc");
	#ifdef solve_repeat
	for(int i = 10; i--;)
	#endif
	{
		Solve::solve(eset, n, m);
		timer("solve", 1);
	}
	// output();
	timer("output");
	return 0;
}

