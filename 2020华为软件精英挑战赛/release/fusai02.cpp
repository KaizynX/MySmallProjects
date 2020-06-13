#include <bits/stdc++.h>   
using namespace std;
#define int unsigned
#define push_back emplace_back
// #define solve_repeat
// #define DEBUG

const int N = 4000001;
const int M = 2*2000001;

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
map<int, int> c[N];
int n;
bool vis[N];
int rec[10];
vector<int> ans[8];

inline bool money_check(const int&, const int&);
inline void add_ans(const int&);
inline void for_dfs(const int&);
inline void bfs_b7(const int&);
inline void topo();

inline void add_ans(const int &len) {
	ans[len].insert(ans[len].end(), rec, rec+len);
}
inline bool money_check(const int &X, const int &Y) {
	// 0.2 <= Y/X <= 3
	return X <= Y*5ULL && Y <= X*3ULL; 
	// return (X-1)/5 < Y && (Y-1)/3 < X;
}

inline void for_dfs(const int &p0) {
	rec[0] = p0;
	vis[p0] = 1;
	for (auto &p1 : c[p0]) {
		if (vis[p1.first]) continue;
		vis[p1.first] = 1;
		rec[1] = p1.first;
		for (auto &p2 : c[p1.first]) {
			if (vis[p2.first] || !money_check(p1.second, p2.second)) continue;
			vis[p2.first] = 1;
			rec[2] = p2.first;
			for (auto &p3 : c[p2.first]) {
				if (!money_check(p2.second, p3.second)) continue;
				if (p3.first == p0 && money_check(p3.second, p1.second)) { add_ans(3); continue;}
				if (vis[p3.first]) continue;
				vis[p3.first] = 1;
				rec[3] = p3.first;
				for (auto &p4 : c[p3.first]) {
					if (!money_check(p3.second, p4.second)) continue;
					if (p4.first == p0 && money_check(p4.second, p1.second)) { add_ans(4); continue;}
					if (vis[p4.first]) continue;
					vis[p4.first] = 1;
					rec[4] = p4.first;
					for (auto &p5 : c[p4.first]) {
						if (!money_check(p4.second, p5.second)) continue;
						if (p5.first == p0 && money_check(p5.second, p1.second)) { add_ans(5); continue;}
						if (vis[p5.first]) continue;
						vis[p5.first] = 1;
						rec[5] = p5.first;
						for (auto &p6 : c[p5.first]) {
							if (!money_check(p5.second, p6.second)) continue;
							if (p6.first == p0 && money_check(p6.second, p1.second)) { add_ans(6); continue;}
							if (vis[p6.first]) continue;
							vis[p6.first] = 1;
							rec[6] = p6.first;
							for (auto &p7 : c[p6.first]) {
								if (!money_check(p6.second, p7.second)) continue;
								if (p7.first == p0 && money_check(p7.second, p1.second)) { add_ans(7); break; }
							}
							vis[p6.first] = 0;
						}
						vis[p5.first] = 0;
					}
					vis[p4.first] = 0;
				}
				vis[p3.first] = 0;
			}
			vis[p2.first] = 0;
		}
		vis[p1.first] = 0;
	}
}

inline void solve(const int *eset, const int *wset, const int &sz, const int &_n){
	n = _n;
	for (int i = 0; i < sz; i += 2) {
		c[eset[i]].insert(make_pair(eset[i^1], wset[i>>1]));
	}
	for (int i = 0; i < n; ++i) {
		for_dfs(i);
	}
}

}

int eset[M], wset[M>>1], n = 0;

inline void input(){
	freopen("test_data.txt","r",stdin);
	// freopen("sample_data.txt", "r", stdin);
	int x,y,z;
	while(~scanf("%u,%u,%u",&x,&y,&z))
		eset[n++]=x,eset[n++]=y,wset[(n>>1)-1]=z;
}

void output(){
	freopen("output.txt","w",stdout);
	n = 0;
	for (int i = 3; i <= 7; ++i) n += Solve::ans[i].size()/i;
	printf("%u\n", n);
	for (int i = 3; i <= 7; ++i) {
		auto p = Solve::ans[i].begin(), ed = Solve::ans[i].end();
		while (p != ed) {
			for (int j = 0; j < i; ++j) {
				printf("%u%c",DISC::a[*(p++)], ",\n"[j==i-1]);
			}
		}
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
		Solve::solve(eset, wset, n, m);
		timer("solve", 1);
	}
	output();
	timer("output");
	return 0;
}