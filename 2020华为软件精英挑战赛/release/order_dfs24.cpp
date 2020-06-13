#include <bits/stdc++.h>   
#include<pthread.h>
using namespace std;
#define int unsigned
#define push_back emplace_back
#define solve_repeat

const int N = 280001;
const int M = 560001;
const int MAX_THREAD_COUNT = 8;
int THREAD_COUNT = 8;

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
	void pop(){++h;}
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
int n;
int qaq[N];

thread threads[MAX_THREAD_COUNT];
int multi_dcnt[MAX_THREAD_COUNT][N];
bool multi_vis[MAX_THREAD_COUNT][N];
Queue multi_q[MAX_THREAD_COUNT];
int multi_rec[MAX_THREAD_COUNT][10];
int multi_ans3[MAX_THREAD_COUNT][3*500000];
int multi_ans4[MAX_THREAD_COUNT][4*500000];
int multi_ans5[MAX_THREAD_COUNT][5*1000000];
int multi_ans6[MAX_THREAD_COUNT][6*2000000];
int multi_ans7[MAX_THREAD_COUNT][7*3000000];
int *multi_ans[MAX_THREAD_COUNT][8];
int *multi_ans_end[MAX_THREAD_COUNT][8];
int final_ans3[3*500000]; 
int final_ans4[4*500000]; 
int final_ans5[5*1000000];
int final_ans6[6*2000000];
int final_ans7[7*3000000];
int *final_ans[8] = {nullptr, nullptr, nullptr, final_ans3, final_ans4, final_ans5, final_ans6, final_ans7};
int *final_ans_end[8] = {nullptr, nullptr, nullptr, final_ans3, final_ans4, final_ans5, final_ans6, final_ans7};

struct PointPool {
	int h = 0;
	std::mutex pool_mutex;
	int qwq() {
		std::lock_guard<std::mutex> guard(pool_mutex);
		return h == n ? -1 : h++;
	}
} point_pool;

void ans_sort() {
	for (int h = 0; h < n; ++h) {
		while (~qaq[h]) { /* fuck something */ }
		for (int i = 3; i <= 7; ++i) {
			int *it = multi_ans[qaq[h]][i];
			*(multi_ans_end[qaq[h]][i]) = 0xffffffff;
			while (*it == h) {
				memcpy(final_ans_end[i], it, sizeof(int)*i);
				final_ans_end[i] += i;
				it += i;
			}
		}
	}
}

