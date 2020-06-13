/*
 * @Author: Kaizyn
 * @Date: 2020-04-06 17:54:46
 * @LastEditTime: 2020-04-06 23:42:10
 */
#include <bits/stdc++.h>

using namespace std;

#define LOCAL_JUDGE

#ifdef LOCAL_JUDGE
const int kN = 1e3+7;
#else
const int kN = 280000+7;
#endif

int num_point, sum_answer, a_set_circle_length;
vector<int> edge[kN];
map<int, int> has_point[kN];
vector<vector<int>> answer_circle[8];
// map<int, vector<int>> previous_point[kN];
map<pair<int, int>, vector<int>> previous_point[kN];
// hash(pair(point, depth)) = depth*num_point+point

void Input();
void Discretization();
void Tarjan();
void Work();
void Dfs(const int&, const int&, const int&);
void FindCircle(const int&, const int&);
void FindArc(const int&, const int&, const int&, vector<vector<int>>&);
void CircleCheck(const vector<int>&, const vector<int>&);
void VectorNormalize(vector<int>&);
void AnswerNormalize();
void Output();

int main()
{
    Input();
    Discretization();
    Tarjan();
    Work();
    AnswerNormalize();
    Output();
    return 0;
}

void Input()
{
    // freopen("test_data.txt", "r", stdin);
    int u, v, w;
    while (scanf("%d,%d,%d", &u, &v, &w) == 3) {
        num_point = max({num_point, u, v});
        edge[u].emplace_back(v);
        edge[v].emplace_back(u);
    }
}

void Discretization()
{
    ;
}

void Tarjan()
{
    ;
}

void Work()
{
    for (a_set_circle_length = 3; a_set_circle_length <= 7; ++a_set_circle_length) {
        for (int j = 1; j <= num_point; ++j) {
            Dfs(j, 0, j);
        }
    }
}

void Dfs(const int &current_point, const int &depth, const int &source_point)
{
    if (depth == a_set_circle_length/2) {
        has_point[source_point][current_point] = 1;
    }
    // 根据当前要找的环的长度而定
    if (depth == (a_set_circle_length+1)/2) {
        // if (current_point 在 a_set_circle_length/2 深度有点 source_point)
        if (has_point[current_point].count(source_point)) {
            FindCircle(current_point, source_point);
        }
        return;
    }
    for (int &next_point : edge[current_point]) {
        // 如果绕着一个二元环走两趟则重复,有待优化
        if (current_point == source_point) continue;
        // 记录从 source_point 开始深度 depth 处点 next_point 的前一个结点
        previous_point[next_point][make_pair(source_point, depth+1)]\
            .emplace_back(current_point);
        Dfs(next_point, depth+1, source_point);
    }
}

void FindCircle(const int &point_one, const int &point_two)
{
    // 寻找路径
    // 从 point_one 沿着 previous_point 一直到 point_two
    // 再从 point_two 沿着 previous_point 一直到 point_one
    // 得到一个环,判断有没有重复的点
    static vector<vector<int>> arc_one, arc_two;
    vector<vector<int>>().swap(arc_one);
    vector<vector<int>>().swap(arc_two);
    FindArc(point_one, a_set_circle_length/2, point_two, arc_one);
    FindArc(point_two, (a_set_circle_length+1)/2, point_one, arc_two);
    for (vector<int> &vec_one : arc_one) reverse(vec_one.begin(), vec_one.end());
    for (vector<int> &vec_two : arc_two) reverse(vec_two.begin(), vec_two.end());
    for (vector<int> &vec_one : arc_one) {
        for (vector<int> &vec_two : arc_two) {
            CircleCheck(vec_one, vec_two);
        }
    }
}

void FindArc(const int &current_point, const int &depth, const int &source_point, vector<vector<int>> &arc_vector)
{
    static vector<int> point_stack;
    if (depth == 0) {
        arc_vector.emplace_back(point_stack);
        return;
    }
    point_stack.emplace_back(current_point);
    for (int &prev_point : previous_point[current_point][make_pair(source_point, depth)]) {
        FindArc(prev_point, depth-1, source_point, arc_vector);
    }
    point_stack.pop_back();
}

// one 是较小弧
void CircleCheck(const vector<int> &vec_one, const vector<int> &vec_two)
{
    static vector<int> vec;
    static map<int, int> visit;
    visit.clear();
    for (const int &point : vec_one) {
        if (visit.count(point)) return;
        visit[point] = 1;
    }
    for (const int &point : vec_two) {
        if (visit.count(point)) return;
        visit[point] = 1;
    }
    vec = vec_one;
    vec.insert(vec.end(), vec_two.begin(), vec_two.end());
    VectorNormalize(vec);
    answer_circle[a_set_circle_length].emplace_back(vec);
}

void VectorNormalize(vector<int> &vec)
{
    static vector<int> temporary_vec;
    int first_postion = 0;
    for (int postion = 1; postion < (int)vec.size(); ++postion) {
        if (vec[postion] < vec[first_postion]) {
            first_postion = postion;
        }
    }
    temporary_vec.assign(vec.begin()+first_postion, vec.end());
    temporary_vec.insert(temporary_vec.end(), vec.begin(), vec.begin()+first_postion);
    swap(temporary_vec, vec);
}

void AnswerNormalize()
{
    for (int i = 3; i <= 7; ++i) {
        sum_answer += answer_circle[i].size();
        sort(answer_circle[i].begin(), answer_circle[i].end());
    }
}

void Output()
{
    // freopen("my_result.txt", "w", stdout);
    printf("%d\n", sum_answer);
    for (int i = 3; i <= 7; ++i) {
        for (auto vec : answer_circle[i]) {
            for (int j = 0; j < i; ++j) {
                printf("%d%c", vec[j], " \n"[j==i-1]);
            }
        }
    }
}