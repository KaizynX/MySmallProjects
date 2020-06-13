#include <cstdio>
#include <fstream>
#include <iomanip>
#include <bits/stdc++.h>   
#include<vector>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include <sys/stat.h>
#include<sys/mman.h>
#include<fcntl.h>
#include<string.h>

using namespace std;
#define int unsigned
#define push_back emplace_back
const int N = 560010;
namespace bkt {
	const int null = N - 1;
	struct element {
		int pre, nxt;
	}bkt[N];
	int head[N], top;
	void add(int i, int deg) {
		int &h = head[deg];
		bkt[i] = { null,h };
		bkt[h].pre = i;
		h = i;
	}
	void erase(int i, int deg) {
		bkt[bkt[i].pre].nxt = bkt[i].nxt;
		bkt[bkt[i].nxt].pre = bkt[i].pre;
		if (i == head[deg])head[deg] = bkt[i].nxt;
	}
}

namespace DISC {
#define u32 unsigned
#define re register
	typedef pair<int, int> pii;
	u32 a[N], b[N], *c;
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
		for (u32 *it = c, *ed = c + n; it < ed; ++it) {
			*it = lower_bound(a, a + m, *it) - a;
		}
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

namespace Solve {
	typedef pair<int, int> pii;
	vector<int> a[N], b[N];
	int s, n;
	set<pii> order;
	int in_deg[N], ot_deg[N], deg[N];
	int dis_b[N], dcnt_b[N], dcnt;
	int dis_a[N], dcnt_a[N];
	bool del[N], vis[N], inq[N];
	vector<int> rec;
	vector<vector<int>> ans;
	int S[N], dfn[N], low[N], cnt, top;
	bool InStack[N];
	int colors, color[N];
	struct Stack_Node {
		int u; vector<int>::iterator e; int S;
	} Stk[N];

	void bfs_a3();
	void bfs_b7();
	inline void adjust();
	inline void topo();
	inline void tarjan(const int &);
	vector<vector<int>>& solve(const int*, const int &, const int&);

	void for_dfs(const int &p1) {
		vis[p1] = 1;
		for (const auto &p2 : a[p1]) {
			if (p2 == s || vis[p2] || dcnt_b[p2] != dcnt || rec.size() + dis_b[p2] > 7) continue;
			rec.push_back(p2); vis[p2] = 1;
			for (const auto &p3 : a[p2]) {
				if (p3 == s || vis[p3] || dcnt_b[p3] != dcnt || rec.size() + dis_b[p3] > 7) continue;
				rec.push_back(p3); vis[p3] = 1;
				for (const auto &p4 : a[p3]) {
					if (p4 == s) { ans.push_back(rec); continue; }
					if (vis[p4] || dcnt_b[p4] != dcnt || rec.size() + dis_b[p4] > 7) continue;
					rec.push_back(p4); vis[p4] = 1;
					for (const auto &p5 : a[p4]) {
						if (p5 == s) { ans.push_back(rec); continue; }
						if (vis[p5] || dcnt_b[p5] != dcnt || rec.size() + dis_b[p5] > 7) continue;
						rec.push_back(p5); vis[p5] = 1;
						for (const auto &p6 : a[p5]) {
							if (p6 == s) { ans.push_back(rec); continue; }
							if (vis[p6] || dcnt_b[p6] != dcnt || rec.size() + dis_b[p6] > 7) continue;
							rec.push_back(p6); vis[p6] = 1;
							for (const auto &p7 : a[p6]) {
								if (p7 == s) { ans.push_back(rec); continue; }
								if (!vis[p7] && dcnt_b[p7] == dcnt && dis_b[p7] == 1) {
									rec.push_back(p7);
									ans.push_back(rec);
									rec.pop_back();
								}
							}
							rec.pop_back(); vis[p6] = 0;
						}
						rec.pop_back(); vis[p5] = 0;
					}
					rec.pop_back(); vis[p4] = 0;
				}
				rec.pop_back(); vis[p3] = 0;
			}
			rec.pop_back(); vis[p2] = 0;
		}
		vis[p1] = 0;
	}
	void bfs_a3() {
		static queue<int> q;
		q.push(s);
		dcnt_a[s] = dcnt; dis_a[s] = 0;
		while (!q.empty()) {
			int x = q.front(); q.pop();
			for (const auto &p : a[x])
				if (color[p] == color[s] && dcnt_a[p] != dcnt && !del[p]) {
					dcnt_a[p] = dcnt;
					dis_a[p] = dis_a[x] + 1;
					if (dis_a[p] < 3)q.push(p);
				}
		}
	}
	void bfs_b7() {
		static queue<int> q;
		q.push(s);
		dcnt_b[s] = dcnt; dis_b[s] = 0;
		while (!q.empty()) {
			int x = q.front(); q.pop();
			for (const auto &p : b[x])
				if (color[p] == color[s] && dcnt_b[p] != dcnt && !del[p]) {
					dcnt_b[p] = dcnt;
					dis_b[p] = dis_b[x] + 1;
					if (dis_b[p] < 4 || (dcnt_a[p] == dcnt && dis_b[p] + dis_a[p] <= 7))q.push(p);
				}
		}
	}
	vector<vector<int>>& solve(const int *eset, const int &sz, const int &_n) {
		ans.reserve(3000000);
		for (int i = 0; i < sz; i += 2) {
			a[eset[i]].push_back(eset[i ^ 1]);
			b[eset[i ^ 1]].push_back(eset[i]);
			++ot_deg[eset[i]];
			++in_deg[eset[i ^ 1]];
		}
		n = _n;
		static queue<int> q;
		topo();
		for (int i = 0; i < n; ++i) {
			if (!dfn[i]) tarjan(i);
		}

		fill(bkt::head, bkt::head + N, bkt::null);
		for (int i = 0; i < n; i++)
			if (!del[i]) {
				deg[i] = in_deg[i] + ot_deg[i];
				bkt::add(i, deg[i]);
			}

		bkt::top = N - 2;
		while (1) {
			while (bkt::top != 0 && bkt::head[bkt::top] == bkt::null)bkt::top--;
			if (bkt::top == 0)break;

			s = bkt::head[bkt::top];

			dcnt++;
			bfs_a3();
			bfs_b7();
			rec.assign(1, s);
			for_dfs(s);
			del[s] = 1;

			q.push(s);
			inq[s] = 1;
			while (q.size()) {
				int x = q.front(); q.pop();
				for (const int &p : a[x])if (!del[p]) {
					bkt::erase(p, deg[p]);
					deg[p]--;
					bkt::add(p, deg[p]);
					if (--in_deg[p] == 0 && !inq[p]) {
						q.push(p);
						inq[p] = 1;
					}
				}
				for (const int &p : b[x])if (!del[p]) {
					bkt::erase(p, deg[p]);
					deg[p]--;
					bkt::add(p, deg[p]);
					if (--ot_deg[p] == 0 && !inq[p]) {
						q.push(p);
						inq[p] = 1;
					}
				}
				bkt::erase(x, deg[x]);
				del[x] = 1;
				deg[x] = in_deg[x] = ot_deg[x] = 0;
				inq[x] = 0;
			}
		}
		adjust();
		return ans;
	}
	void adjust() { 
		for (auto &arr : ans) {
			rotate(arr.begin(), min_element(arr.begin(), arr.end()), arr.end());
		}
		sort(ans.begin(), ans.end(), [](const vector<int> &a, const vector<int> &b)->bool {
			if (a.size() != b.size())return a.size() < b.size();
			return a < b;
		});
	}
	inline void topo() {
		static queue<int> q;
		for (int i = 0; i < n; ++i) {
			if (in_deg[i] == 0 || ot_deg[i] == 0) {
				q.push(i);
				inq[i] = 1;
			}
		}
		while (q.size()) {
			int x = q.front(); q.pop();
			for (const int &p : a[x])if (!del[p]) {
				if (--in_deg[p] == 0 && !inq[p]) {
					q.push(p);
					inq[p] = 1;
				}
			}
			for (const int &p : b[x])if (!del[p]) {
				if (--ot_deg[p] == 0 && !inq[p]) {
					q.push(p);
					inq[p] = 1;
				}
			}
			del[x] = 1;
			in_deg[x] = ot_deg[x] = 0;
			inq[x] = 0;
		}
	}

