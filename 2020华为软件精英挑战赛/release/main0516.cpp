#include <cstdio>

#include <iomanip>

#include <bits/stdc++.h>   

#include<stdlib.h>

#include<sys/types.h>

#include<pthread.h>

#include<unistd.h>

#include <sys/stat.h>

#include<sys/mman.h>

#include<fcntl.h>

using namespace std;

#define int unsigned

#define push_back emplace_back

const int N = 4000001;

const int M = 2*2000001;

struct Info

{

	int start;

	int end;

};



struct Queue {

	int a[1 << 22];

	unsigned h : 22, t : 22;

	Queue() { h = t = 0; }

	void push(int x) { a[t++] = x; }

	void pop() { ++h; }

	bool empty() { return h == t; }

	int front() { return a[h]; }

	int size() { return t - h; }

	int pop_getfront() { return a[h++]; }

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



namespace Solve {

	const int dis1 = 1u << 30;

	const int dis2 = 2u << 30;

	const int dis3 = 3u << 30;

	const int dcnt_b = (1u << 30) - 1;

	vector<pair<int, double>> a[N];

	vector<pair<int, double>>::iterator a_begin[N];

	vector<int> b[N];

	map<int, double> c[N];

	int in_deg[N], ot_deg[N];

	int n, circle_num;

	int dcnt[N];

	bool vis[N];

	Queue q;

	int rec[10];

	vector<int> ans[9];



	inline void add_ans(const int&);

	inline void for_dfs(const int&);

	inline void bfs_b7(const int&);

	inline void topo();



	inline void add_ans(const int &len) {

		ans[len].insert(ans[len].end(), rec, rec + len);

	}

	inline bool money_check(const double &X, const double &Y) {

		return Y / X >= 0.2 && Y / X <= 3;

	}



	inline void for_dfs(const int &p0) {

#define circle_check(fuck) dcnt[fuck->first] == circle_end && \

						   money_check(fuck->second, c[fuck->first][p0]) && \

						   money_check(c[fuck->first][p0], p1->second)

	vector<pair<int, double>>::iterator p1, p2, p3, p4, p5, p6, p7, ed1, ed2, ed3, ed4, ed5, ed6, ed7;

	int circle_end = p0+dis1;

	rec[0] = p0;

	for (p1 = a_begin[p0], ed1 = a[p0].end(); p1 != ed1; ++p1) {

		if (vis[p1->first]) continue;

		rec[1] = p1->first; vis[p1->first] = 1;

		for (p2 = a_begin[p1->first], ed2 = a[p1->first].end(); p2 != ed2; ++p2) {

			if (vis[p2->first] || !money_check(p1->second, p2->second)) continue;

			rec[2] = p2->first; vis[p2->first] = 1;

			if (circle_check(p2)) { add_ans(3); }

			for (p3 = a_begin[p2->first], ed3 = a[p2->first].end(); p3 != ed3; ++p3) {

				if (vis[p3->first] || !money_check(p2->second, p3->second)) continue;

				rec[3] = p3->first; vis[p3->first] = 1;

				if (circle_check(p3)) { add_ans(4); }

				for (p4 = a_begin[p3->first], ed4 = a[p3->first].end(); p4 != ed4; ++p4) {

					if (vis[p4->first] || !money_check(p3->second, p4->second)) continue;

					rec[4] = p4->first; vis[p4->first] = 1;

					if (circle_check(p4)) { add_ans(5); }

					for (p5 = a_begin[p4->first], ed5 = a[p4->first].end(); p5 != ed5; ++p5) {

						if (vis[p5->first] || (dcnt[p5->first]&dcnt_b) != p0 || !money_check(p4->second, p5->second)) continue;

						rec[5] = p5->first; vis[p5->first] = 1;

						if (circle_check(p5)) { add_ans(6); }

						for (p6 = a_begin[p5->first], ed6 = a[p5->first].end(); p6 != ed6; ++p6) {

							if (vis[p6->first] || (dcnt[p6->first]&dcnt_b) != p0 || dcnt[p6->first] >= dis3  || !money_check(p5->second, p6->second)) continue;

							rec[6] = p6->first; vis[p6->first] = 1;

							if (circle_check(p6)) { add_ans(7); }

							for (p7 = a_begin[p6->first], ed7 = a[p6->first].end(); p7 != ed7; ++p7) {

								if (!vis[p7->first] && circle_check(p7)) {

									rec[7] = p7->first;

									add_ans(8);

								}

							}

							vis[p6->first] = 0;

						}

						vis[p5->first] = 0;

					}

					vis[p4->first] = 0;

				}

				vis[p3->first] = 0;

			}

			vis[p2->first] = 0;

		}

		vis[p1->first] = 0;

	}

#undef circle_check

}



