/*
 * @Author: Kaizyn
 * @Date: 2020-04-06 17:54:46
 * @LastEditTime: 2020-04-08 15:08:44
 */
#include <bits/stdc++.h>

using namespace std;

struct CLOCK{
	double st;
	CLOCK(){st=clock();}
	~CLOCK(){cerr<<endl<<(clock()-st)/1000<<"s"<<endl;}
}Clock;

namespace zkx_dfs {

const int kN = 280000+7;
// point [0, num_point)
int num_point, num_result;
vector<int> *edge;
// result[i][j] 存储长度为 i 以 j 开头的环
vector<vector<int>> results[8][kN];
// 这个如果多线程就不能共用
vector<int> visit(kN, 0), point_stack;

// 传入 点的数量 和邻接表图
void Slove(int, vector<int>*);

struct Dfs
{
    int depth, source_point;
    // 多线程就开里面
    // vector<int> visit, point_stack;
    Dfs(const int &_source_point) {
        depth = 0;
        source_point = _source_point;
        // vector<int>(kN, 0).swap(visit);
        // vector<int>().swap(point_stack);
        do_dfs(source_point);
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
};

void Slove(int _num_point, vector<int> *_edge) {
    CLOCK Clock;
    num_point = _num_point;
    edge = _edge;
    for (int i = 0; i < num_point; ++i) {
        sort(edge[i].begin(), edge[i].end());
    }
    // 此处可以多线程
    for (int i = 0; i < num_point; ++i) {
        Dfs dfs(i);
    }
}

}

const int kN = 280000+7;
int num_point;
vector<unsigned> u_vec, v_vec, all_vec;
vector<int> edge[kN];

void Input();
void Discretization();
void BuildMap();
void Tarjan();
void AnswerNormalize();
void Output();

int main()
{
    Input();
    Discretization();
    BuildMap();
    Tarjan();
    zkx_dfs::Slove(num_point, edge);
    Output();
    return 0;
}

void Input()
{
    freopen("test_data.txt", "r", stdin);
    int u, v, w;
    while (scanf("%d,%d,%d", &u, &v, &w) == 3) {
        u_vec.emplace_back(u);
        v_vec.emplace_back(v);
    }
}

void Discretization()
{
    all_vec.assign(u_vec.begin(), u_vec.end());
    all_vec.insert(all_vec.end(), v_vec.begin(), v_vec.end());
    sort(all_vec.begin(), all_vec.end());
    all_vec.erase(unique(all_vec.begin(), all_vec.end()), all_vec.end());
    num_point = all_vec.size();
    for (unsigned &u : u_vec)
        u = lower_bound(all_vec.begin(), all_vec.end(), u)-all_vec.begin();
    for (unsigned &v : v_vec)
        v = lower_bound(all_vec.begin(), all_vec.end(), v)-all_vec.begin();
}

void BuildMap()
{
    for (int i = 0; i < (int)u_vec.size(); ++i) {
        edge[u_vec[i]].emplace_back(v_vec[i]);
    }
    vector<unsigned>().swap(u_vec);
    vector<unsigned>().swap(v_vec);
}

void Tarjan()
{
    ;
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
                    printf("%u,", all_vec[vec[k]]);
                }
                printf("%u\r\n", all_vec[vec[i-1]]);
            }
        }
    }
}