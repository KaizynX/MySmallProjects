/*
 * @Author: Kaizyn
 * @Date: 2020-04-06 17:54:46
 * @LastEditTime: 2020-04-08 17:29:32
 */
#include <bits/stdc++.h>

using namespace std;

#define int unsigned

struct CLOCK{
	double st;
	CLOCK(){st=clock();}
	~CLOCK(){cerr<<endl<<(clock()-st)/1000<<"s"<<endl;}
}Clock;

struct DISC{
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

namespace zkx_dfs {

const int kN = 280000+7;
// point [0, num_point)
int num_point, num_result;
vector<int> *edge;
// result[i][j] 存储长度为 i 以 j 开头的环
vector<vector<int>> results[8][kN];

struct Dfs
{
    int depth, source_point;
    vector<int> visit, point_stack;
    Dfs() {
        depth = 0;
        vector<int>(kN, 0).swap(visit);
        vector<int>().swap(point_stack);
    }
    void solve(const int &_source_point) {
        source_point = _source_point;
        do_dfs(source_point);
        // assert(depth == 0);
        // assert(point_stack.empty());
    }
    void do_dfs(const int &current_point) {
        auto it = lower_bound(edge[current_point].begin(),
                              edge[current_point].end(), source_point);
        if (it == edge[current_point].end()) return;
        ++depth;
        visit[current_point] = 1;
        point_stack.emplace_back(current_point);
        if (*it == source_point) {
            if (depth >= 3) {
                ++num_result;
                results[depth][source_point].emplace_back(point_stack);
            }
            ++it;
        }
        if (depth < 7) for ( ; it != edge[current_point].end(); ++it) {
            if (visit[*it] != 0) continue;
            do_dfs(*it);
        }
        --depth;
        visit[current_point] = 0;
        point_stack.pop_back();
    }
} dfs[8];

// 传入 点的数量 和邻接表图
void Slove(int _num_point, vector<int> *_edge) {
    CLOCK Clock;
    num_point = _num_point;
    edge = _edge;
    for (int i = 0; i < num_point; ++i) {
        sort(edge[i].begin(), edge[i].end());
    }
    // 此处可以多线程
    for (int i = 0; i < num_point; i += 8) {
        dfs[0].solve(i);
        dfs[1].solve(i+1);
        dfs[2].solve(i+2);
        dfs[3].solve(i+3);
        dfs[4].solve(i+4);
        dfs[5].solve(i+5);
        dfs[6].solve(i+6);
        dfs[7].solve(i+7);
    }
    /*
    vector<thread> threads(8);
    for (int i = 0; i < num_point; i += 8) {
        for (int j = 0; j < 7; ++j) {
            if (threads[j].joinable()) threads[j].join();
            threads[j] = thread(dfs[j].solve, i+j);
        }
    }
    */
}

}

const int kN = 280000+7;
int num_point;
vector<unsigned> input_edge;
vector<int> edge[kN];

void Input();
void Discretization();
void BuildMap();
void AnswerNormalize();
void Output();

signed main()
{
    Input();
    Discretization();
    BuildMap();
    zkx_dfs::Slove(num_point, edge);
    Output();
    return 0;
}

void Input()
{
    freopen("test_data4.txt", "r", stdin);
    int u, v, w;
    while (scanf("%d,%d,%d", &u, &v, &w) == 3) {
        input_edge.emplace_back(u);
        input_edge.emplace_back(v);
    }
}

void Discretization()
{
    num_point = Disc.init(input_edge);
}

void BuildMap()
{
    for (int i = 0; i < input_edge.size(); i += 2) {
        edge[input_edge[i]].emplace_back(input_edge[i^1]);
    }
}

void Output()
{
    freopen("my_result.txt", "w", stdout);
    printf("%d\n", zkx_dfs::num_result);
    for (int i = 3; i <= 7; ++i) {
        for (int j = 0; j < num_point; ++j) {
            const vector<vector<int>> &result = zkx_dfs::results[i][j];
            for (auto &vec : result) {
                for (int k = 0; k < i-1; ++k) {
                    printf("%u,", Disc.b[vec[k]]);
                }
                printf("%u\r\n", Disc.b[vec[i-1]]);
            }
        }
    }
}