	inline void bfs_b7(const int &s) {

		q.push(s);

		dcnt[s] = s;

		int x, next_dcnt;

		vector<int>::iterator p, ed;

		while (!q.empty()) {

			x = q.pop_getfront();

			next_dcnt = dcnt[x] + dis1;

			for (p = b[x].begin(), ed = b[x].end(); p != ed; ++p)

				if ((dcnt[*p] & dcnt_b) != s && !vis[*p]) {

					dcnt[*p] = next_dcnt;

					if (next_dcnt < dis3) q.push(*p);

				}

		}

	}

	inline void solve(const int *eset, const double *wset, const int &sz, const int &_n) {

		n = _n;

		memset(dcnt, 0xff, sizeof(int)*(n));

		for (int i = 0; i < sz; i += 2) {

			a[eset[i]].emplace_back(eset[i ^ 1], wset[i >> 1]);

			b[eset[i ^ 1]].emplace_back(eset[i]);

			c[eset[i]].insert(make_pair(eset[i ^ 1], wset[i >> 1]));

		}

		for (int i = 0; i < n; ++i) {

			sort(a[i].begin(), a[i].end());

			a_begin[i] = a[i].begin();

			in_deg[i] = b[i].size();

			ot_deg[i] = a[i].size();

			if (!in_deg[i] || !ot_deg[i]) {

				q.push(i);

				vis[i] = 1;

			}

		}

		topo();

		vector<int>::iterator p, ed;

		for (int i = 0; i < n; ++i) if (!vis[i]) {

			vis[i] = 1;

			bfs_b7(i);

			for_dfs(i);

			for (p = b[i].begin(), ed = b[i].end(); p != ed; ++p) ++a_begin[*p];

			q.push(i);

			topo();

		}

	}



	inline void topo() {

		static int x;

		while (!q.empty()) {

			x = q.pop_getfront();

			for (auto p = a_begin[x], ed = a[x].end(); p != ed; ++p) if (!vis[p->first]) {

				if (--in_deg[p->first] == 0) {

					q.push(p->first);

					vis[p->first] = 1;

				}

			}

			for (auto p = b[x].begin(), ed = b[x].end(); p != ed; ++p) if (!vis[*p]) {

				if (--ot_deg[*p] == 0) {

					q.push(*p);

					vis[*p] = 1;

				}

			}

		}

	}



}



int eset[M];

double wset[M >> 1];

int n = 0,g=0;

inline void input()

{

	struct stat statbuf;

	register int sz = 0;

	if (stat("/data/test_data.txt", &statbuf) == 0)sz = statbuf.st_size;

	int fd = open("/data/test_data.txt", O_RDONLY);

	char* buf = (char*)mmap(NULL, sz, PROT_READ, MAP_PRIVATE, fd, 0);

	char* mapped = buf;

	int m;

	while (sscanf(mapped, "%u,%u,%lf%n", eset + n, eset + n + 1, wset + (n >> 1), &m) == 3) {

		n += 2;

		mapped += m;

	}

}



inline void output()

{

	n = 0;

	for (register int i = 3; i <= 8; ++i)n += (Solve::ans[i].size()) / i;

	int fd = open("/projects/student/result.txt", O_RDWR | O_CREAT, 0777);

	ftruncate(fd, n * 8 * 20);

	char*buf = (char*)mmap(NULL, n * 8 * 20, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

	char*mapped = buf;

	mapped+=sprintf(mapped, "%d\n", n);

	vector<int>::iterator it, ed;

#define write(ch) memcpy(mapped, DISC::str[*it], DISC::len[*(it)]); \

				  mapped += DISC::len[*(it++)]; \

				  *(mapped++) = ch;

	it = Solve::ans[3].begin(); ed = Solve::ans[3].end();

	while (it != ed) {

		write(',');

		write(',');

		write('\n');

	}

	it = Solve::ans[4].begin(); ed = Solve::ans[4].end();

	while (it != ed) {

		write(',');

		write(',');

		write(',');

		write('\n');

	}

	it = Solve::ans[5].begin(); ed = Solve::ans[5].end();

	while (it != ed) {

		write(',');

		write(',');

		write(',');

		write(',');

		write('\n');

	}

	it = Solve::ans[6].begin(); ed = Solve::ans[6].end();

	while (it != ed) {

		write(',');

		write(',');

		write(',');

		write(',');

		write(',');

		write('\n');

	}

	it = Solve::ans[7].begin(); ed = Solve::ans[7].end();

	while (it != ed) {

		write(',');

		write(',');

		write(',');

		write(',');

		write(',');

		write(',');

		write('\n');

	}

	it = Solve::ans[8].begin(); ed = Solve::ans[8].end();

	while (it != ed) {

		write(',');

		write(',');

		write(',');

		write(',');

		write(',');

		write(',');

		write(',');

		write('\n');

	}

	munmap(buf, n * 8 * 20);

	ftruncate(fd, mapped - buf);

#undef write

}

signed main()

{

	input();

	Solve::solve(eset, wset, n, DISC::init(eset, n));

	output();

	exit(0);

}



