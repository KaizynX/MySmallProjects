#pragma GCC optimize(3)
#include <cstdio>
#include <fstream>
#include <iomanip>
#include <bits/stdc++.h>   
#include<vector>
#include<stdlib.h>
#include<sys/types.h>
#include<pthread.h>
#include<unistd.h>
#include <sys/stat.h>
#include<sys/mman.h>
#include<fcntl.h>
#include<string.h>
using namespace std;
#define int unsigned
#define push_back emplace_back
const int N = 560010;
struct Queue {
	int a[1 << 16];
	unsigned short h, t;
	Queue() { h = t = 0; }
	void push(int x) { a[t++] = x; }
	void pop() { h++; }
	bool empty() { return h == t; }
	int front() { return a[h]; }
	int size() { return t - h; }
	int pop_getfront() { return a[h++]; }
};

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

namespace Solve {
	typedef pair<int, int> pii;
	vector<int> a[N], b[N];
	int s, n;
	int in_deg[N], ot_deg[N];
	int dis_b[N], dcnt_b[N], dcnt;
	bool vis[N], inq[N];
	Queue q;
	int rec[10];
	int ans3[3 * 500000];
	int ans4[4 * 500000];
	int ans5[5 * 1000000];
	int ans6[6 * 2000000];
	int ans7[7 * 3000000];
	int *ans[] = { nullptr,nullptr,nullptr,ans3,ans4,ans5,ans6,ans7 };
	int *ans_end[] = { nullptr,nullptr,nullptr,ans3,ans4,ans5,ans6,ans7 };

	inline void add_ans(const int&);
	inline void for_dfs(const int&);
	inline void bfs_b7();
	inline void topo();
	inline void solve(const int*, const int &, const int&);

	inline void add_ans(const int &len) {
		memcpy(ans_end[len], rec, sizeof(int)*len);
		ans_end[len] += len;
	}

	inline void for_dfs(const int &p0) {
		rec[0] = p0; vis[p0] = 1;
		for (const auto &p1 : a[p0]) {
			if (vis[p1]) continue;
			rec[1] = p1; vis[p1] = 1;
			for (const auto &p2 : a[p1]) {
				if (vis[p2]) continue;
				rec[2] = p2; vis[p2] = 1;
				for (const auto &p3 : a[p2]) {
					if (p3 == s) { add_ans(3); continue; }
					if (vis[p3]) continue;
					rec[3] = p3; vis[p3] = 1;
					for (const auto &p4 : a[p3]) {
						if (p4 == s) { add_ans(4); continue; }
						if (vis[p4] || dcnt_b[p4] != dcnt) continue;
						rec[4] = p4; vis[p4] = 1;
						for (const auto &p5 : a[p4]) {
							if (p5 == s) { add_ans(5); continue; }
							if (vis[p5] || dcnt_b[p5] != dcnt || dis_b[p5] > 2) continue;
							rec[5] = p5; vis[p5] = 1;
							for (const auto &p6 : a[p5]) {
								if (p6 == s) { add_ans(6); continue; }
								if (!vis[p6] && dcnt_b[p6] == dcnt && dis_b[p6] == 1) {
									rec[6] = p6;
									add_ans(7);
								}
							}
							vis[p5] = 0;
						}
						vis[p4] = 0;
					}
					vis[p3] = 0;
				}
				vis[p2] = 0;
			}
			vis[p1] = 0;
		}
		vis[p0] = 0;
	}
	inline void bfs_b7() {
		q.push(s);
		dcnt_b[s] = dcnt; dis_b[s] = 0;
		while (!q.empty()) {
			int x = q.pop_getfront();
			for (const auto &p : b[x])
				if (dcnt_b[p] != dcnt && !vis[p]) {
					dcnt_b[p] = dcnt;
					dis_b[p] = dis_b[x] + 1;
					if (dis_b[p] < 3)q.push(p);
				}
		}
	}
	inline void solve(const int *eset, const int &sz, const int &_n) {
		for (int i = 0; i < sz; i += 2) {
			a[eset[i]].push_back(eset[i ^ 1]);
			b[eset[i ^ 1]].push_back(eset[i]);
			++ot_deg[eset[i]];
			++in_deg[eset[i ^ 1]];
		}
		n = _n;
		topo();
		for (int i = 0; i < n; ++i)if (!vis[i]) {
			sort(a[i].begin(), a[i].end());
		}

		for (int i = 0; i < n; ++i) if (!vis[i]) {
			s = i;
			dcnt++;
			bfs_b7();
			for_dfs(s);

			q.push(s);
			inq[s] = 1;
			while (q.size()) {
				int x = q.pop_getfront();
				for (const int &p : a[x])if (!vis[p]) {
					if (--in_deg[p] == 0 && !inq[p]) {
						q.push(p);
						inq[p] = 1;
					}
				}
				for (const int &p : b[x])if (!vis[p]) {
					if (--ot_deg[p] == 0 && !inq[p]) {
						q.push(p);
						inq[p] = 1;
					}
				}
				vis[x] = 1;
				inq[x] = 0;
			}
		}
	}
	inline void topo() {
		for (int i = 0; i < n; ++i) {
			if (in_deg[i] == 0 || ot_deg[i] == 0) {
				q.push(i);
				inq[i] = 1;
			}
		}
		while (q.size()) {
			int x = q.pop_getfront();
			for (const int &p : a[x])if (!vis[p]) {
				if (--in_deg[p] == 0 && !inq[p]) {
					q.push(p);
					inq[p] = 1;
				}
			}
			for (const int &p : b[x])if (!vis[p]) {
				if (--ot_deg[p] == 0 && !inq[p]) {
					q.push(p);
					inq[p] = 1;
				}
			}
			vis[x] = 1;
			in_deg[x] = ot_deg[x] = 0;
			inq[x] = 0;
		}
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
	register int d = 0;
	while ((*mapped) != '\0' && n < 560000)
	{
		read(mapped, eset[n++]);
		read(mapped, eset[n++]);
		read_skip(mapped);
	}
}
inline void output()
{
	n = 0;
	for (register int i = 3; i <= 7; ++i)n += (Solve::ans_end[i] - Solve::ans[i]) / i;
	int fd = open("/projects/student/result.txt", O_RDWR | O_CREAT, 0777);
	ftruncate(fd, n * 7 * 12);
	char*buf = (char*)mmap(NULL, n * 7 * 12, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	char*mapped = buf;
	mapped += sprintf(mapped, "%u%c", n, '\n');
	for (register int i = 3; i <= 7; ++i)
	{
		int *it = Solve::ans[i], *ed = Solve::ans_end[i];
		while (it != ed)
		{
			for (int j = 0; j < i; ++j)
			{
				memcpy(mapped, DISC::str[*it], DISC::len[*(it)]);
				mapped += DISC::len[*(it++)];
				*(mapped++) = ',';
			}
			*(mapped - 1) = '\n';
		}
	}
	munmap(buf, n * 7 * 12);
	ftruncate(fd, mapped - buf);
}
signed main()
{
	input();
	int m = DISC::init(eset, n);
	Solve::solve(eset, n, m);
	output();
	exit(0);
}