inline void for_dfs(const int &p0, const int &id) {
	int *dcnt = multi_dcnt[id];
	bool *vis = multi_vis[id];
	int *rec = multi_rec[id];
	int **ans_end = multi_ans_end[id];
#define add_ans(len); memcpy(ans_end[len], rec, sizeof(int)*len);ans_end[len]+=len;
	int *p1, *p2, *p3, *p4, *p5, *p6, *ed1, *ed2, *ed3, *ed4, *ed5, *ed6;
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

inline void bfs_b7(const int &s, const int &id){
	Queue &q = multi_q[id];
	int *dcnt = multi_dcnt[id];
	bool *vis = multi_vis[id];

	q.push(s);
	dcnt[s] = s;
	int x, next_dcnt, *p, *ed;
	while(!q.empty()){
		x = q.pop_getfront();
		next_dcnt = dcnt[x]+dis1;
		if (next_dcnt < dis3) {
			for (p = b[x], ed = b_end[x]; p != ed; ++p)
			if((dcnt[*p]&dcnt_b) != s && !vis[*p]){
				dcnt[*p] = next_dcnt;
				q.push(*p);
			}
		} else {
			for (p = b[x], ed = b_end[x]; p != ed; ++p)
			if((dcnt[*p]&dcnt_b) != s && !vis[*p]){
				dcnt[*p] = next_dcnt;
			}
		}
	}
}
void multi_thread_solve(const int &id) {
	bool *vis = multi_vis[id];
	int last = 0, i;
	memset(multi_dcnt[id], 0xff, sizeof(int)*(n));
	while (~(i = point_pool.qwq())) {
		fill(vis+last, vis+i, true);
		last = i;
		vis[i] = 1;
		bfs_b7(i, id);
		for_dfs(i, id);
		qaq[i] = id;
	}
}
inline void solve(const int *eset, const int &sz, const int &_n){
#ifdef solve_repeat
	memset(multi_vis, 0, sizeof multi_vis);
	point_pool.h = 0;
	timer("",0,1);
#endif
	n = _n;
	memset(qaq, -1, sizeof(int)*n);
	for (int i = 0; i < n; ++i) {
		a_begin[i] = a_end[i] = A[i];
		b_end[i] = b[i];
	}
	for (int i = 0; i < sz; i += 2){
		*(a_end[eset[i]]++) = eset[i^1];
		*(b_end[eset[i^1]]++) = eset[i];
	}
	for(int i=0;i<n;++i){
		sort(a_begin[i], a_end[i]);
	}
	THREAD_COUNT = 7;
	for (int i = 0; i < THREAD_COUNT; ++i) {
		multi_ans[i][3] = multi_ans3[i];
		multi_ans[i][4] = multi_ans4[i];
		multi_ans[i][5] = multi_ans5[i];
		multi_ans[i][6] = multi_ans6[i];
		multi_ans[i][7] = multi_ans7[i];
		multi_ans_end[i][3] = multi_ans3[i];
		multi_ans_end[i][4] = multi_ans4[i];
		multi_ans_end[i][5] = multi_ans5[i];
		multi_ans_end[i][6] = multi_ans6[i];
		multi_ans_end[i][7] = multi_ans7[i];
	}
	thread ans_sort_thread = thread(ans_sort);
	for (int t = 0; t < THREAD_COUNT; ++t) {
		threads[t] = thread(multi_thread_solve, t);
	}
	for (int t = 0; t < THREAD_COUNT; ++t) {
		if (threads[t].joinable()) threads[t].join();
	}
	if (ans_sort_thread.joinable()) ans_sort_thread.join();
}

}

int eset[M], n = 0;

inline void input(){
	freopen("test_data.txt","r",stdin);
	// freopen("sample_data.txt","r",stdin);
	int x,y,z;
	while(~scanf("%u,%u,%u",&x,&y,&z))
		eset[n++]=x,eset[n++]=y;
}

struct OP{
	bool operator()(const int *const&a,const int *const&b) const { return *a > *b; }
};
priority_queue<int*, vector<int*>, OP> pri_q;

void output(){
	freopen("output.txt","w",stdout);
	int num = 0;
	for (int t = 0; t < THREAD_COUNT; ++t) {
		int **ans_end = Solve::multi_ans_end[t];
		int **ans = Solve::multi_ans[t];
		for (int i = 3; i <= 7; ++i) {
			num += (ans_end[i]-ans[i])/i;
		}
	}
	printf("%u\n",num);
	/*
	for (int i = 3; i <= 7; ++i) {
		for (int t = 0; t < THREAD_COUNT; ++t) {
			if (Solve::multi_ans[t][i] != Solve::multi_ans_end[t][i]) {
				pri_q.push(Solve::multi_ans[t][i]);
				*(Solve::multi_ans_end[t][i]) = 0xffffffff;
			}
		}
		while (!pri_q.empty()) {
			int *it = pri_q.top();
			pri_q.pop();
			while (pri_q.empty() || *it < *pri_q.top()) {
				for (int j = 0; j < i; ++j) {
					printf("%u%c",DISC::a[*(it++)], ",\n"[j==i-1]);
				}
				if (*it == 0xffffffff) break;
			}
			if (*it != 0xffffffff) pri_q.push(it);
		}
	}
	*/
	for (int i = 3; i <= 7; ++i) {
		int *it = Solve::final_ans_end[i];
		int *ed = Solve::final_ans[i];
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
	output();
	timer("output");
	return 0;
}