	inline void tarjan(const int &x) {
#define v *e
		int tail = 0;
		++tail;
		Stk[tail].u = x;
		Stk[tail].e = a[x].begin();
		Stk[tail].S = 0;
		while (tail) {
			bool flag = 0;
			int u = Stk[tail].u;
			vector<int>::iterator e = Stk[tail].e;
			switch (Stk[tail].S) {
			case 0:
				dfn[u] = low[u] = ++cnt;
				InStack[u] = true;
				S[top++] = u;
				Stk[tail].S = 1;
				flag = 0;
				for (; e != a[u].end(); ++e) {
					if (dfn[v] == 0) {
						Stk[tail].e = e;
						++tail;
						Stk[tail].u = v;
						Stk[tail].e = a[v].begin();
						Stk[tail].S = 0;
						flag = true;
						break;
			case 1:
				flag = false;
				low[u] = min(low[v], low[u]);
					}
					else if (InStack[v]) {
						low[u] = min(low[u], dfn[v]);
					}

				}
				if (flag) break;
				if (dfn[u] == low[u]) {
					++colors;
					do {
						int j = S[--top];
						color[j] = colors;
						InStack[j] = false;
						if (j == u) break;
					} while (1);
				}
				tail--;
			}
		}
#undef v
	}

}

inline void read(char *&s, unsigned &x) {
	while (*s < '0') ++s;
	while (*s > '/') x = (x << 3u) + (x << 1u) + (*(s++) ^ '0');
}
inline void read_skip(char *&s) {
	while (*s < '0') ++s;
	while (*s > '/') ++s;
}
int eset[N];
int n = 0;
inline void input()
{
	struct stat statbuf;
	register int sz = 0;
	if (stat("/data/test_data.txt", &statbuf) == 0)sz = statbuf.st_size;
	int fd = open("/data/test_data.txt", O_RDONLY);
	char* buf = (char*)mmap(NULL, sz, PROT_READ, MAP_PRIVATE, fd, 0);
	char*mapped = buf;
	while ((*mapped) != '\0' && n < 560000)
	{
		read(mapped, eset[n++]);
		read(mapped, eset[n++]);
		read_skip(mapped);
	}
}
inline void output(vector<vector<int>>&ans)
{
	n = ans.size();
	int fd = open("/projects/student/result.txt", O_RDWR | O_CREAT, 0777);
	ftruncate(fd, n * 7 * 12);
	char*buf = (char*)mmap(NULL, n * 7 * 12, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	char*mapped = buf;
	mapped += sprintf(mapped, "%u%c", n, '\n');
	for (register int i = 0; i < n; ++i)
	{
		for (register int j = 0; j < ans[i].size(); ++j)
		{
			memcpy(mapped, DISC::str[ans[i][j]], DISC::len[ans[i][j]]);
			mapped += DISC::len[ans[i][j]];
			*(mapped++) = ',';
		}
		*(mapped - 1) = '\n';
	}
	munmap(buf, n * 7 * 12);
	ftruncate(fd, mapped - buf);
}
signed main()
{
	input();
	output(Solve::solve(eset, n, DISC::init(eset, n)));
	exit(0);
}